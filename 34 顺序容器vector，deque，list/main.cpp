#include<iostream>
#include<vector>
#include<deque>
#include<list>

#include<algorithm>

using namespace std;

template<typename T>
void show(T item) {
	cout << item << " ";
}

int main() {
	/* ######################################################################################
		vector: ��������
		�ײ����ݽṹ����̬���ٵ����飬ÿ����ԭ���ռ��С��2����������
	   ######################################################################################
	*/
	vector<int> vec;
	// β��
	for (int i = 0; i < 10; i++) {
		vec.push_back(rand() % 100 + 1); // ĩβ���Ԫ��O(1)�����ܵ�������
	}

	// ����
	vec.insert(vec.begin(), 3); // O(n)��Ų������Ԫ�أ����ܵ�������

	// βɾ
	vec.pop_back();  // O(1)

	// ɾ��
	vec.erase(vec.begin());  // O(n)��Ų������Ԫ��

	// ��ѯ
	cout << vec[0] << endl;  // []�±���������vec[index]�� O(1)
	for (auto it = vec.begin(); it != vec.end(); ++it) {  
		cout << *it << " "; // ͨ��������������
	}cout << endl;
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;  // �﷨��for_each()

	//��������ɾ��
	/*
		�������������������ɾ������(insert/erase)��һ��Ҫ���µ������������һ��insert����erase���
		��������ʧЧ��
	*/
	auto it = vec.begin();
	while (it != vec.end()) {
		auto itNew = vec.insert(it + 1, *it - 1);
		it = ++itNew;
	}
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;

	it = vec.begin();
	while (it != vec.end()) {
		if (*it % 2 == 1) {
			it = vec.erase(it);
		}
		else {
			++it;
		}
	}
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;

	// ���÷���
	cout << "size of vec: " << vec.size() << endl;  // ������ЧԪ�ظ���
	cout << "capacity of vec: " << vec.capacity() << endl;  // ����������С
	cout << "empty of no?: " << vec.empty() << endl;  // �Ƿ�Ϊ��
	vec.reserve(30);  // Ԥ���ռ�,ֻ�ı�����������̫Ƶ���ǲ��õģ�����Ԥ������
	vec.resize(12);  // ��0����ЧԪ�����룬����size=12�����ܵ�������

	//cout << "size of vec: " << vec.size() << endl;  // ������ЧԪ�ظ���
	//cout << "capacity of vec: " << vec.capacity() << endl;  // ����������С
	//for_each(vec.begin(), vec.end(), show<int>); cout << endl;

	vector<int> vec2 = { 1,2,3,4,5 };
	swap(vec2, vec);  // ������������
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;
	for_each(vec2.begin(), vec2.end(), show<int>); cout << endl;

	cout << "-------------------------------------------------------------------" << endl;


	/* ######################################################################################
		deque: ˫�˶�������
		�ײ����ݽṹ����̬���ٵĶ�ά���飬һά�����2��ʼ����2���ķ�ʽ�������ݣ�ÿ�����ݺ�ԭ
		���ڶ�ά�����飬���µĵ�һά���±�oldsize/2��ʼ��ţ����¶�Ԥ����ͬ�Ŀ��У�����֧��deque
		����βԪ�����
	   ######################################################################################
	*/
	deque<int> deq;
	for (int i = 0; i < 5; ++i) {
		deq.push_back(rand() % 20);  // ��β�����Ԫ��O(1)
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	for (int i = 0; i < 5; ++i) {
		deq.push_front(rand() % 20);  // ��ͷ�����Ԫ��O(1)
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	deq.insert(deq.begin(), 5003); // ָ��λ�ò���O(n)
	for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	deq.pop_back(); // ��β��ɾ��O(1)

	deq.pop_front(); // ��ͷ��ɾ��O(1)

	deq.erase(--deq.end());  // ָ��λ��ɽ��O(n)
	for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	auto it2 = deq.begin();
	while (it2 != deq.end()) {
		if ((*it2 % 2) == 1) {
			auto itNew = deq.insert(it2 + 1, *it2 - 1);
			it2 = ++itNew;
		}
		else {
			++it2;
		}
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	it2 = deq.begin();
	while (it2 != deq.end()) {
		it2 = ++deq.erase(it2);
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	// ��ѯʲô�ĺ�vectorһ��
	cout << "-------------------------------------------------------------------" << endl;


	/* ######################################################################################
		list: ��������
		�ײ����ݽṹ��˫��ѭ������
	   ######################################################################################
	*/
	list<int> mylist;
	for (int i = 0; i < 5; ++i) {
		mylist.push_back(i);
		mylist.push_front(4 - i);
	}for_each(mylist.begin(), mylist.end(), show<int>); cout << endl;

	mylist.insert(mylist.begin(), 20); // ���������O(1)��Ϊ���漰Ԫ�ص�Ų��������ѯ����Ӧλ����O(n)
	mylist.erase(--mylist.end());  // ɾ��O(n)?

	mylist.pop_back();  // βɾO(1)
	mylist.pop_front();  // ͷɾO(1)
	for_each(mylist.begin(), mylist.end(), show<int>); cout << endl;

	//ͬ���ĵ�����ʧЧ����


	system("pause");
	return 0;
}