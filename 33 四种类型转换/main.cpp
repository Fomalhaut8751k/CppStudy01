#include<iostream>

using namespace std;

/*
	C++语言级别提供的四种类型转换方式
	const_cast: 去掉常量属性的一个类型转换
	static_cast: 提供编译器认为安全的类型转换
	reinterpret_cast: 类似于c风格的强制类型转换
	dtnamic_cast: 主要用在继承结构中，可以支持RTTI类型识别的上下转换
*/

class Base {
public:
	virtual void func() = 0;
};

class Derive1 : public Base {
public:
	void func() {
		cout << "call Derive1::func()" << endl;
	}
};

class Derive2 : public Base {
public:
	void func() {
		cout << "call Derive2::func()" << endl;
	}
	// 假如设计了一个新的func版本，希望Derive2的实例化对象调用新的版本
	void derive02func() {
		cout << "call Derive2::derive02func()" << endl;
	}
};

void show(Base* p) {
	Derive2* pd2 = dynamic_cast<Derive2*>(p);  // 判断p指向的是哪个派生类对象
	if (pd2 != nullptr) { // 如果非nullptr说明是Derive2类型的
		pd2->derive02func();
	}
	else {  // 不是的话类型转化失败，就是nullptr
		p->func();
	}
}

void convert(Base* p) {
	if (dynamic_cast<Derive1*>(p) == nullptr) {
		cout << typeid(p).name() << " --> " 
			<< "nullptr" << endl;
	}
	else {
		cout << typeid(p).name() << " --> " 
			<< typeid(dynamic_cast<Derive1*>(p)).name() << endl;
	}
}

int main() {
	// c语言风格
	const int a = 10;
	int* p1 = (int*)&a;
	// c++语言风格
	int* p2 = const_cast<int*>(&a);
	// char* p3 = const_cast<char*>(&a);  // a去掉const必须和<>里面保持一致
	// int b = const_cast<int>(a);  // <>里面必须是指针或引用

	int* p = nullptr;
	// short* b = static_cast<short*>(p);  // short和int没有任何联系，被否决
	// double* b = static_cast<double*>(p); // double可以访问8字节，int只有4字节，不安全

	short* b = reinterpret_cast<short*>(p);  // 强制转换和c一样，不考虑安不安全

	Derive1 d1;
	Derive2 d2;

	show(&d1);
	show(&d2);

	Base* p1_ = &d1; convert(p1_);
	Base* p2_ = &d2; convert(p2_);

	return 0;
}