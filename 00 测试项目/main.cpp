#include<iostream>

using namespace std;

#if 0  // 测试1. memcpy遇上拷贝和赋值的正确处理
class inner {
public:
	inner(int size = 3) {
		_ptr = new int[3];
		_size = size;
	}

	inner(const inner& inn) {
		_ptr = new int[3];
		for (int i = 0; i < inn._size; i++) {
			_ptr[i] = inn._ptr[i];
		}
		_size = inn._size;
	}

	~inner() {
		delete[] _ptr;
		_ptr = nullptr;
	}

	void operator=(const inner& inn) {
		if (this == &inn)
			return;
		delete[] _ptr;
		_ptr = new int[inn._size];
		_size = inn._size;
		for (int i = 0; i < inn._size; i++) {
			_ptr[i] = inn._ptr[i];
		}
	}

	int* _ptr;

private:
	
	int _size;
};

class external {
public:
	external(int size = 2) {
		_innptr = new inner[size];
		_size = size;
	}
	//memcpy(_innptr, ext._innptr, sizeof(inner)* ext._size);  // 内存拷贝

	external(const external& ext) {
		_innptr = new inner[ext._size];  // 创建新的内存
		for (int i = 0; i < ext._size; i++) {
			_innptr[i]._ptr[i] = ext._innptr[i]._ptr[i];  // 将值写入
		}
		_size = ext._size;
	}

	~external() {
		delete[] _innptr;
		_innptr = nullptr;
	}

	inner* _innptr;

private:
	
	int _size;
};

int main() {
	inner i1;
	inner i2(i1);

	external e1;
	external e2 = e1;
	cout << "对象e1在堆区上的成员变量的地址：" << e1._innptr->_ptr << endl;
	cout << "对象e2在堆区上的成员变量的地址：" << e2._innptr->_ptr << endl;

	inner i3;
	i3 = i1;

	cout << "对象i1在堆区上的成员变量的地址：" << i1._ptr << endl;
	cout << "对象i3在堆区上的成员变量的地址：" << i3._ptr << endl;
	
	system("pause");

	return 0;
}
#endif

#if 0 // 测试2：空间配置器的使用
// 测试类，用于作为数组元素
class Test {
public:
	// 默认构造
	Test() { cout << "Test()" << endl; }
	// 拷贝构造
	Test(const Test& T) { cout << "Test(const Test& T)" << endl; }
	// 默认析构
	~Test() { cout << "~Test()" << endl; }
};

template<typename T>
class Vector {
public:
	// 默认构造
	Vector(int cappacity = 10) {
		// 只开辟内存，不构造变量
		_first = _alloc.allocate(cappacity);
		_last = _first;  // 尾的下一位为头，则说明没有
		_end = _first + cappacity;
	}

	// 拷贝构造
	Vector(const Vector<T>& vec) {
		int _size = vec._last - vec._first;
		int _cappacity = vec._end - vec._first;
		// 开辟内存
		_first = _alloc.allocate(_cappacity);
		// 构造对象
		for (int i = 0; i < _size; i++) {
			_alloc.construct(_first + i, vec._first[i]);
		}
		_last = vec._last;
		_end = vec._end;
	}

	// 赋值
	Vector<T>& operator=(const Vector<T>& vec) {
		if (this == &vec) {
			return *this;
		}
		// 析构所有有效对象
		for (T* p = _first; p < _last; p++) {
			_alloc.destroy(p);
		}
		// 释放原来的空间
		_alloc.deallocate(_first, _end - _first);
		// 开辟内存
		_first = _alloc.allocate(vec._end - vec._first);
		// 构造对象
		for (int i = 0; i < vec._last - vec._first; i++) {
			_alloc.construct(_first + i, vec._first[i]);
		}
		_last = vec._last;
		_end = vec._end;
	}

	// 析构
	~Vector() {
		// 析构所有有效对象
		for (T* p = _first; p < _last; p++) {
			//system("pause");
			_alloc.destroy(p);
		}
		// 释放原来的空间
		_alloc.deallocate(_first, _end - _first);
		_first = _last = _end = nullptr;
	}

	// 插入
	void push_back(const T& t) {
		if (full()) {
			expand();
		}
		// 构造对象
		_alloc.construct(_last, t);
		_last++;
	}

	// 弹出
	void pop_back() {
		if (empty()) {
			return;
		}
		// 析构对象
		_last--;
		_alloc.destroy(_last);
	}

	// 打印容器信息
	void show(){
		cout << "容器大小(size): " << _last - _first << "\t";
		cout << "容器容量(cappacity): " << _end - _first << endl;
	}


public:
	T* _first;  // 头
	T* _last;  // 有效元素的下一位
	T* _end;  // 尾的下一位
	allocator<T> _alloc;  // 定义空间配置器

	// 判断容器是否满
	bool full() const {
		return _last == _end;
	}

	// 判断容器是否空
	bool empty() const {
		return _first == _last;
	}

	// 扩容
	void expand() {
		int _size = _last - _first;
		int _newcappacity = (_end - _first) * 2;
		// 开辟内存
		T* _newfirst = _alloc.allocate(_newcappacity);
		// 构造对象
		for (int i = 0; i < _size; i++) {
			_alloc.construct(_newfirst + i, _first[i]);
		}
		// 析构原来的对象
		for (T* p = _first; p != _last; p++) {
			_alloc.destroy(p);
		}
		// 释放原内存
		_alloc.deallocate(_first, _size);
		
		_first = _newfirst;
		_last = _first + _size;
		_end = _first + _newcappacity;
	}

};

int main() {
	cout << "----------------------------" << endl;
	Vector<Test> v(3);  // 这里没有Test的构造函数调用，因为只开辟了内存
	cout << "----------------------------" << endl;
	for (int i = 0; i < 5; i++) {
		v.push_back(Test());
		v.show();
	}
	cout << "----------------------------" << endl;
	v.pop_back();
	cout << "----------------------------" << endl;
	v.show();
	return 0;
}

#endif


#if 1

class Test {
public:
	Test(int a = 10, int b = 20):
		_b(b){
		_a = a;
	}

	const int* returnAddress() const{
		return &_a;
	}

	int returnA() {
		return _a;
	}

	int _a;
	const int _b;
};

int main() {
	Test t;
	cout << "成员变量 a = " << t.returnA() << endl;
	//int* p = t.returnAddress();
	//*p = 30;
	cout << "成员变量 a = " << t.returnA() << endl;

	return 0;
}

#endif