#include<iostream>

using namespace std;

class Base {
public:
	Base(int data = 10) :ma(data) {}
	void show() { cout << "Base::show()" << endl; }
	void show(int) { cout << "Base::show(int)" << endl; }

private:
	int ma;
};

class Derive : public Base {
public:
	Derive(int data = 20) :Base(data), mb(data) {}
	//void show() { cout << "Derive::show()" << endl; }
private:
	int mb;
};

int main() {

	/*
	Derive d;
	d.show();
	// d.show(10);  // 触发了隐藏，导致基类所有同名的函数都被隐藏
	d.Base::show();  // 只能加上基类的作用域
	*/

	Base b(10);
	Derive d(20);
	// 基类对象 <= 派生类对象
	b = d;
	// 派生类对象 <= 基类对象
	// d = b;

	// 基类指针 <= 派生类对象地址
	Base* pb = &d;
	pb->show();
	pb->show(20);
	
	// 派生类指针 <= 基类对象地址
	// Derive* pd = &b;

	return 0;
}