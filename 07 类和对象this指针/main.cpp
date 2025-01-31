#include<iostream>

using namespace std;

/*
c++: ��  => ʵ��ĳ�������
ʵ��(���ԣ���Ա��������Ϊ����Ա����)

�಻��ʵ�壬��ʵ��ĳ����������ͣ���ͨ��ʵ�����õ�����ռһ���Ŀռ�

OOP���Ĵ����ԣ����󣬼̳У���װ����̬
�����޶�����public,private,protected
*/

const int NAME_LEN = 20;
class CGoods {
public:  // ���ⲿ�ṩ���еķ�����������˽�е�����
	CGoods(char* name, double price, int amount){
		strcpy_s(_name, name);
		_price = price;
		_amount = amount;
	}

	void setAmount(int amount) {
		_amount = amount;
	}

	const char* getName() { 
		return _name;
	}

private:  // ����һ����˽�е�
	char _name[NAME_LEN];
	double _price;
	int _amount;
};

int main() {
	char name[3] = "12";
	CGoods good1 = { name,3.4, 2 };
	good1.setAmount(20);

	return 0;
}