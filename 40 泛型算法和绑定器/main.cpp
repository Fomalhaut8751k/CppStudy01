#include<iostream>

#include<vector>

#include<algorithm>
#include<functional>  // ������������Ͱ���

using namespace std;

/*  �����㷨
	sort,find, find_if, binary_search, for_each
	�����㷨���ܵĲ�����������
	�����㷨�����Խ��ܺ�������
*/


/* ����
	

*/


class MyGreater {
public:
	bool operator()(int a, int b) {
		return a > b;
	}
};

int main() {
	int arr[] = { 12,4,78,9,21,43,56,52,42,31 };
	vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

	for (auto item : vec) {
		cout << item << " ";
	}cout << endl;

	// ����Ĭ�ϴ�С����,����ͨ����������ʵ�ִӴ�С,ʹ�ÿ�������
	sort(vec.begin(), vec.end()); 
	//sort(vec.begin(), vec.end(), MyGreater())

	for (auto item : vec) {
		cout << item << " ";
	}cout << endl;

	// ���ֲ��ң�����������  ���������ǲ���
	cout << "21���Ԫ���Ƿ����: " << 
		binary_search(vec.begin(), vec.end(), 21) << endl;  // ���뵥������

	// find ���ص�����/�Ҳ�������end(),Ч�ʲ�����֣���ͷ��ʼһ��һ����
	auto it2 = find(vec.begin(), vec.end(), 21);
	cout << "21���Ԫ���Ƿ����: " <<
		(it2 != vec.end()) << endl;

	// �ҵ�һ������48�ģ�
	//auto it3 = find_if(vec.begin(), vec.end(), bind1st(less<int>(), 48));  // ��48��Ϊ��һ������
	auto it4 = find_if(vec.begin(), vec.end(), [](int val)->bool {return val > 27; }); // lambda���ʽ
	//cout << *it3 << endl;
	//vec.insert(it3, 48);

	cout << *it4 << endl;
	vec.insert(it4, 27);

	for (auto item : vec) {
		cout << item << " ";
	}cout << endl;

	// ����������������Ӻ��ʵĺ�������
	for_each(vec.begin(), vec.end(), [](int val)->void {cout << val << " "; }); cout << endl;
	//for_each(vec.begin(), vec.end(), [](int val)->void { val += 1; }); cout << endl;  �޷��޸ģ�
	for_each(vec.begin(), vec.end(), [](int val)->void {
		if (val % 2 == 0) {
			cout << val << " ";
		}  // ���ˣ�ֻ��ӡ����ż��
	}); cout << endl;
	return 0;
}