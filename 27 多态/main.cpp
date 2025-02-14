#include<iostream>

using namespace std;

// ��̬��̬������������
bool compare(int a, int b) {
	return a > b;
}
bool compare(double a, double b) {
	return a > b;
}

class Animal {
public:
	Animal(string name) :_name(name) {}
	virtual void bark(){}
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
	Dog(string name) :Animal(name){}
	void bark() { cout << _name << " bark: wang wang!" << endl; }
};

//template<typename T>
//void bark(T animal) {
//	animal.bark();
//}

void bark(Animal* p) {
	p->bark();  // ��̬��
}

int main() {
	/*compare(1, 2);
	compare(1.2, 3.4);*/

	Cat cat("������");
	Dog dog("ˮ8888");

	bark(&cat);
	bark(&dog);

	return 0;
}