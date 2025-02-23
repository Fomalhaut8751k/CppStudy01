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
		for (T* p = _first; p != _last; ++p) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& vec) {
		//_first(new T[vec._end - vec._fisrt]);
		int size = vec._end - vec._first;
		_first = _allocator.allocate(size);

		int len = vec._last - vec._first;
	
		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // 在指定的堆内存上创建变量
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& vec) {
		if (this == &vec)
			return *this;
		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存 
		
		int size = vec._end - vec._first;
		_first = _allocator.allocate(size);

		int len = vec._last - vec._first;

		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // 在指定的堆内存上创建变量
		}
		_last = _first + len;
		_end = _first + size;
		return *this;
	}

	void push_back(const T& vec) {
		if (full())
			expand();
		//verify(_last - 1, _last);  // 检查一下是否有效
		//*_last++ = vec;
		_allocator.construct(_last, vec);
		_last++;
	}

	void pop_back() {
		if (empty())
			return;
		verify(_last - 1, _last);
		--_last;
		_allocator.destroy(_last);
	}

	T back() const {
		if (empty())
			throw "vector is empty";
		return *(_last - 1);
	}

	void show() const{
		for (int* p = _first; p != _last; p++) {
			cout << *p << " ";
		}cout << endl;
	}

	bool full() const { return _last == _end; }
	bool empty() const { return _last == _first; }
	int size() const { return _last - _first; }

	T operator[](int index) {
		if (index < 0 || index >= size()) {
			throw "OutOfRangeException";
		}
		return _first[index];
	}

	class iterator {
	public:
		friend class vector<T, Alloc>;
		iterator(vector<T,Alloc>* pvec, T* ptr = nullptr) 
			:_ptr(ptr), _pVec(pvec){
			Iterator_Base* itb = 
				new Iterator_Base(this, _pVec->_head._next);  
			_pVec->_head._next = itb;
		}
		// !=  必须有效，且容器类型一致
		bool operator!=(const iterator& it) const{
			if (_pVec == nullptr || _pVec != it._pVec) {  
				throw "iterator incompatable!";
			}
			//cout << (_ptr == nullptr) << " " << (it._ptr == nullptr) << endl;
			return _ptr != it._ptr;
		}
		// 前置递增
		//iterator& operator++() {
		//	if (_pVec == nullptr) {  // 必须有效
		//		throw "iterator invalid!";
		//	}
		//	++_ptr;
		//	return *this;
		//}
		void operator++() {
			_ptr++;
		}
		// 解引用
		T& operator*() {
			//if (_pVec == nullptr) {  // 必须有效
			//	throw "iterator invalid!";
			//}
			return *_ptr;
		}
	private:
		T* _ptr;
		vector<T, Alloc>* _pVec;  // 当前迭代器是哪个容器的一些
	};

	iterator begin() { return iterator(this, _first); }
	iterator end() { return iterator(this, _last); }

	// 检查迭代器是否失效
	void verify(T* first, T* last) {
		Iterator_Base* pre = &this->_head;     // 头
		Iterator_Base* it = this->_head._next;  // 第一个
		while (it != nullptr) {  // 遍历链表
			if (it->_cur->_ptr > first && it->_cur->_ptr <= last) {
				// 迭代器失效，把iterator持有的容器指针置为nullptr
				it->_cur->_pVec = nullptr;
				// 删除当前迭代器节点，继续判断后面的迭代器节点是否失效
				pre->_next = it->_next;
				delete it;
				it = pre->_next;
			}
			else {
				pre = it;
				it = it->_next;
			}
		}
	}

	// 自定义vector容器insert方法的实现
	iterator insert(iterator it, const T& val) {
		// 不考虑扩容，以及it._ptr的合法性
		verify(it._ptr - 1, _last);
		T* p = _last;
		while(p > it._ptr){
			_allocator.construct(p, *(p-1));  // 在当前位置p构造一个值为*(p-1)的新对象
			_allocator.destroy(p - 1);
			p--;
		}
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);  // 新的迭代器
	}

	// 自定义vector容器erase方法的实现
	iterator erase(iterator it) {
		verify(it._ptr - 1, _last);
		T* p = it._ptr;
		while (p < _last - 1){
			_allocator.destroy(p);
			_allocator.construct(p, *(p + 1));  
			++p;
		}
		_allocator.destroy(p);
		_last--;
		return iterator(this, it._ptr);
	}

private:
	T* _first;  // 指向数组起始的位置
	T* _last;  // 指向数组中有效元素的后继位置
	T* _end;  // 指向数组空间的后继位置
	Alloc _allocator;  // 定义空间配置器

	// 容器迭代器失效增加代码
	struct Iterator_Base {  // 一个链表结点，把所有迭代器记录下来
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c), _next(n){}
		iterator* _cur;  // 维护一个指向某个迭代器的指针
		Iterator_Base* _next;  // 下一个Iterator_Base
	};

	Iterator_Base _head;

	void expand() {
		int size = _end - _first;
		//T* _newfirst = new T[newsize];
		T* ptmp = _allocator.allocate(2 * size);

		for (int i = 0; i < size; ++i) {
			//_newfirst[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}

		//delete[] _first;
		for (T* p = _first; p != _last; ++p) {
			_allocator.destroy(p); // 把_first指针指向的数组的有效元素进行析构操作
		}
		_allocator.deallocate(_first);  // 释放堆上的数组内存 

		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}
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

#if 0
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

#endif
	vector<int> vec(200);
	for (int i = 0; i < 20; i++) {
		vec.push_back(rand() % 100 + 1);
	}
	/*auto it1 = vec.end();
	vec.pop_back();
	auto it2 = vec.end();
	cout << (it1 != it2) << endl;*/

	auto it = vec.begin();
	for (; it != vec.end(); ++it) {
		it = vec.insert(it, *it - 1); 
		++it;
	}

	for (int v : vec) {
		cout << v << " ";
	}

	return 0;
}