#include<iostream>

using namespace std;

// 顺序栈
class SeqStack {
public:
	// 构造函数
	SeqStack(int size = 10) {
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}
	// 析构函数
	~SeqStack() {
		cout << this << " ~SeqStack()" << endl;
		delete[] _pstack;
		_pstack = nullptr;
	}
	// 入栈
	void push(int val) {
		if (full())
			resize();
		_pstack[++_top] = val;
	}
	// 出栈
	void pop() {
		if (empty())
			return;
		--_top;
	}
	// 判断栈空
	bool empty() {
		return _top == -1;
	}
	// 判断栈满
	bool full() {
		return _top == _size - 1;
	}
	// 返回栈顶
	int top() {
		return _pstack[_top];
	}

private:
	int* _pstack;  // 动态开辟数组，存储顺序栈的元素
	int _top;  // 栈顶
	int _size;  // 数组扩容的总大小


	void resize() {
		int* ptmp = new int[_size * 2];
		for (int i = 0; i < _size; i++) {
			ptmp[i] = _pstack[i];
		}
		delete[] _pstack;
		_pstack = ptmp;
		_size *= 2;
	}
};


int main() {
	// 开辟内存，然后调用构造函数
	SeqStack s;
	for (int i = 0; i < 15; i++) {
		s.push(rand() % 100);
	}
	while (!s.empty()) {
		cout << s.top() << " ";
		s.pop();
	}
	return 0;
}
