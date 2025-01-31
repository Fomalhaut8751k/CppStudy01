#include<iostream>

using namespace std;

/*
c++: 类  => 实体的抽象类型
实体(属性：成员变量，行为：成员方法)

类不是实体，是实体的抽象数据类型，类通过实例化得到对象，占一定的空间

OOP的四大特性：抽象，继承，封装，多态
访问限定符：public,private,protected
*/

const int NAME_LEN = 20;
class CGoods {
public:  // 给外部提供公有的方法，来访问私有的属性
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

private:  // 属性一般是私有的
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