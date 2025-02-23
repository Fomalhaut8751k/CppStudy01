#include<iostream>

using namespace std;

// �麯������̬�󶨺Ͷ�̬��
class Base {
public:
	Base(int data = 10) :ma(data) {}
	// �麯��
	void show() { cout << "Base::show()" << endl; }
	virtual void show(int) { cout << "Base::show(int)" << endl; }

protected:
	int ma;
};

class Derive:public Base {
public:
	Derive(int data = 20) :Base(data), mb(data) {}
	void show() { cout << "Derivr::show()" << endl; }
private:
	int mb;
};


int main() {
	Derive d(50);
	Base* pb = &d;
	pb->show();  
	pb->show(10);

	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;

	cout << typeid(pb).name() << endl;
	cout << typeid(*pb).name() << endl;
	return 0;
}