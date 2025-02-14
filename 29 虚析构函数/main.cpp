#include<iostream>

using namespace std;

class Base {
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	virtual ~Base() { cout << "~Base()" << endl; }
	void show() { cout << "call Base::show()" << endl; }
protected:
	int ma;
};

class Derive :public Base {
public:
	Derive(int data) : Base(data), mb(data) { cout << "Derive()" << endl; }
	~Derive() { cout << "~Derive()" << endl; }
private:
	int mb;
};

int main() {

	/*Derive d(20);
	Base* pb = &d;
	pb->show();*/

	Base* pb = new Derive(20);
	pb->show();
	delete pb;

	// 这段代码的运行结果中：派生类的析构函数没有调用
	return 0;
}