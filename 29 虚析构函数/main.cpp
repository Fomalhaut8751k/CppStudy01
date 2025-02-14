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

	// ��δ�������н���У����������������û�е���
	return 0;
}