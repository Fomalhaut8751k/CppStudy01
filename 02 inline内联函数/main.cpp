#include<iostream>
#pragma link 

using namespace std;

inline int sum(int a, int b){
	return a + b;
}

int main() {

	int num1 = 10;
	int num2 = 20;

	int ret = sum(num1, num2);

	cout << "ret=" << ret << endl;

	return 0;
}