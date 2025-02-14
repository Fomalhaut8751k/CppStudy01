#include<iostream>

using namespace std;

// ������

/*
����Animal���͵ĳ��ԣ���������Animal����ĳ��ʵ�������
   1. string _name�� �����еĶ���ʵ����ͨ���̳�Animalֱ�ӷ��ø�����
   2. �����е������ౣ��ͳһ�ĸ���/��д�ӿ�
*/


class Animal {
public:
	Animal(string name) :_name(name) {}
	//virtual void bark() {}
	virtual void bark() = 0;  // ���麯��
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
	p->bark();  // ��̬��
}




// �����Ļ���
class Car {
public:
	Car(string name) : _name(name) {}
	// ��ȡ����ʣ�����������ܵĹ�����
	double getLeftMiles(double oil){
		// 1L�Ϳ�����x���� * ����
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


// ���ⲿ�ṩһ��ͬһ�Ļ�ȡ����ʣ��·������API
double showCarLeftMiles(Car& car) {
	return car.getLeftMiles(20);
}

int main() {
	/*compare(1, 2);
	compare(1.2, 3.4);*/

	//Cat cat("������");
	//Dog dog("���ݺ�");

	//bark(&cat);
	//bark(&dog);

	// Animal a;

	Bnze b1("����");
	Audi a1("�µ�");
	BMW b2("����");

	cout << showCarLeftMiles(b1) << endl;
	cout << showCarLeftMiles(a1) << endl;
	cout << showCarLeftMiles(b2) << endl;

	return 0;
}