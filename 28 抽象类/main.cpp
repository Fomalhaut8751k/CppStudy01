#include<iostream>

using namespace std;

// 抽象类

/*
定义Animal类型的初衷，并不是让Animal抽象某个实体的类型
   1. string _name； 让所有的动物实体类通过继承Animal直接服用该属性
   2. 给所有的派生类保留统一的覆盖/重写接口
*/


class Animal {
public:
	Animal(string name) :_name(name) {}
	//virtual void bark() {}
	virtual void bark() = 0;  // 纯虚函数
protected:
	string _name;
};

class Cat : public Animal {
public:
	Cat(string name) :Animal(name) {}
	void bark() { cout << _name << " bark: miao miao!" << endl; }
};

class Dog : public Animal {
public:
	Dog(string name) :Animal(name) {}
	void bark() { cout << _name << " bark: wang wang!" << endl; }
};

//template<typename T>
//void bark(T animal) {
//	animal.bark();
//}

void bark(Animal* p) {
	p->bark();  // 动态绑定
}




// 汽车的基类
class Car {
public:
	Car(string name) : _name(name) {}
	// 获取汽车剩余油量还能跑的公里数
	double getLeftMiles(double oil){
		// 1L油可以跑x公里 * 油量
		return oil * getMilesPerGallon();
	}
protected:
	string _name;

	virtual double getMilesPerGallon() = 0;
};

class Bnze : public Car {
public:
	Bnze(string name) :Car(name) {}
	double getMilesPerGallon() { return 20.0; }
};

class Audi : public Car {
public:
	Audi(string name) :Car(name) {}
	double getMilesPerGallon() { return 18.0; }
};

class BMW : public Car {
public:
	BMW(string name) :Car(name) {}
	double getMilesPerGallon() { return 19.0; }
};


// 给外部提供一个同一的获取汽车剩余路程数的API
double showCarLeftMiles(Car& car) {
	return car.getLeftMiles(20);
}

int main() {
	/*compare(1, 2);
	compare(1.2, 3.4);*/

	//Cat cat("哈基米");
	//Dog dog("张容赫");

	//bark(&cat);
	//bark(&dog);

	// Animal a;

	Bnze b1("奔驰");
	Audi a1("奥迪");
	BMW b2("宝马");

	cout << showCarLeftMiles(b1) << endl;
	cout << showCarLeftMiles(a1) << endl;
	cout << showCarLeftMiles(b2) << endl;

	return 0;
}