#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

// ������
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
	// û�к��ʵ�Ĭ�Ϲ��캯������
	CGoods(const char* n, int a, double p, int y, int m, int d)
		:_data(y,m,d),  // 1. ���캯���ĳ�ʼ���б�
		_amount(a), 
		_price(p){  
		// 2. ��ǰ�����͹��캯����
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


// ����ĳ�Ա�����ĳ�ʼ����ʽ�����ڹ��캯���ĳ�ʼ���б���ָ��
// ���û��ָ����Ĭ�Ϲ��졣����ڹ��캯����ʼ���б���ָ������Ա������ʼ��
// ��˳���ǰ������Ƕ����˳��ȥ��ʼ���ģ�ma�ȶ��壬ma�ȳ�ʼ������ʱ
// mbʲô�����ǣ���ma����ʲô������
//class Test {
//public:
//	Test(int data = 10) : mb(data), ma(mb) {}  
//	void show() { cout << "ma: " << ma << "\nmb: " << mb << endl; }
//private:
//	int ma;
//	int mb;
//};


int main() {

	CGoods good("��Ʒ", 100, 35.0, 2019, 5, 12);
	good.show();

	//Test t;
	//t.show(); 
	return 0;

	return 0;
}