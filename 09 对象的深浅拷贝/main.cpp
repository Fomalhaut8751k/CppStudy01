#include<iostream>

using namespace std;

// ˳��ջ
class SeqStack {
public:
	// ���캯��
	SeqStack(int size = 10) {
		cout << this << " SeqStack()" << endl;
		_pstack = new int[size];
		_top = -1;
		_size = size;
	}

	// �������캯��
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

	// ��������
	~SeqStack() {
		cout << this << " ~SeqStack()" << endl;
		delete[] _pstack;
		_pstack = nullptr;
	}
	// ��ջ
	void push(int val) {
		if (full())
			resize();
		_pstack[++_top] = val;
	}
	// ��ջ
	void pop() {
		if (empty())
			return;
		--_top;
	}
	// �ж�ջ��
	bool empty() {
		return _top == -1;
	}
	// �ж�ջ��
	bool full() {
		return _top == _size - 1;
	}
	// ����ջ��
	int top() {
		return _pstack[_top];
	}
	void testAddress() {
		cout << _pstack << endl;
	}

private:
	int* _pstack;  // ��̬�������飬�洢˳��ջ��Ԫ��
	int _top;  // ջ��
	int _size;  // �������ݵ��ܴ�С


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

	// �������ֶ��ǿ������캯���ĵ���
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
