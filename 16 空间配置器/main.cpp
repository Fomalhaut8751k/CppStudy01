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
		for (T* p = _first; p != _last; ++p) {
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ�
		_first = _last = _end = nullptr;
	}

	vector(const vector<T>& vec) {
		//_first(new T[vec._end - vec._fisrt]);
		int size = vec._end - vec._first;
		_first = _allocator.allocate(size);

		int len = vec._last - vec._first;
	
		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // ��ָ���Ķ��ڴ��ϴ�������
		}
		_last = _first + len;
		_end = _first + size;
	}

	vector<T>& operator=(const vector<T>& vec) {
		if (this == &vec)
			return *this;
		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ� 
		
		int size = vec._end - vec._first;
		_first = _allocator.allocate(size);

		int len = vec._last - vec._first;

		for (int i = 0; i < vec._last - vec._first; i++) {
			// _first[i] = vec._first[i];
			_allocator.construct(_first + i, vec._first[i]);  // ��ָ���Ķ��ڴ��ϴ�������
		}
		_last = _first + len;
		_end = _first + size;
		return *this;
	}

	void push_back(const T& vec) {
		if (full())
			expand();
		//verify(_last - 1, _last);  // ���һ���Ƿ���Ч
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
		// !=  ������Ч������������һ��
		bool operator!=(const iterator& it) const{
			if (_pVec == nullptr || _pVec != it._pVec) {  
				throw "iterator incompatable!";
			}
			//cout << (_ptr == nullptr) << " " << (it._ptr == nullptr) << endl;
			return _ptr != it._ptr;
		}
		// ǰ�õ���
		//iterator& operator++() {
		//	if (_pVec == nullptr) {  // ������Ч
		//		throw "iterator invalid!";
		//	}
		//	++_ptr;
		//	return *this;
		//}
		void operator++() {
			_ptr++;
		}
		// ������
		T& operator*() {
			//if (_pVec == nullptr) {  // ������Ч
			//	throw "iterator invalid!";
			//}
			return *_ptr;
		}
	private:
		T* _ptr;
		vector<T, Alloc>* _pVec;  // ��ǰ���������ĸ�������һЩ
	};

	iterator begin() { return iterator(this, _first); }
	iterator end() { return iterator(this, _last); }

	// ���������Ƿ�ʧЧ
	void verify(T* first, T* last) {
		Iterator_Base* pre = &this->_head;     // ͷ
		Iterator_Base* it = this->_head._next;  // ��һ��
		while (it != nullptr) {  // ��������
			if (it->_cur->_ptr > first && it->_cur->_ptr <= last) {
				// ������ʧЧ����iterator���е�����ָ����Ϊnullptr
				it->_cur->_pVec = nullptr;
				// ɾ����ǰ�������ڵ㣬�����жϺ���ĵ������ڵ��Ƿ�ʧЧ
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

	// �Զ���vector����insert������ʵ��
	iterator insert(iterator it, const T& val) {
		// ���������ݣ��Լ�it._ptr�ĺϷ���
		verify(it._ptr - 1, _last);
		T* p = _last;
		while(p > it._ptr){
			_allocator.construct(p, *(p-1));  // �ڵ�ǰλ��p����һ��ֵΪ*(p-1)���¶���
			_allocator.destroy(p - 1);
			p--;
		}
		_allocator.construct(p, val);
		_last++;
		return iterator(this, p);  // �µĵ�����
	}

	// �Զ���vector����erase������ʵ��
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
	T* _first;  // ָ��������ʼ��λ��
	T* _last;  // ָ����������ЧԪ�صĺ��λ��
	T* _end;  // ָ������ռ�ĺ��λ��
	Alloc _allocator;  // ����ռ�������

	// ����������ʧЧ���Ӵ���
	struct Iterator_Base {  // һ�������㣬�����е�������¼����
		Iterator_Base(iterator* c = nullptr, Iterator_Base* n = nullptr)
			:_cur(c), _next(n){}
		iterator* _cur;  // ά��һ��ָ��ĳ����������ָ��
		Iterator_Base* _next;  // ��һ��Iterator_Base
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
			_allocator.destroy(p); // ��_firstָ��ָ����������ЧԪ�ؽ�����������
		}
		_allocator.deallocate(_first);  // �ͷŶ��ϵ������ڴ� 

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