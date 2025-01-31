#include<iostream>

using namespace std;

void func(int(&ptr)[5]) {
	cout << "helloworld" << endl;
}

int main() {
#if 0
	/*int a = 10;
	int* p = &a;
	int& b = a;

	b = 30;

	int& s = 20;*/

	int array[5] = {};

	int* p = array;  // 指针
	int(*q1)[5] = &array;  // 数组指针
	
	// 定义一个引用变量，来引用array数组
	int(&q2)[5] = array;
#endif
	// 左值引用和右值引用
	//int& a = 10;
	int&& b = 20;
	
	// 写一句代码代码，在内存的0x0018ff44处写一个4字节的10
	int* const &p = (int*)0x0018ff44;

	return 0;
}