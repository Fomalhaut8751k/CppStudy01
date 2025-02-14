#include<iostream>

using namespace std;

/*
	抽象类：有纯虚函数的类
	虚基类：被虚继承的类

*/

class A {
public:
private:
	int ma;
};

class B: virtual A{
public:
private:
	int mb;
};

int main() {


	return 0;
}