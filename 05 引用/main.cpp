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

	int* p = array;  // ָ��
	int(*q1)[5] = &array;  // ����ָ��
	
	// ����һ�����ñ�����������array����
	int(&q2)[5] = array;
#endif
	// ��ֵ���ú���ֵ����
	//int& a = 10;
	int&& b = 20;
	
	// дһ�������룬���ڴ��0x0018ff44��дһ��4�ֽڵ�10
	int* const &p = (int*)0x0018ff44;

	return 0;
}