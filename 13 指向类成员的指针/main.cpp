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

	// ----------------------ָ���Ա������ָ��-------------------------
	// int* p = &Test::ma;  �޷���int Test::* תΪ int*
	int Test::* p = &Test::ma;
    // *p = 20;  �������������ȡ�����޸���ͨ����
	t1.*p = 20;
	cout << t1.*p << endl;

	t2->*p = 30;
	cout << t2->*p << endl;

	int* p1 = &Test::mb;  // ���ھ�̬��������ֱ��ͨ����ָͨ�����
	*p1 = 30;


	// ---------------------ָ���Ա������ָ��--------------------------
	void(Test::*pfunc)() = &Test::func;
	(t1.*pfunc)();
	(t2->*pfunc)();

	void(*pfunc1)() = &Test::static_func;
	(*pfunc1)();


	delete t2;

	return 0;
}