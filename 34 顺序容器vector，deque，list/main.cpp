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
		vector: 向量容器
		底层数据结构：动态开辟的数组，每次以原来空间大小的2倍进行扩容
	   ######################################################################################
	*/
	vector<int> vec;
	// 尾插
	for (int i = 0; i < 10; i++) {
		vec.push_back(rand() % 100 + 1); // 末尾添加元素O(1)，可能导致扩容
	}

	// 插入
	vec.insert(vec.begin(), 3); // O(n)，挪动后面元素，可能导致扩容

	// 尾删
	vec.pop_back();  // O(1)

	// 删除
	vec.erase(vec.begin());  // O(n)，挪动后面元素

	// 查询
	cout << vec[0] << endl;  // []下标的随机访问vec[index]， O(1)
	for (auto it = vec.begin(); it != vec.end(); ++it) {  
		cout << *it << " "; // 通过迭代器来访问
	}cout << endl;
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;  // 语法糖for_each()

	//连续插入删除
	/*
		对容器进行连续插入或删除操作(insert/erase)，一定要更新迭代器，否则第一次insert或者erase完成
		迭代器就失效了
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

	// 常用方法
	cout << "size of vec: " << vec.size() << endl;  // 返回有效元素个数
	cout << "capacity of vec: " << vec.capacity() << endl;  // 返回容器大小
	cout << "empty of no?: " << vec.empty() << endl;  // 是否为空
	vec.reserve(30);  // 预留空间,只改变容量，扩容太频繁是不好的，可以预先扩容
	vec.resize(12);  // 用0当有效元素填入，补到size=12，可能导致扩容

	//cout << "size of vec: " << vec.size() << endl;  // 返回有效元素个数
	//cout << "capacity of vec: " << vec.capacity() << endl;  // 返回容器大小
	//for_each(vec.begin(), vec.end(), show<int>); cout << endl;

	vector<int> vec2 = { 1,2,3,4,5 };
	swap(vec2, vec);  // 两个容器交换
	for_each(vec.begin(), vec.end(), show<int>); cout << endl;
	for_each(vec2.begin(), vec2.end(), show<int>); cout << endl;

	cout << "-------------------------------------------------------------------" << endl;


	/* ######################################################################################
		deque: 双端队列容器
		底层数据结构：动态开辟的二维数组，一维数组从2开始，以2倍的方式进行扩容，每次扩容后，原
		来第二维的数组，从新的第一维的下标oldsize/2开始存放，上下都预留相同的空行，方便支持deque
		的首尾元素添加
	   ######################################################################################
	*/
	deque<int> deq;
	for (int i = 0; i < 5; ++i) {
		deq.push_back(rand() % 20);  // 从尾部添加元素O(1)
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	for (int i = 0; i < 5; ++i) {
		deq.push_front(rand() % 20);  // 从头部添加元素O(1)
	}for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	deq.insert(deq.begin(), 5003); // 指定位置插入O(n)
	for_each(deq.begin(), deq.end(), show<int>); cout << endl;

	deq.pop_back(); // 从尾部删除O(1)

	deq.pop_front(); // 从头部删除O(1)

	deq.erase(--deq.end());  // 指定位置山粗O(n)
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

	// 查询什么的和vector一样
	cout << "-------------------------------------------------------------------" << endl;


	/* ######################################################################################
		list: 链表容器
		底层数据结构：双向循环链表
	   ######################################################################################
	*/
	list<int> mylist;
	for (int i = 0; i < 5; ++i) {
		mylist.push_back(i);
		mylist.push_front(4 - i);
	}for_each(mylist.begin(), mylist.end(), show<int>); cout << endl;

	mylist.insert(mylist.begin(), 20); // 本身插入是O(1)因为不涉及元素的挪动，但查询到对应位置是O(n)
	mylist.erase(--mylist.end());  // 删除O(n)?

	mylist.pop_back();  // 尾删O(1)
	mylist.pop_front();  // 头删O(1)
	for_each(mylist.begin(), mylist.end(), show<int>); cout << endl;

	//同样的迭代器失效问题


	system("pause");
	return 0;
}