#include<iostream>
#include<string>

using namespace std;

#if 0 // 题目一
class Animal {
public:
	Animal(string name) :_name(name) {}
	virtual void bark() {}  // 纯虚函数
protected:
	string _name;
};

class Cat : public Animal {
public:
	Cat(string name) :Animal(name) {}
	void bark() { 
		cout << "Cat::func()" << endl;  // 测试代码
		cout << _name << " bark: miao miao!" << endl; 
	}
};

class Dog : public Animal {
public:
	Dog(string name) :Animal(name) {}
	void bark() { 
		cout << "Dog::func()" << endl;  // 测试代码
		cout << _name << " bark: wang wang!" << endl; 
	}
};

class Pig : public Animal {
public:
	Pig(string name) :Animal(name) {}
	void bark() {
		cout << "Pig::func()" << endl;  // 测试代码
		cout << _name << " bark: heng heng!" << endl; 
	}
};


int main() {
	/*
		Animal是抽象类，因为他有一个纯虚函数，因此不能实例化，
		但是可以定义Animal*类的指针
	*/
	Animal* p1 = new Cat("加菲猫");
	Animal* p2 = new Dog("二哈");
	/*
		派生类内基类数据是放在前面，而派生类本身数据放在后面，
		基类指针指向派生类对象，永远指向的是派生类【基类】部分数据的起始位置

		指向了基类的成员变量：_name?
		############ error : 基类/内存起始位置放的是vfptr！############
	*/
	int* p11 = (int*)p1;
	int* p22 = (int*)p2;
	/*
		int*四个字节？此时p11
		下面是一个交换，交换_name
		############ error : 交换vfptr！############
		刚好vfptr也是4个字节
	*/
	int tmp = p11[0];
	p11[0] = p22[0];
	p22[0] = tmp;
	
	p1->bark();
	p2->bark();
	/*
		二哈 bark: miao miao!  
		加菲猫 bark: wang wang!
		############ error : 先打印加菲猫再打印二哈！############
		p1->bark(), vfptr指向的Dog类的vftable，于是调用的是Dog::func();
		但是p1是Cat类型的指针，因此this->_name = 加菲猫
		p2->bark()同理
	*/

	delete p1;
	delete p2;

	return 0;
}
#endif


#if 0  // 问题二
class Base {
public:
	virtual void show(int i = 10) {
		cout << "call Base::show i:" << i << endl;
	}
};

class Derive : public Base {
public:
	void show(int i = 20) {
		cout << "call Derive::show i:" << i << endl;
	}
};

int main() {
	Base* p = new Derive();
	p->show();
	/*
		动态绑定，调用的是Derive::show()，但是结果是：
		############	call Derive::show i:10  ############
		即调用Derive的show方法，但是使用了Base的形参默认值

		函数调用的底层逻辑顺序：
		1. 先压形参入栈(从右到左)
		2. 把call的下一个语句入栈
		3. 压入main函数栈帧的栈底
		4. 开辟函数栈帧
		5. 调用完毕，回收栈帧
		6. ebp回到main函数栈底
		7. call的下一个指令放入某个寄存器
		8. call的下一条指令一般是释放形参

		00DD28DE  mov         esi,esp  
		00DD28E0  push        0Ah						压栈
		00DD28E2  mov         eax,dword ptr [p]  
		00DD28E5  mov         edx,dword ptr [eax]  

		00DD28E7  mov         ecx,dword ptr [p]  
		00DD28EA  mov         eax,dword ptr [edx]  
		00DD28EC  call        eax

		因为编译阶段要确定形参，参数压栈要在编译阶段完成
		但是动态绑定导致编译时期连函数地址都未确定？
		编译阶段只知道p是Base类型的指针，所以只能看Base的show的参数
		
	*/
	delete p;

	return 0;
}
#endif


#if 0  // 问题三
class Base {
public:
	virtual void show() {
		cout << "call Base::show" << endl;
	}
};

class Derive : public Base {
private:
	void show() {
		cout << "call Derive::show" << endl;
	}
};

int main() {
	Base* p = new Derive();
	p->show();
	/*
		如果Derive中的show方法放在私有作用域下：

			成员方法能不能调用，就是说方法的访问权限是不是public的，是在
			编译阶段就需要确定好的
			最终能调用到Derive::show()，是在运行时期才确定的

		因此是可以正常运行的

		如果交换一下，基类内是private，派生类内是public
		则不能正常运行，因为编译阶段，编译器只能看到p是Base*类型的，但由于
		private类外不可访问，因此p->show()在编译阶段就出错了
	*/
	delete p;

	return 0;
}
#endif


#if 1  // 问题四
class Base {
public:
	Base() {
		/*
			push ebp  // 把调用方的栈底地址入栈
			mov ebp, esp  // 把栈底指针移动到栈顶指针位置
			sub esp, 4Ch  // 开辟函数栈帧
			rep stos esp<->ebp 0xCCCCCCCC  // 初始化
		
			如果类包含虚函数，那么在这里，就把vftable的地址给到vfptr
			vfptr <- &Base::vftable

			然后函数代码开始运行
		*/
		cout << "call Base()" << endl;
		clear();
	}

	void clear() { memset(this, 0, sizeof(*this)); }

	virtual void show() {
		cout << "call Base::show()" << endl;
	}
};

class Derive : public Base {
public:
	Derive(){
		cout << "call Derive()" << endl;
	}
	void show() {
		cout << "call Derive::show()" << endl;
	}
};


int main() {
	//Base* pb1 = new Base();
	//pb1->show();
	//delete pb1;

	Base* pb2 = new Derive();
	int* vfptr = (int*)pb2;
	cout << vfptr << endl;
	pb2->show();
	delete pb2;

	/*
		都是动态绑定
		第一部分运行到pb1->show()时报错
			clear把Base内存全部变成了0，包括内存起始位置的vfptr
			即vfptr指向地址0的位置，已经访问不到vftable了，且0地址也是不能访问的
		第二部分可以正常运行
			new Derive()时，先调用Base(),再调用Derive()
			
		先调用Base()，在此之前把Base的vftable的地址给到vfptr，但是给clear()清掉了
		不过又调用Derive，把Derive的vftable地址给到vfptr，所以没事
	*/

	return 0;
}
#endif