#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

class Person {
public:
	// 普通构造函数
	Person(int age, const char* name)
	:_age(age){
		if (name != nullptr) {
			_name = new char[strlen(name) + 1];
			strcpy(_name, name);
		}
		else {
			_name = new char[1];
			*_name = '\0';
		}
		_age = age;
		_number++;

	}

	// 拷贝构造函数
	Person(const Person& per) {
		_name = new char[strlen(per._name) + 1];
		/*for (int i = 0; i < strlen(per._name); i++) {
			_name[i] = per._name[i];
		}*/
		strcpy(_name, per._name);
		_age = per._age;
		_number++;
	}

	// 赋值
	Person& operator=(const Person& per) {
		if (this == &per) {
			return *this;
		}
		delete[] _name;
		_name = new char[strlen(per._name) + 1];
		/*for (int i = 0; i < strlen(per._name); i++) {
			_name[i] = per._name[i];
		}*/
		strcpy(_name, per._name);
		_age = per._age;
		return *this;
	}

	void show() {
		cout << "姓名：" << _name << "\t" << "年龄：" << _age << endl;
	}

	// 想要形参是const Person*可以
	// 常成员方法
	void show() const{
		cout << "姓名：" << _name << "\t" << "年龄：" << _age << endl;
		// _name = "awl";
	}

	int count() {
		return _number;
	}

	// 析构函数
	~Person() {
		delete[] _name;
		_name = nullptr;
	}

private:
	int _age;
	char* _name;

	static int _number;
};

// 静态成员变量
// 类内声明，类外初始化
int Person::_number = 0;

// 静态成员函数
/*
	1. 属于类的作用域
	2. 用类名作用域来调用方法
	3. 可以任意访问对象的私有成员，仅限于不依赖对象的成员(静态的)
*/

int main() {

	Person p1(23, "wudongwei");
	cout << "已创建人员数：" << p1.count() << endl;
	Person p2 = p1;
	cout << "已创建人员数：" << p1.count() << endl;
	Person p3(21, "yezhenhao");
	p3 = p2;
	cout << "已创建人员数：" << p1.count() << endl;
	p1.show();
	p2.show();
	p3.show();

	const Person p4(24, "zhoujunbo");
	// p4.show(); 前面说到，调用成员方法是会把对象的地址作为参数传入
	// 对象是一个const类型，故其地址为 const Person*，而show的形参是Person*
	// 就相当于Person* <= const Person* 是错误的
	p4.show();
	// 说明普通的方法常对象是调用不了的
	// 常对象只能调用常方法，而普通对象可以调用不同方法和常方法
	// 一般建议只读操作的成员方法一律写成常方法
	// 常方法里不能修改成员变量，例如_age,因为相当于this->_age，但this是const修饰
	// 的，所以指针指向的内容无法修改


	return 0;
}