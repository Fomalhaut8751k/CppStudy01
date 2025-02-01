#include<iostream>

using namespace std;


template<typename T>
class Allocator {
public:
	T* allocate(size_t size) {  // 负责内存开辟
		return (T*)malloc(size * sizeof(T));
	}

	void deallocate(void* p) {  // 负责内存释放
		free(p);
	}

	void construct(T* p, const T& val) {  // 负责对象构造
		new (p) T(val);   // 在指定的堆内存上创建变量
	}

	void destroy(T* p) {  // 负责对象析构
		p->~T();  // ~T()表示T类型的析构函数
	}
};

template<typename T, typename Alloc = Allocator<T>>
class vector {
public:
	// 需要把内存开辟和对象构造分开处理
	vector(int size = 10) {
		_first = _allocator.allocate(size); // 内存开辟
		_last = _first;
		_end = _first + size;
	}

	// 析构容器有效的元素，然后释放_first指向的堆内存
	~vector() {
		//delete[] _first;
		for (T* p = _first; p < _last; ++p) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& vec) {
		//_first(new T[vec._end - vec._fisrt]);
		_first = _allocator.allocate(vec._end - vec._first);

		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // 在指定的堆内存上创建变量
		}
	}

	vector<T>& operator=(const vector<T>& vec) {
		if (this == &vec)
			return *this;
		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存 
		
		//_first(new T[vec._end - vec._fisrt]);
		_first = _allocator.allocate(vec._end - vec._first);

		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			//_first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // 在指定的堆内存上创建变量
		}
		return *this;
	}

	void push_back(const T& vec) {
		if (full())
			expand();
		//*_last++ = vec;
		_allocator.construct(_last, vec);
		_last++;
	}

	void pop_back() {
		if (empty())
			return;
		_last--;
		_allocator.destroy(_last);
	}

	void show() const{
		for (int* p = _first; p != _last; p++) {
			cout << *p << " ";
		}cout << endl;
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
		//T* _newfirst = new T[newsize];
		T* _newfirst = _allocator.allocate(newsize);

		for (int i = 0; i < len; i++) {
			//_newfirst[i] = _first[i];
			_allocator.construct(_newfirst + i, _first[i]);
		}

		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存 

		_first = _newfirst;
		_last = _first + len;
		_end = _first + newsize;
	}

	T operator[](int index) {
		return _first[index];
	}

	class iterator {
	public:
		iterator(T* p = nullptr) 
			:_p(p){
		}
		// !=
		bool operator!=(const iterator& it) const{
			return _p != it._p;
		}
		// 前置递增
		iterator& operator++() {
			++_p;
			return *this;
		}
		// 解引用
		T& operator*() {
			return *_p;
		}
	private:
		T* _p;
	};

	iterator begin() { return iterator(_first); }
	iterator end() { return iterator(_last); }

private:
	T* _first;  // 指向数组起始的位置
	T* _last;  // 指向数组中有效元素的后继位置
	T* _end;  // 指向数组空间的后继位置
	Alloc _allocator;  // 定义空间配置器

	friend int main();
};


class Test {
public:
	Test() { cout << "Test()" << endl; }
	Test(const Test& T) {
		cout << "const Test& ()" << endl; 
	}
	~Test() { cout << "~Test()" << endl; }
};

int main() {

	Test t1, t2, t3;
	cout << "------------------------" << endl;
	vector<Test> v;  // 仅是初始化，还未添加任何元素，就按照size构造了10个Test对象
	/*
		在于 _first = new Test[size]中，new不仅开辟空间，还会构造Test对象。
		需要把内存开辟和对象构造分开处理，创建v的时候先开辟内存。
		析构的话，应该是有几个有效元素就析构几个，而不是创建size个最后析构size个
	*/
	cout << "-------------------------" << endl;
	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);

	cout << "-------------------------" << endl;
	v.pop_back();
	cout << "-------------------------" << endl;

	/*vector<int> vec;
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100);
	}

	for (vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		cout << *it << " ";
	}cout << endl;*/

	return 0;
}