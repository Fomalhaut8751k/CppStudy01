#include<iostream>

using namespace std;
/*
c++����������أ��Ƕ����������ֵúͱ�������������һ��
*/

// ������
class CComplex {
	friend CComplex operator+(const CComplex& comp1, const CComplex& comp2);
	//friend CComplex operator++(CComplex& comp);
	//friend CComplex operator++(CComplex& comp, int);
	friend ostream& operator<< (ostream& cout, const CComplex& comp);

	friend istream& operator>> (istream& cin, CComplex& comp);

public:
	CComplex(int r = 0, int i = 0) :
		_mreal(r),
		_mimage(i) {

	}

	// �ӷ���������� 
	CComplex operator+ (const CComplex& comp) {  // ���ܷ�������
		return CComplex(_mreal + comp._mreal, _mimage + comp._mimage);
	}

	// ǰ�õ���
	CComplex operator++ () {
		return CComplex(_mreal + 1, _mimage + 1);
	}

	// ���õ���
	CComplex operator++(int) {
		return CComplex(_mreal++, _mimage + 1);
	}

	// +=
	void operator+=(CComplex& comp) {
		_mreal += comp._mreal;
		_mimage += comp._mimage;
	}

	void show() const {
		cout << "����: " << _mreal << " + j" << _mimage << endl;
	}

	int returnMreal(){
		return _mreal;
	}

	int returnMimage() {
		return _mimage;
	}

private:
	int _mreal;
	int _mimage;
};

//CComplex operator+(CComplex& comp1, CComplex& comp2) {
//	int comp1_mreal = comp1.returnMreal();
//	int comp1_mimage = comp1.returnMimage();
//
//	int comp2_mreal = comp2.returnMreal();
//	int comp2_mimage = comp2.returnMimage();
//	return CComplex(comp1_mreal + comp2_mreal, comp2_mreal + comp2_mimage);
//}

CComplex operator+(const CComplex& comp1, const CComplex& comp2) {
	return CComplex(comp1._mreal + comp2._mreal, comp2._mreal + comp2._mimage);
}

//CComplex operator++(CComplex& comp) {
//	comp._mreal++;
//	return comp;
//}
//
//CComplex operator++(CComplex& comp, int) {
//	comp._mreal++;
//	return comp;
//}

ostream& operator<< (ostream &cout, const CComplex & comp) {
	cout << comp._mreal << " + j" << comp._mimage;
	return cout;
}

istream& operator>> (istream& cin, CComplex& comp) {
	cin >> comp._mreal >> comp._mimage;
	return cin;
}

int main() {

	CComplex comp1(20, 10);
	CComplex comp2(10, 20);

	comp1.show();
	CComplex comp3 = comp1 + comp2;
	// �����Ͼ��� CComplex comp3 = comp1.operator+(comp2);
	comp3.show();

	CComplex comp4 = comp1 + 20;  // ��һ������һ�����εĹ��캯����Ȼ��������ʱ����(20 + j0)
	comp4.show();

	// CComplex comp5 = 30 + comp1; �����comp1 + 20 => comp1.operator+(20),��˳��Ҫ��
	// ��Ϊ��Ա���������أ����������Ҳ������ȫ�ֺ�����������ʵ��

	CComplex comp5 = 30 + comp1;  // ��Ա�Ĳ��У�����ȫ�ֵ�

	/*
		����������������ʱ������ö������������غ���(���ȵ��ó�Ա����)�����û�г�Ա����
		����ȫ���������Һ��ʵ���������غ���
	*/

	/*
		ǰ�õ�����operator++();
		���õ�����operator++(int)
	*/

	comp5.show();
	comp5 = comp1++;
	comp5.show();
	comp5 = ++comp1;

	// ����ǰ�úͺ���
	comp5.show();
	cout << "���õ���: ";
	(comp5++).show();
	cout << "ǰ�õ���: ";
	(++comp5).show();

	cout << comp5 << " " << comp4 << endl;

	CComplex comp6;
	cin >> comp6;
	comp6.show();

	return 0;
}