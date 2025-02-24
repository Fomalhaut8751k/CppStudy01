#include<iostream>

#include<vector>

#include<algorithm>

using namespace std;

template<typename T = string>
void pdc(T item) { cout << item << " "; }

int main() {
	vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100);
	}

	// 普通正向迭代器iterator，从第一个访问到最后一个
	vector<int>::iterator it = vec.begin(); 
	for (; it != vec.end(); ++it) {
		cout << *it << " ";
	}cout << endl;
	*(--it) = 5003;  // 还可以修改
	for_each(vec.begin(), vec.end(), pdc<int>);

	pdc("HelloWorld"); cout << endl;

	// 常量的整形迭代器const_iterator，只能读不能写
	vector<int>::const_iterator it1 = vec.begin();  // const_iterator是基类，iterator是派生类，所以可以接受
	cout << *it1 << endl;
	// *it1 = 20;  // 不可修改

	// 反向迭代器reverse_iterator
	vector<int>::reverse_iterator rit1 = vec.rbegin();  // rbegin()返回最后一个，rend()相反
	for (; rit1 != vec.rend(); ++rit1) {
		cout << *rit1 << " ";
	}cout << endl;
	*(--rit1) = 3111;  // --是回去
	for_each(vec.begin(), vec.end(), pdc<int>);

	// 反向常量迭代器const_reverse_iterator
	vector<int>::const_reverse_iterator crit1 = vec.rbegin();
	// *crit1 = 20; 不可修改
	
	return 0;
}