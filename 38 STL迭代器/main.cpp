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

	// ��ͨ���������iterator���ӵ�һ�����ʵ����һ��
	vector<int>::iterator it = vec.begin(); 
	for (; it != vec.end(); ++it) {
		cout << *it << " ";
	}cout << endl;
	*(--it) = 5003;  // �������޸�
	for_each(vec.begin(), vec.end(), pdc<int>);

	pdc("HelloWorld"); cout << endl;

	// ���������ε�����const_iterator��ֻ�ܶ�����д
	vector<int>::const_iterator it1 = vec.begin();  // const_iterator�ǻ��࣬iterator�������࣬���Կ��Խ���
	cout << *it1 << endl;
	// *it1 = 20;  // �����޸�

	// ���������reverse_iterator
	vector<int>::reverse_iterator rit1 = vec.rbegin();  // rbegin()�������һ����rend()�෴
	for (; rit1 != vec.rend(); ++rit1) {
		cout << *rit1 << " ";
	}cout << endl;
	*(--rit1) = 3111;  // --�ǻ�ȥ
	for_each(vec.begin(), vec.end(), pdc<int>);

	// ������������const_reverse_iterator
	vector<int>::const_reverse_iterator crit1 = vec.rbegin();
	// *crit1 = 20; �����޸�
	
	return 0;
}