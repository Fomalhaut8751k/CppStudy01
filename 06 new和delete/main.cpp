#include<iostream>

using namespace std;

int main() {
	// c���Ե��ڴ濪�ٷ���
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

	// c++���ڴ濪�ٷ���
	int* p1 = new int(20);  // new�������Կ��٣������Գ�ʼ��
	delete p1;
	// int* q1 = new int[20];  // ֻ���ٲ���ʼ��
	int* q1 = new int[20]();  // ��ʼ��Ϊ0
	delete[] q1;

	// new�����ࣿ
	int* p2 = new int(20);
	int* p3 = new (nothrow) int;  // ���׳��쳣����mallocһ����nullptrȥ�ж�
	const int* p3 = new const int(40);

	int data = 0;
	int* p4 = new(&data) int(50);  // ��ָ�����ڴ��Ͽ���
	cout << data << endl;   // ���50

	return 0;
}