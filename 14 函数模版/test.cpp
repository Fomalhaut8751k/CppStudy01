#include<iostream>

using namespace std;

// 函数模板
template<typename T>  
bool compare(T a, T b) { 
	cout << "compare<" << typeid(T).name() << ">" << endl;
	return a > b;
}

// 函数模板特例化
template<>
bool compare(const char* a, const char* b) {
	cout << "compare<const char*>" << endl;
	return strcmp(a, b) > 0;
}

// 普通函数
bool compare(const char* a, const char* b) {
	cout << "normal compare" << endl;
	return strcmp(a, b) > 0;
}