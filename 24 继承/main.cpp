#include<iostream>

using namespace std;

/*
	继承的本质和原理：
	a. 代码的复用，b. 
*/

class Base {
public:
	Base(int data) :ma(data) { cout << "Base()" << endl; }
	~Base() { cout << "~Base()" << endl; }
protected:
	int ma;
};

class Derive :public Base {
public:
	// 继承来的成员变量要用基类的构造函数去构造
	Derive(int data): Base(data), mb(data) { cout << "Derive()" << endl; }
	//Derive(int data) : ma(data), mb(data) { cout << "Derive()" << endl; }

	// 基类的析构函数会自动调用
	~Derive() { cout << "~Derive()" << endl; }
private:
	int mb;
};

int main() {
	
	Derive d(20);


	return 0;
}