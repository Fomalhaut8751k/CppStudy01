#include<iostream>

using namespace std;
/*
c++的运算符重载：是对象的运算表现得和编译器内置类型一样
*/

// 复数类
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

	// 加分运算符重载 
	CComplex operator+ (const CComplex& comp) {  // 不能返回引用
		return CComplex(_mreal + comp._mreal, _mimage + comp._mimage);
	}

	// 前置递增
	CComplex operator++ () {
		return CComplex(_mreal + 1, _mimage + 1);
	}

	// 后置递增
	CComplex operator++(int) {
		return CComplex(_mreal++, _mimage + 1);
	}

	// +=
	void operator+=(CComplex& comp) {
		_mreal += comp._mreal;
		_mimage += comp._mimage;
	}

	void show() const {
		cout << "复数: " << _mreal << " + j" << _mimage << endl;
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
	// 本质上就是 CComplex comp3 = comp1.operator+(comp2);
	comp3.show();

	CComplex comp4 = comp1 + 20;  // 找一个符合一个整形的构造函数，然后生成临时对象(20 + j0)
	comp4.show();

	// CComplex comp5 = 30 + comp1; 上面的comp1 + 20 => comp1.operator+(20),有顺序要求
	// 因为成员函数的重载，上述的情况也可以用全局函数的重载来实现

	CComplex comp5 = 30 + comp1;  // 成员的不行，就用全局的

	/*
		编译器做对象运算时，会调用对象的运算符重载函数(优先调用成员方法)；如果没有成员方法
		就在全局作用域找合适的运算符重载函数
	*/

	/*
		前置递增：operator++();
		后置递增：operator++(int)
	*/

	comp5.show();
	comp5 = comp1++;
	comp5.show();
	comp5 = ++comp1;

	// 区别前置和后置
	comp5.show();
	cout << "后置递增: ";
	(comp5++).show();
	cout << "前置递增: ";
	(++comp5).show();

	cout << comp5 << " " << comp4 << endl;

	CComplex comp6;
	cin >> comp6;
	comp6.show();

	return 0;
}