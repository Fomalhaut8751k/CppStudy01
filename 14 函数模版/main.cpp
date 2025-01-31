#include<iostream>

using namespace std;

// c++函数模板
/*
	模版的意义：对类型也可以进行参数化。
	函数模板是无法编译的，因为不知道参数类型，在调用点进行实例化
*/

template<typename T>  // 定义一个模板参数列表
bool compare(T a, T b);

/*
在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
bool compare<int>(int a, int b) {  
	return a > b.
}

bool compare<double>(double a, double b) {
	return a > b.
}
这些实例化出来的叫做模板函数

*/

// 针对compare函数模板，提供const char* 类型的特例化版本
template<>
bool compare(const char* a, const char* b);

// 普通函数
bool compare(const char* a, const char* b);

// 函数模板，模板的特例化，非模板(普通)函数不是重载关系

template<typename T, int SIZE>
void show(T a);

template<typename T, char s>
void show2(T a);

int main() {

	// cout << compare<int>(10, 20) << endl;  // 函数模板加具体类型才是具体函数

	// cout << compare(10, 20) << endl;  // 即使不传入具体类型，也可以根据用户传入的实参类型
	// 进行推导，即模板的实参推演
	// 某个类型实例化的模板产生的函数只产生一份：
	// compare<int>(10, 20)第一次使用int类型，产生一份
	// compare(10, 20)实参推演发现也是int，就不会产生，使用之前的

	// cout << compare<int>(10, 9.5) << endl;  // 类型转化
	// cout << compare(10, 9.5) << endl; 无法进行实参推演，找不到对应的模板

	// cout << compare("aaa", "bbb") << endl;  // T = const char*
	// 但是比较的是两者的地址，我们希望是按ascii进行比较，理论上应该用strcmp()
	// 模板的特例化(专用化)
	
	// 如果存在模板的特例化和普通函数，会优先调用普通函数
	compare("aaa", "bbb");  // 调用普通
	compare<const char*>("aaa", "bbb");  // 调用特例化

	// 模板代码不能在一个文件中定义，在另一个文件中使用的。模板代码调用之前，一定要看到
	// 模板定义的地方，这样的话，模板才能够进行正常的实例化，产生能够被编译器编译的代码
	// 所以一般模板代码都是放在头文件当中的，然后在源文件当中直接进行#include包含
	show<int, 4>(3);
	show2<int, 'a'>(3);

	return 0;
}

// 非类型参数 
template<typename T, int SIZE>
void show(T a) {
	for (int i = 0; i < SIZE; i++) {
		cout << a << endl;
		a++;
	}
}

template<typename T, char s>
void show2(T a) {
	cout << a << ": " << s << endl;
}

