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
	// �������ڵ�ǰ���£��ͻ����ȴ�������ʹʵ�ζ���double
	

	cout << sum(10, 20) << endl;

	return 0;

}

//// ȫ��������;ֲ�������
//int data = 20;
//cout << data << endl;  // ����ͬһ���������µ�
//cout << ::data << endl;  // ����ȫ���������µ�
//
//// һ��������ܷ��庯���������ͣ����������