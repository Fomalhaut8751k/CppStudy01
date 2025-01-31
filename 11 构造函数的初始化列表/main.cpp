#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

// 日期类
class CDate {
public:
	CDate(int y, int m, int d) {
		_year = y;
		_month = m;
		_day = d;
	}

	void show() {
		cout << _year << "::" << _month << "::" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

class CGoods {
public:
	// 没有合适的默认构造函数可用
	CGoods(const char* n, int a, double p, int y, int m, int d)
		:_data(y,m,d),  // 1. 构造函数的初始化列表
		_amount(a), 
		_price(p){  
		// 2. 当前类类型构造函数体
		strcpy(_name, n);
	}

	void show() {
		cout << "name: " << _name << endl;
		cout << "amount: " << _amount << endl;
		cout << "price: " << _price << endl;
	}

private:
	char _name[20];
	int _amount;
	double _price;
	CDate _data;
};


// 对象的成员变量的初始化方式可以在构造函数的初始化列表中指定
// 如果没有指定就默认构造。如果在构造函数初始化列表中指定，成员变量初始化
// 的顺序是按照他们定义的顺序去初始化的，ma先定义，ma先初始化，此时
// mb什么都不是，故ma最终什么都不是
//class Test {
//public:
//	Test(int data = 10) : mb(data), ma(mb) {}  
//	void show() { cout << "ma: " << ma << "\nmb: " << mb << endl; }
//private:
//	int ma;
//	int mb;
//};


int main() {

	CGoods good("商品", 100, 35.0, 2019, 5, 12);
	good.show();

	//Test t;
	//t.show(); 
	return 0;

	return 0;
}