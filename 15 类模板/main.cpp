#include<iostream>

using namespace std;

template<typename T>
class SeqStack {
public:
	// 构造和析构不用加<T>,其他要用到的需要加上<T>
	SeqStack(int size = 10):
		_top(-1),
		_size(size),
		_pstack(new T[size]){
	}

	SeqStack(const SeqStack<T>& seq) {
		_pstack = new T[seq._size];
		for (int i = 0; i <= seq._top; i++) {
			// T可能是个对象，不能使用memcpy
			_pstack[i] = seq._pstack[i];
		}
		_size = seq._size;
		_top = seq._top;
	}

	SeqStack<T>& operator=(const SeqStack<T>& seq) {
		if (this == &seq) {
			return *this;
		}
		delete[] _pstack;
		_pstack = new T[seq._size];
		for (int i = 0; i <= seq._top; i++) {
			_pstack[i] = seq._pstack[i];
		}
		_size = seq._size;
		_top = seq._top;
	}

	bool full() const {
		return _top + 1 == _size;
	}

	bool empty() const {
		return _top == -1;
	}

	void resize() {
		int _newsize = 2 * _size;
		T* _ptmp = new T[_newsize];
		for (int i = 0; i <= _top; i++) {
			_ptmp[i] = _pstack[i];
		}
		delete[] _pstack;
		_pstack = _ptmp;
		_size = _newsize;
	}

	void push(const T& val) {
		if (full())
			resize();
		_pstack[++_top] = val;
	}

	void pop() {
		if (empty())
			return;
		_top--;
	}

	void show(){
		for (int i = 0; i <= _top; i++) {
			cout << _pstack[i] << " " ;
		}cout << endl;
	}

	T top() const{
		if (empty())
			throw "stack is empty";
		return _pstack[_top];
	}

	~SeqStack() {
		delete[] _pstack;
		_pstack = nullptr;
	}

private:
	T* _pstack;
	int _top;
	int _size;
};


template<typename T>
class vector {
public:
	vector(int size = 10) :
		_first(new T[size]),
		_last(_first),
		_end(_first + size){
	}

	~vector() {
		delete[] _first;
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& vec) {
		_first(new T[vec._end - vec._fisrt]);
		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			_first[i] = vec._first[i];
		}
	}

	vector<T>& operator=(const vector<T>& vec) {
		if (this == &vec)
			return *this;
		delete[] _first;
		_first(new T[vec._end - vec._fisrt]);
		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			_first[i] = vec._first[i];
		}
		return *this;
	}

	void push_back(const T& val) {
		if (full())
			expand();
		*_last++ = val;
	}

	void pop_back() {
		if (empty())
			return;
		_last--;
	}

	bool full() const {
		return _last == _end;
	}

	bool empty() const {
		return _last == _first;
	}

	T back() const {
		if (empty())
			throw "vector is empty";
		return *(_last - 1);
	}

	void expand() {
		int newsize = (_end - _first) * 2;
		int len = _last - _first;
		T* _newfirst = new T[newsize];

		for (int i = 0; i < len; i++) {
			_newfirst[i] = _first[i];
		}

		delete[] _first;
		_first = _newfirst;
		_last = _first + len;
		_end = _first + newsize;
	}

private:
	T* _first;  // 指向数组起始的位置
	T* _last;  // 指向数组中有效元素的后继位置
	T* _end;  // 指向数组空间的后继位置
};

int main() {

	SeqStack<int> s;
	for (int i = 0; i < 10; i++) {
		s.push(rand() % 100);
	}
	s.show();


	vector<int> v;
	for (int i = 0; i < 20; i++) {
		v.push_back(rand() % 100);
	}
	while (!v.empty()) {
		cout << v.back() << " ";
		v.pop_back();
	}cout << endl;


	return 0;
}