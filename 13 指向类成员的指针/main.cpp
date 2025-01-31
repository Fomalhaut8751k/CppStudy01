#include<iostream>

using namespace std;

class Test {
public:
	void func() { cout << "call Test::func" << endl; }
	static void static_func() { cout << "Test::static_func" << endl; }
	int ma;
	static int mb;
};

int Test::mb;

int main() {

	Test t1;
	Test* t2 = new Test();

	// ----------------------指向成员变量的指针-------------------------
	// int* p = &Test::ma;  无法从int Test::* 转为 int*
	int Test::* p = &Test::ma;
    // *p = 20;  不允许脱离对象取访问修改普通对象
	t1.*p = 20;
	cout << t1.*p << endl;

	t2->*p = 30;
	cout << t2->*p << endl;

	int* p1 = &Test::mb;  // 对于静态变量可以直接通过普通指针接收
	*p1 = 30;


	// ---------------------指向成员方法的指针--------------------------
	void(Test::*pfunc)() = &Test::func;
	(t1.*pfunc)();
	(t2->*pfunc)();

	void(*pfunc1)() = &Test::static_func;
	(*pfunc1)();


	delete t2;

	return 0;
}