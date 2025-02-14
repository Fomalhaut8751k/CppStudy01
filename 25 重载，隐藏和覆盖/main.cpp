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
	// d.show(10);  // ���������أ����»�������ͬ���ĺ�����������
	d.Base::show();  // ֻ�ܼ��ϻ����������
	*/

	Base b(10);
	Derive d(20);
	// ������� <= ���������
	b = d;
	// ��������� <= �������
	// d = b;

	// ����ָ�� <= ����������ַ
	Base* pb = &d;
	pb->show();
	pb->show(20);
	
	// ������ָ�� <= ��������ַ
	// Derive* pd = &b;

	return 0;
}