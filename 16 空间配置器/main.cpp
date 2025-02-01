#include<iostream>

using namespace std;


template<typename T>
class Allocator {
public:
	T* allocate(size_t size) {  // �����ڴ濪��
		return (T*)malloc(size * sizeof(T));
	}

	void deallocate(void* p) {  // �����ڴ��ͷ�
		free(p);
	}

	void construct(T* p, const T& val) {  // ���������
		new (p) T(val);   // ��ָ���Ķ��ڴ��ϴ�������
	}

	void destroy(T* p) {  // �����������
		p->~T();  // ~T()��ʾT���͵���������
	}
};

template<typename T, typename Alloc = Allocator<T>>
class vector {
public:
	// ��Ҫ���ڴ濪�ٺͶ�����ֿ�����
	vector(int size = 10) {
		_first = _allocator.allocate(size); // �ڴ濪��
		_last = _first;
		_end = _first + size;
	}

	// ����������Ч��Ԫ�أ�Ȼ���ͷ�_firstָ��Ķ��ڴ�
	~vector() {
		//delete[] _first;
		for (T* p = _first; p < _last; ++p) {
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ�
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& vec) {
		//_first(new T[vec._end - vec._fisrt]);
		_first = _allocator.allocate(vec._end - vec._first);

		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // ��ָ���Ķ��ڴ��ϴ�������
		}
	}

	vector<T>& operator=(const vector<T>& vec) {
		if (this == &vec)
			return *this;
		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ� 
		
		//_first(new T[vec._end - vec._fisrt]);
		_first = _allocator.allocate(vec._end - vec._first);

		_last = _first + (vec._last - vec._first);
		_end = _first + (vec._end - vec._first);
		for (int i = 0; i < vec._last - vec._first; i++) {
			//_first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // ��ָ���Ķ��ڴ��ϴ�������
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
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ� 

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
		// ǰ�õ���
		iterator& operator++() {
			++_p;
			return *this;
		}
		// ������
		T& operator*() {
			return *_p;
		}
	private:
		T* _p;
	};

	iterator begin() { return iterator(_first); }
	iterator end() { return iterator(_last); }

private:
	T* _first;  // ָ��������ʼ��λ��
	T* _last;  // ָ����������ЧԪ�صĺ��λ��
	T* _end;  // ָ������ռ�ĺ��λ��
	Alloc _allocator;  // ����ռ�������

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
	vector<Test> v;  // ���ǳ�ʼ������δ����κ�Ԫ�أ��Ͱ���size������10��Test����
	/*
		���� _first = new Test[size]�У�new�������ٿռ䣬���ṹ��Test����
		��Ҫ���ڴ濪�ٺͶ�����ֿ���������v��ʱ���ȿ����ڴ档
		�����Ļ���Ӧ�����м�����ЧԪ�ؾ����������������Ǵ���size���������size��
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