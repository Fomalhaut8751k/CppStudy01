#include<iostream>
#include<deque>

#include<stack>
#include<queue>

using namespace std;

/*
	��׼���� - ����������
	1. �������ײ�û���Լ������ݽṹ����������һ�������ķ�װ��
	   ���ķ�����ȫ���ɵײ�����������ʵ�ֵ�
	2. û��ʵ���Լ��ĵ�����
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
	push��ջ��pop��ջ��top�鿴ջ��Ԫ�أ�empty�пգ�sizeԪ�ظ���
	������deque

	queue:
	push��ӣ�pop���ӣ�front�鿴��ͷԪ�أ�back�鿴��βԪ�أ�empty�пգ�sizeԪ�ظ���
	������deque

	priority_queue:
	push��ӣ�pop���ӣ�top�鿴��ͷԪ�أ�empty�пգ�sizeԪ�ظ���
	������vector
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
		p1.pop();  // ˭Խ�����ȼ�Խ��Խ�ȳ���
	}cout << endl;

	return 0;
}