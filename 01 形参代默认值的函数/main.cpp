#include<iostream>
//#include "pch.h"

using namespace std;
// ѹջ��Ĭ��ֵλ������
// Ч������

int sum(int a = 10, int b = 20);


int main() {

	int a = 10;
	int b = 20;

	//int ret = sum(a, b);
	int ret = sum(a);
	cout << "ret = " << ret << endl;

	ret = sum();
	cout << "ret = " << ret << endl;

	return 0;
}

int sum(int a, int b) {
	return a + b;
}