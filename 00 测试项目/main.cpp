#include<iostream>

using namespace std;

#if 0  // ����1. memcpy���Ͽ����͸�ֵ����ȷ����
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
	//memcpy(_innptr, ext._innptr, sizeof(inner)* ext._size);  // �ڴ濽��

	external(const external& ext) {
		_innptr = new inner[ext._size];  // �����µ��ڴ�
		for (int i = 0; i < ext._size; i++) {
			_innptr[i]._ptr[i] = ext._innptr[i]._ptr[i];  // ��ֵд��
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
	cout << "����e1�ڶ����ϵĳ�Ա�����ĵ�ַ��" << e1._innptr->_ptr << endl;
	cout << "����e2�ڶ����ϵĳ�Ա�����ĵ�ַ��" << e2._innptr->_ptr << endl;

	inner i3;
	i3 = i1;

	cout << "����i1�ڶ����ϵĳ�Ա�����ĵ�ַ��" << i1._ptr << endl;
	cout << "����i3�ڶ����ϵĳ�Ա�����ĵ�ַ��" << i3._ptr << endl;
	
	system("pause");

	return 0;
}
#endif

#if 0 // ����2���ռ���������ʹ��
// �����࣬������Ϊ����Ԫ��
class Test {
public:
	// Ĭ�Ϲ���
	Test() { cout << "Test()" << endl; }
	// ��������
	Test(const Test& T) { cout << "Test(const Test& T)" << endl; }
	// Ĭ������
	~Test() { cout << "~Test()" << endl; }
};

template<typename T>
class Vector {
public:
	// Ĭ�Ϲ���
	Vector(int cappacity = 10) {
		// ֻ�����ڴ棬���������
		_first = _alloc.allocate(cappacity);
		_last = _first;  // β����һλΪͷ����˵��û��
		_end = _first + cappacity;
	}

	// ��������
	Vector(const Vector<T>& vec) {
		int _size = vec._last - vec._first;
		int _cappacity = vec._end - vec._first;
		// �����ڴ�
		_first = _alloc.allocate(_cappacity);
		// �������
		for (int i = 0; i < _size; i++) {
			_alloc.construct(_first + i, vec._first[i]);
		}
		_last = vec._last;
		_end = vec._end;
	}

	// ��ֵ
	Vector<T>& operator=(const Vector<T>& vec) {
		if (this == &vec) {
			return *this;
		}
		// ����������Ч����
		for (T* p = _first; p < _last; p++) {
			_alloc.destroy(p);
		}
		// �ͷ�ԭ���Ŀռ�
		_alloc.deallocate(_first, _end - _first);
		// �����ڴ�
		_first = _alloc.allocate(vec._end - vec._first);
		// �������
		for (int i = 0; i < vec._last - vec._first; i++) {
			_alloc.construct(_first + i, vec._first[i]);
		}
		_last = vec._last;
		_end = vec._end;
	}

	// ����
	~Vector() {
		// ����������Ч����
		for (T* p = _first; p < _last; p++) {
			//system("pause");
			_alloc.destroy(p);
		}
		// �ͷ�ԭ���Ŀռ�
		_alloc.deallocate(_first, _end - _first);
		_first = _last = _end = nullptr;
	}

	// ����
	void push_back(const T& t) {
		if (full()) {
			expand();
		}
		// �������
		_alloc.construct(_last, t);
		_last++;
	}

	// ����
	void pop_back() {
		if (empty()) {
			return;
		}
		// ��������
		_last--;
		_alloc.destroy(_last);
	}

	// ��ӡ������Ϣ
	void show(){
		cout << "������С(size): " << _last - _first << "\t";
		cout << "��������(cappacity): " << _end - _first << endl;
	}


public:
	T* _first;  // ͷ
	T* _last;  // ��ЧԪ�ص���һλ
	T* _end;  // β����һλ
	allocator<T> _alloc;  // ����ռ�������

	// �ж������Ƿ���
	bool full() const {
		return _last == _end;
	}

	// �ж������Ƿ��
	bool empty() const {
		return _first == _last;
	}

	// ����
	void expand() {
		int _size = _last - _first;
		int _newcappacity = (_end - _first) * 2;
		// �����ڴ�
		T* _newfirst = _alloc.allocate(_newcappacity);
		// �������
		for (int i = 0; i < _size; i++) {
			_alloc.construct(_newfirst + i, _first[i]);
		}
		// ����ԭ���Ķ���
		for (T* p = _first; p != _last; p++) {
			_alloc.destroy(p);
		}
		// �ͷ�ԭ�ڴ�
		_alloc.deallocate(_first, _size);
		
		_first = _newfirst;
		_last = _first + _size;
		_end = _first + _newcappacity;
	}

};

int main() {
	cout << "----------------------------" << endl;
	Vector<Test> v(3);  // ����û��Test�Ĺ��캯�����ã���Ϊֻ�������ڴ�
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
	cout << "��Ա���� a = " << t.returnA() << endl;
	//int* p = t.returnAddress();
	//*p = 30;
	cout << "��Ա���� a = " << t.returnA() << endl;

	return 0;
}

#endif