#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

// 自定义字符串类型
class String {
public:
	// 普通构造函数
	String(const char* str = nullptr) {
		if (str != nullptr) {  // 先判断指针是否为nullptr，nullptr不能给到strlen计算
			m_data = new char[strlen(str) + 1];  // 包含末尾的\0
			strcpy(m_data, str);
		}
		else {
			m_data = new char[1];
			*m_data = '\0';
		}
	}

	// 拷贝构造函数
	String(const String& other) {
		m_data = new char[strlen(other.m_data) + 1];
		/*for (int i = 0; i < strlen(other.m_data); i++) {
			m_data[i] = other.m_data[i];
		}*/
		strcpy(m_data, other.m_data);
	}

	// 析构函数
	~String() {
		delete[] m_data;
		m_data = nullptr;
	}

	// 赋值函数
	String& operator = (const String& other){
		// 为了支持连续赋值，故返回值不为void
		if (this == &other) {
			return *this;
		}
		delete[] m_data;
		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);
		return *this;
	}

	const char* getMData() {
		return m_data;
	}

private:
	char* m_data;  // 用于保存字符串
};


// 循环队列
class Queue {
public:
	// 普通构造函数
	Queue(int size = 20) {
		_pQue = new int[size];
		_size = size;
		_front = _rear = 0;
	}

	// 拷贝构造函数
	Queue(const Queue& q) {
		_pQue = new int[q._size];
		for (int i = q._front; i < q._rear; i = (i + 1) % q._size) {
			_pQue[i] = q._pQue[i];
		}
		_size = q._size;
		_front = q._front;
		_rear = q._rear;
	}
	
	// operator
	Queue& operator=(const Queue& q) {
		if (this == &q) {
			return *this;
		}
		delete[] _pQue;
		_pQue = new int[q._size];
		for (int i = q._front; i < q._rear; i = (i + 1) % q._size) {
			_pQue[i] = q._pQue[i];
		}
		_size = q._size;
		_front = q._front;
		_rear = q._rear;
		return *this;
	}

	// 可以通过如下操作删除默认的拷贝构造和赋值函数，这样直接拷贝构造和赋值就会报错
	// Queue(const Queue& q) = delete;
	// Queue& operator=(const Queue& q) = delete;

	// 析构函数
	~Queue() {
		delete[] _pQue;
		_pQue = nullptr;
	}

	// 入队
	void addQue(int val) {
		if (full())
			resize();
		_pQue[_rear] = val;
		_rear = (_rear + 1) % _size;
	}

	// 出队
	void pop() {
		if (empty())
			return;
		_front = (_front + 1) % _size;
	}

	// 获取队头元素
	int top() {
		return _pQue[_front];
	}

	// 判断队满
	bool full() {
		return (_rear + 1) % _size == _front;
	}

	//
	bool empty() {
		return _front == _rear;
	}

private:
	int* _pQue;  // 申请队列的数组空间
	int _front;  // 指示队头的位置
	int _rear;  // 指示队尾的位置
	int _size;  // 总的大小

	void resize() {
		int* ptmp = new int[2 * _size];
		int index = 0;
		for (int i = _front; i != _rear; i = (i + 1) % _size) {
			ptmp[index++] = _pQue[i];
		}
		delete[] _pQue;
		_pQue = ptmp;
		_front = 0; _rear = index; _size *= 2;
	}
};

int main() {
	String str1("pdchelloworld");
	String str2 = str1;
	String str3;
	str3 = str2 = str1;

	cout << "str1: " << str1.getMData() << endl;
	cout << "str2: " << str2.getMData() << endl;
	cout << "str3: " << str3.getMData() << endl;

	Queue queue;
	for (int i = 0; i < 20; i++) {
		queue.addQue(rand() % 100);
	}

	Queue queue2 = queue;
	Queue queue3;
	queue3 = queue;

	while (!queue.empty()) {
		cout << queue.top() << " ";
		queue.pop();
	}cout << endl;


	return 0;
}