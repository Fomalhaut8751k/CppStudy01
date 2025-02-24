#include<iostream>

#include<unordered_set>
#include<unordered_map>

#include<set>
#include<map>

/*
* 无序关联容器 => 链式哈希表 增删查O(1)
	set: 集合 key   map: 映射表 [key, value]
	unordered_set 单重集合【不会存储重复的】
	unordered_multiset 多重集合
	unordered_map 单重映射表
	unordered_multimap 多重映射表

* 有序关联容器 => 红黑树 增删查O(log2n) 2是底数(n是树的层数，树的高度)
	set
	multiset
	map
	multimap

	增删查
	1. 增加insert()
	2. 遍历iterator，调用find
	3. erase(key), erase(it)
*/

using namespace std;


int main() {

#if 0
	// set
	unordered_set<int> set1;  // 不会存储key值
	for (int i = 0; i < 50; ++i) {
		set1.insert(rand() % 20 + 1); // 不需要指定迭代器的位置
	}
	for (auto item : set1) { cout << item << " ";} cout << endl; // 遍历

	cout << "size: " << set1.size() << endl;  // 大小
	cout << "count for 15: " << set1.count(15) << endl; // 计数

	set1.erase(20); // 删掉元素20
	for (auto it = set1.begin(); it != set1.end(); ++it) {
		if (*it == 30) {
			set1.erase(it); // 也可以传入迭代器
			break;
		}
	}
	for (auto item : set1) { cout << item << " "; } cout << endl;

	auto it1 = set1.find(20); // 查找20这个元素，找不到则返回set1.end()
	cout << (it1 == set1.end()) << endl;
#endif

#if 0
	// map：键值对pair first -> key, second -> key
	unordered_map<int, string> map1;
	// 多种插入方法
	map1.insert(pair<int, string>(3111, "沙超"));
	map1.insert(make_pair(5003, "世界杯"));
	map1.insert({ 1876, "亚冠" });
	// multi解除了key不能重复的限制
	for (auto item : map1) {
		cout << item.second << ": " << item.first << endl;
	}
	cout << map1[1876] << endl;  // 通过key取value
	cout << map1[1001] << endl; // 如果key不存在会创建，value会使用默认值，string就是""
	map1[1002] = "阿巴阿巴";  // 修改，不存在就创建

	map1.erase(3111);  // 通过key删除
	for (auto item : map1) {
		cout << item.second << ": " << item.first << endl;
	}

	auto it = map1.find(1002);  // 如果查不到就返回map1.end()

#endif

#if 0
	// 1. 处理海量数据查重复，统计哪些重复了，重复了多少次
	const int ARR_LEN = 1000;
	int arr[ARR_LEN] = { 0 };
	for (int i = 0; i < ARR_LEN; ++i) {
		arr[i] = rand() % 100 + 1;
	}，
	unordered_map<int, int> map1;
	for (int i = 0; i < ARR_LEN; ++i) {
		map1[arr[i]] += 1;  // 如果i这个key不存在，这使用默认值0,  创建并+1，如果存在......
	}
	cout << "数字" << " 出现次数" << endl;
	for (const auto& item : map1) {
		cout << item.first << ":\t" << item.second << endl;
	}
#endif

#if 1
	// 2. 处理海量数据查重复，去重复
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