#include<iostream>

using namespace std;

/*
	�̳еı��ʺ�ԭ��
	a. ����ĸ��ã�b. 
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
	// �̳����ĳ�Ա����Ҫ�û���Ĺ��캯��ȥ����
	Derive(int data): Base(data), mb(data) { cout << "Derive()" << endl; }
	//Derive(int data) : ma(data), mb(data) { cout << "Derive()" << endl; }

	// ����������������Զ�����
	~Derive() { cout << "~Derive()" << endl; }
private:
	int mb;
};

int main() {
	
	Derive d(20);


	return 0;
}