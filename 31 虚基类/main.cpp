#include<iostream>

using namespace std;

/*
	�����ࣺ�д��麯������
	����ࣺ����̳е���

*/

class A {
public:
	virtual void func() { cout << "call A::func" << endl; }
	~A() { cout << "call ~A()" << endl; }
private:
	int ma;
};

class B: virtual public A{
public:
	void func() { cout << "call B::func" << endl; }

	void* operator new(size_t size) {
		void* p = malloc(size);
		cout << "operator new p: " << p << endl;
		return p;
	}

	~B() { cout << "call ~B()" << endl; }
private:
	int mb;
};

int main() {
	A* a = new B() ;
	cout << "main p:" << a << endl;
	a->func();
	delete a;

	return 0;
}