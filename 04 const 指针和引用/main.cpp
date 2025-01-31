#include<iostream>

using namespace std;

int main() {
#if 0
	int b = 20;
	const int a = b;
	int* p = (int*)&a; *p = 30;
	printf("%d %d %d \n", a, *p, *(&a));  // 30, 30, 30

#endif

#if 0
	// const修饰成为常变量
	int b = 20;
	const int a = 20;
	int c = a;
	int d = b;
	system("pause");

#endif

#if 0
	/*const int a = 10;
	int* p = (int*)&a;*/

	int a = 10;
	int b = 20;
	const int* p1 = &a;
	//*p1 = 20;
	p1 = &b;

	int const* p2 = &a;
	//*p2 = 30;
	p2 = &b;

	int* const p3 = &a;
	*p3 = 40;
	//p3 = b;

	const int* const p4 = &a;
	//*p4 = 20;
	//p4 = &b;

	//对于一个常量
	const int aa = 10;  // 他的值不可以被修改，即const需要修饰*p，因此
	const int* p = &aa;
	// int* const p_ = &aa;是不行的，因为是可以修改p_指向的内容的，与aa冲突

#endif

	
#if 1
	

	//const int b = 20;
	//// int* p1 = &b;  // int* <= const int*  (x) 
	//// const int* p2 = &b;
	//// int* const p3 = &b;  // int* const <= const int*  (x) 
	//int a = 20;
	//int* q = &a;
	//const int* p = q;

	//cout << "a = " << a << "\t*p = " << *p << "\tq = " << *q << endl;


	int a = 10;
	int* q1 = &a;
	const int* p1 = q1;
	cout << p1 << "\n" << q1 << endl;
	a = 20;
	*q1 = 30;

	int b = 10;
	const int* p2 = &b;
	//int* q2 = p2;



#endif
	return 0;
}