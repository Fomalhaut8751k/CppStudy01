#include<iostream>

using namespace std;

// ����ģ��
template<typename T>  
bool compare(T a, T b) { 
	cout << "compare<" << typeid(T).name() << ">" << endl;
	return a > b;
}

// ����ģ��������
template<>
bool compare(const char* a, const char* b) {
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

// ��ͨ����
bool compare(const char* a, const char* b) {
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}