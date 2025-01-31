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
	// �����ڴ棬Ȼ����ù��캯��
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
