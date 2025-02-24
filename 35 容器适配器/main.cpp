#include<iostream>
#include<deque>

#include<stack>
#include<queue>

using namespace std;

/*
	标准容器 - 容器适配器
	1. 适配器底层没有自己的数据结构，它是另外一个容器的封装，
	   它的方法，全部由底层依赖的容器实现的
	2. 没有实现自己的迭代器
*/
template<typename T, typename Container=deque<T>>
class Stack {
public:
	void push(const T& val) { con.push_back(val); }
	void pop() { con.pop_back();  }
	T top() const { return con.back(); }
private:
	Container con;
};

/*
*	stack:
	push入栈，pop出栈，top查看栈顶元素，empty判空，size元素个数
	依赖于deque

	queue:
	push入队，pop出队，front查看队头元素，back查看队尾元素，empty判空，size元素个数
	依赖于deque

	priority_queue:
	push入队，pop出队，top查看队头元素，empty判空，size元素个数
	依赖于vector
*/

int main() {
	stack<int> s1;
	queue<int> q1;
	priority_queue<int> p1;

	for (int i = 0; i < 20; ++i) {
		int temp = rand() % 100 + 1;
		s1.push(temp);
		q1.push(temp);
		p1.push(temp);
	}
	//cout << s1.size() << endl;
	cout << "stack: ";
	while (!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}cout << endl;

	cout << "queue: ";
	while (!q1.empty()) {
		cout << q1.front() << " ";
		q1.pop();
	}cout << endl;

	cout << "priority_queue: ";
	while (!p1.empty()) {
		cout << p1.top() << " ";
		p1.pop();  // 谁越大，优先级越大，越先出列
	}cout << endl;

	return 0;
}