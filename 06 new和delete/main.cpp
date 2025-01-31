#include<iostream>

using namespace std;

int main() {
	// c语言的内存开辟方法
	int* p = (int*)malloc(sizeof(int));
	if (p == nullptr) {
		return -1;
	}
	*p = 20;
	free(p);

	int* q = (int*)malloc(sizeof(int) * 20);
	if (q == nullptr) {
		return -1;
	}
	free(q);

	// c++的内存开辟方法
	int* p1 = new int(20);  // new不仅可以开辟，还可以初始化
	delete p1;
	// int* q1 = new int[20];  // 只开辟不初始化
	int* q1 = new int[20]();  // 初始化为0
	delete[] q1;

	// new的种类？
	int* p2 = new int(20);
	int* p3 = new (nothrow) int;  // 不抛出异常，和malloc一样用nullptr去判断
	const int* p3 = new const int(40);

	int data = 0;
	int* p4 = new(&data) int(50);  // 在指定的内存上开辟
	cout << data << endl;   // 输出50

	return 0;
}