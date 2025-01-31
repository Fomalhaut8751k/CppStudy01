#include<iostream>
//#include "pc.c"

using namespace std;

int data = 10; 

//int sum(int a, int b) {
//	return a + b;
//}
//
//double sum(double a, double b) {
//	return a + b;
//}


//extern "C" {
//	int sum(int a, int b);
//}

#ifdef __cplusplus
extern "C" {
#endif
	int sum(int a, int b) {
		return a + b;
	}
#ifdef __cplusplus
}
#endif

int main() {
	// 声明放在当前域下，就会优先触发，即使实参都是double
	

	cout << sum(10, 20) << endl;

	return 0;

}

//// 全局作用域和局部作用域
//int data = 20;
//cout << data << endl;  // 优先同一个作用域下的
//cout << ::data << endl;  // 访问全局作用域下的
//
//// 一般情况下能分清函数重载类型，但是如果：