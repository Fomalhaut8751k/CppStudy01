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

	// 拷贝构造函数
	SeqStack(const SeqStack& src) {
		cout << this << " SeqStack(const SeqStack& src)" << endl;
		_pstack = new int[src._size];
		
		for (int i = 0; i <= src._top; i++) {
			_pstack[i] = src._pstack[i];
		}
		//memcpy(_pstack, src._pstack, sizeof(int) * (src._top + 1));
		_size = src._size;
		_top = src._top;
	}

	// operator=
	void operator=(const SeqStack& src) {
		cout << this << "Seq(operator=)" << endl;
		if (this == &src)
			return;

		delete[] _pstack;
		_pstack = new int[src._size];
		for (int i = 0; i <= src._top; i++) {
			_pstack[i] = src._pstack[i];
		}
		_size = src._size;
		_top = src._top;
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
	void testAddress() {
		cout << _pstack << endl;
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
	SeqStack s1(10);
	
	for (int i = 0; i < 10; i++) {
		s1.push(rand() % 20);
	}

	// 下面两种都是拷贝构造函数的调用
	SeqStack s2 = s1;

	SeqStack s3;
	s3 = s1;

	while (!s1.empty()) {
		cout << s1.top() << " ";
		s1.pop();
	}cout << endl;

	while (!s2.empty()) {
		cout << s2.top() << " ";
		s2.pop();
	}cout << endl;

	while (!s3.empty()) {
		cout << s3.top() << " ";
		s3.pop();
	}cout << endl;

	system("pause");

	return 0;
}
