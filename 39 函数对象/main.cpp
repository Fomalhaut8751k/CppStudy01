#include<iostream>
#include<queue>
#include<vector>

using namespace std;

// 把有operator()小括号运算符重载函数的对象，称作函数对象
// 或者叫做仿函数

//template<typename T>
//bool compare(T a, T b) {
//	return a > b;  // 不够灵活，在实际项目中不能改成大于
//}

// c语言的方法，通过函数指针
//template<typename T>
//bool mygreater(T a, T b) {
//	return a > b;
//}
//
//template<typename T>
//bool myless(T a, T b) {
//	return a < b;
//}
//
//template<typename T, typename Compare>
//bool compare(T a, T b, Compare comp) {
//	return comp(a, b);
//}


// 通过函数对象
template<typename T>
class mygreater {
public:
	bool operator()(T a, T b) {
		return a > b;
	}
};

template<typename T>
class myless {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};

template<typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
	return comp(a, b);
}

int main() {
	// 通过函数指针
	/*cout << compare(10, 20, mygreater<int>) << endl;
	cout << compare(10, 20, myless<int>) << endl;*/
	// 但是通过函数指针调用函数，是没办法内联的，效率很低，因为有函数调用开销
	// 内联是发生在编译阶段的，在编辑阶段无法确定调用哪个函数

	// 通过函数对象调用，可以省略函数的调用开销
	cout << compare(10, 20, mygreater<int>()) << endl;

	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // 小根堆的实现
	MinHeap que2;
	for (int i = 0; i < 10; ++i) {
		que2.push(rand() % 100);
	}
	while (!que2.empty()) {
		cout << que2.top() << " ";
		que2.pop();
	}cout << endl;

	return 0;
}