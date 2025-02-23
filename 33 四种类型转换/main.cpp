#include<iostream>

using namespace std;

/*
	C++���Լ����ṩ����������ת����ʽ
	const_cast: ȥ���������Ե�һ������ת��
	static_cast: �ṩ��������Ϊ��ȫ������ת��
	reinterpret_cast: ������c����ǿ������ת��
	dtnamic_cast: ��Ҫ���ڼ̳нṹ�У�����֧��RTTI����ʶ�������ת��
*/

class Base {
public:
	virtual void func() = 0;
};

class Derive1 : public Base {
public:
	void func() {
		cout << "call Derive1::func()" << endl;
	}
};

class Derive2 : public Base {
public:
	void func() {
		cout << "call Derive2::func()" << endl;
	}
	// ���������һ���µ�func�汾��ϣ��Derive2��ʵ������������µİ汾
	void derive02func() {
		cout << "call Derive2::derive02func()" << endl;
	}
};

void show(Base* p) {
	Derive2* pd2 = dynamic_cast<Derive2*>(p);  // �ж�pָ������ĸ����������
	if (pd2 != nullptr) { // �����nullptr˵����Derive2���͵�
		pd2->derive02func();
	}
	else {  // ���ǵĻ�����ת��ʧ�ܣ�����nullptr
		p->func();
	}
}

void convert(Base* p) {
	if (dynamic_cast<Derive1*>(p) == nullptr) {
		cout << typeid(p).name() << " --> " 
			<< "nullptr" << endl;
	}
	else {
		cout << typeid(p).name() << " --> " 
			<< typeid(dynamic_cast<Derive1*>(p)).name() << endl;
	}
}

int main() {
	// c���Է��
	const int a = 10;
	int* p1 = (int*)&a;
	// c++���Է��
	int* p2 = const_cast<int*>(&a);
	// char* p3 = const_cast<char*>(&a);  // aȥ��const�����<>���汣��һ��
	// int b = const_cast<int>(a);  // <>���������ָ�������

	int* p = nullptr;
	// short* b = static_cast<short*>(p);  // short��intû���κ���ϵ�������
	// double* b = static_cast<double*>(p); // double���Է���8�ֽڣ�intֻ��4�ֽڣ�����ȫ

	short* b = reinterpret_cast<short*>(p);  // ǿ��ת����cһ���������ǰ�����ȫ

	Derive1 d1;
	Derive2 d2;

	show(&d1);
	show(&d2);

	Base* p1_ = &d1; convert(p1_);
	Base* p2_ = &d2; convert(p2_);

	return 0;
}