#include<iostream>
#include<string>

using namespace std;

#if 0 // ��Ŀһ
class Animal {
public:
	Animal(string name) :_name(name) {}
	virtual void bark() {}  // ���麯��
protected:
	string _name;
};

class Cat : public Animal {
public:
	Cat(string name) :Animal(name) {}
	void bark() { 
		cout << "Cat::func()" << endl;  // ���Դ���
		cout << _name << " bark: miao miao!" << endl; 
	}
};

class Dog : public Animal {
public:
	Dog(string name) :Animal(name) {}
	void bark() { 
		cout << "Dog::func()" << endl;  // ���Դ���
		cout << _name << " bark: wang wang!" << endl; 
	}
};

class Pig : public Animal {
public:
	Pig(string name) :Animal(name) {}
	void bark() {
		cout << "Pig::func()" << endl;  // ���Դ���
		cout << _name << " bark: heng heng!" << endl; 
	}
};


int main() {
	/*
		Animal�ǳ����࣬��Ϊ����һ�����麯������˲���ʵ������
		���ǿ��Զ���Animal*���ָ��
	*/
	Animal* p1 = new Cat("�ӷ�è");
	Animal* p2 = new Dog("����");
	/*
		�������ڻ��������Ƿ���ǰ�棬�������౾�����ݷ��ں��棬
		����ָ��ָ�������������Զָ����������ࡾ���ࡿ�������ݵ���ʼλ��

		ָ���˻���ĳ�Ա������_name?
		############ error : ����/�ڴ���ʼλ�÷ŵ���vfptr��############
	*/
	int* p11 = (int*)p1;
	int* p22 = (int*)p2;
	/*
		int*�ĸ��ֽڣ���ʱp11
		������һ������������_name
		############ error : ����vfptr��############
		�պ�vfptrҲ��4���ֽ�
	*/
	int tmp = p11[0];
	p11[0] = p22[0];
	p22[0] = tmp;
	
	p1->bark();
	p2->bark();
	/*
		���� bark: miao miao!  
		�ӷ�è bark: wang wang!
		############ error : �ȴ�ӡ�ӷ�è�ٴ�ӡ������############
		p1->bark(), vfptrָ���Dog���vftable�����ǵ��õ���Dog::func();
		����p1��Cat���͵�ָ�룬���this->_name = �ӷ�è
		p2->bark()ͬ��
	*/

	delete p1;
	delete p2;

	return 0;
}
#endif


#if 0  // �����
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
		��̬�󶨣����õ���Derive::show()�����ǽ���ǣ�
		############	call Derive::show i:10  ############
		������Derive��show����������ʹ����Base���β�Ĭ��ֵ

		�������õĵײ��߼�˳��
		1. ��ѹ�β���ջ(���ҵ���)
		2. ��call����һ�������ջ
		3. ѹ��main����ջ֡��ջ��
		4. ���ٺ���ջ֡
		5. ������ϣ�����ջ֡
		6. ebp�ص�main����ջ��
		7. call����һ��ָ�����ĳ���Ĵ���
		8. call����һ��ָ��һ�����ͷ��β�

		00DD28DE  mov         esi,esp  
		00DD28E0  push        0Ah						ѹջ
		00DD28E2  mov         eax,dword ptr [p]  
		00DD28E5  mov         edx,dword ptr [eax]  

		00DD28E7  mov         ecx,dword ptr [p]  
		00DD28EA  mov         eax,dword ptr [edx]  
		00DD28EC  call        eax

		��Ϊ����׶�Ҫȷ���βΣ�����ѹջҪ�ڱ���׶����
		���Ƕ�̬�󶨵��±���ʱ����������ַ��δȷ����
		����׶�ֻ֪��p��Base���͵�ָ�룬����ֻ�ܿ�Base��show�Ĳ���
		
	*/
	delete p;

	return 0;
}
#endif


#if 0  // ������
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
		���Derive�е�show��������˽���������£�

			��Ա�����ܲ��ܵ��ã�����˵�����ķ���Ȩ���ǲ���public�ģ�����
			����׶ξ���Ҫȷ���õ�
			�����ܵ��õ�Derive::show()����������ʱ�ڲ�ȷ����

		����ǿ����������е�

		�������һ�£���������private������������public
		�����������У���Ϊ����׶Σ�������ֻ�ܿ���p��Base*���͵ģ�������
		private���ⲻ�ɷ��ʣ����p->show()�ڱ���׶ξͳ�����
	*/
	delete p;

	return 0;
}
#endif


#if 1  // ������
class Base {
public:
	Base() {
		/*
			push ebp  // �ѵ��÷���ջ�׵�ַ��ջ
			mov ebp, esp  // ��ջ��ָ���ƶ���ջ��ָ��λ��
			sub esp, 4Ch  // ���ٺ���ջ֡
			rep stos esp<->ebp 0xCCCCCCCC  // ��ʼ��
		
			���������麯������ô������Ͱ�vftable�ĵ�ַ����vfptr
			vfptr <- &Base::vftable

			Ȼ�������뿪ʼ����
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
		���Ƕ�̬��
		��һ�������е�pb1->show()ʱ����
			clear��Base�ڴ�ȫ�������0�������ڴ���ʼλ�õ�vfptr
			��vfptrָ���ַ0��λ�ã��Ѿ����ʲ���vftable�ˣ���0��ַҲ�ǲ��ܷ��ʵ�
		�ڶ����ֿ�����������
			new Derive()ʱ���ȵ���Base(),�ٵ���Derive()
			
		�ȵ���Base()���ڴ�֮ǰ��Base��vftable�ĵ�ַ����vfptr�����Ǹ�clear()�����
		�����ֵ���Derive����Derive��vftable��ַ����vfptr������û��
	*/

	return 0;
}
#endif