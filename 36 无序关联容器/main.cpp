#include<iostream>

#include<unordered_set>
#include<unordered_map>

#include<set>
#include<map>

/*
* ����������� => ��ʽ��ϣ�� ��ɾ��O(1)
	set: ���� key   map: ӳ��� [key, value]
	unordered_set ���ؼ��ϡ�����洢�ظ��ġ�
	unordered_multiset ���ؼ���
	unordered_map ����ӳ���
	unordered_multimap ����ӳ���

* ����������� => ����� ��ɾ��O(log2n) 2�ǵ���(n�����Ĳ��������ĸ߶�)
	set
	multiset
	map
	multimap

	��ɾ��
	1. ����insert()
	2. ����iterator������find
	3. erase(key), erase(it)
*/

using namespace std;


int main() {

#if 0
	// set
	unordered_set<int> set1;  // ����洢keyֵ
	for (int i = 0; i < 50; ++i) {
		set1.insert(rand() % 20 + 1); // ����Ҫָ����������λ��
	}
	for (auto item : set1) { cout << item << " ";} cout << endl; // ����

	cout << "size: " << set1.size() << endl;  // ��С
	cout << "count for 15: " << set1.count(15) << endl; // ����

	set1.erase(20); // ɾ��Ԫ��20
	for (auto it = set1.begin(); it != set1.end(); ++it) {
		if (*it == 30) {
			set1.erase(it); // Ҳ���Դ��������
			break;
		}
	}
	for (auto item : set1) { cout << item << " "; } cout << endl;

	auto it1 = set1.find(20); // ����20���Ԫ�أ��Ҳ����򷵻�set1.end()
	cout << (it1 == set1.end()) << endl;
#endif

#if 0
	// map����ֵ��pair first -> key, second -> key
	unordered_map<int, string> map1;
	// ���ֲ��뷽��
	map1.insert(pair<int, string>(3111, "ɳ��"));
	map1.insert(make_pair(5003, "���籭"));
	map1.insert({ 1876, "�ǹ�" });
	// multi�����key�����ظ�������
	for (auto item : map1) {
		cout << item.second << ": " << item.first << endl;
	}
	cout << map1[1876] << endl;  // ͨ��keyȡvalue
	cout << map1[1001] << endl; // ���key�����ڻᴴ����value��ʹ��Ĭ��ֵ��string����""
	map1[1002] = "���Ͱ���";  // �޸ģ������ھʹ���

	map1.erase(3111);  // ͨ��keyɾ��
	for (auto item : map1) {
		cout << item.second << ": " << item.first << endl;
	}

	auto it = map1.find(1002);  // ����鲻���ͷ���map1.end()

#endif

#if 0
	// 1. ���������ݲ��ظ���ͳ����Щ�ظ��ˣ��ظ��˶��ٴ�
	const int ARR_LEN = 1000;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i) {
		arr[i] = rand() % 100 + 1;
	}��
	unordered_map<int, int> map1;
	for (int i = 0; i < ARR_LEN; ++i) {
		map1[arr[i]] += 1;  // ���i���key�����ڣ���ʹ��Ĭ��ֵ0,  ������+1���������......
	}
	cout << "����" << " ���ִ���" << endl;
	for (const auto& item : map1) {
		cout << item.first << ":\t" << item.second << endl;
	}
#endif

#if 1
	// 2. ���������ݲ��ظ���ȥ�ظ�
	const int ARR_LEN = 1000;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i) {
		arr[i] = rand() % 100 + 1;
	}
	unordered_set<int> set1;
	for (int i = 0; i < ARR_LEN; ++i) {
		set1.insert(arr[i]);
	}
	for (const auto& item : set1) {
		cout << item << " ";
	}cout << endl;
#endif

	return 0;
}