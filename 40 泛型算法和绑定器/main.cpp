#include<iostream>

#include<vector>

#include<algorithm>
#include<functional>  // 包含函数对象和绑定器

using namespace std;

/*  泛型算法
	sort,find, find_if, binary_search, for_each
	泛型算法接受的参数都迭代器
	泛型算法还可以接受函数对象
*/


/* 绑定器
	

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

	// 排序：默认从小到大,可以通过函数对象实现从大到小,使用快速排序
	sort(vec.begin(), vec.end()); 
	//sort(vec.begin(), vec.end(), MyGreater())

	for (auto item : vec) {
		cout << item << " ";
	}cout << endl;

	// 二分查找（有序容器）  返回类型是布尔
	cout << "21这个元素是否存在: " << 
		binary_search(vec.begin(), vec.end(), 21) << endl;  // 必须单调递增

	// find 返回迭代器/找不到就是end(),效率不如二分，从头开始一个一个找
	auto it2 = find(vec.begin(), vec.end(), 21);
	cout << "21这个元素是否存在: " <<
		(it2 != vec.end()) << endl;

	// 找第一个大于48的，
	//auto it3 = find_if(vec.begin(), vec.end(), bind1st(less<int>(), 48));  // 把48绑定为第一个参数
	auto it4 = find_if(vec.begin(), vec.end(), [](int val)->bool {return val > 27; }); // lambda表达式
	//cout << *it3 << endl;
	//vec.insert(it3, 48);

	cout << *it4 << endl;
	vec.insert(it4, 27);

	for (auto item : vec) {
		cout << item << " ";
	}cout << endl;

	// 遍历，可以自行添加合适的函数对象
	for_each(vec.begin(), vec.end(), [](int val)->void {cout << val << " "; }); cout << endl;
	//for_each(vec.begin(), vec.end(), [](int val)->void { val += 1; }); cout << endl;  无法修改？
	for_each(vec.begin(), vec.end(), [](int val)->void {
		if (val % 2 == 0) {
			cout << val << " ";
		}  // 过滤，只打印所有偶数
	}); cout << endl;
	return 0;
}