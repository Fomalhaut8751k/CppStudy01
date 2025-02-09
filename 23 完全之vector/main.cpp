#include<iostream>

using namespace std;

/*		Ŀ�꣺һ��������ߵ�vector����
* 1. ���
* 2. ģ��
* 3. �ռ�������(�ò���)
* 4. ������ʧЧ
* 5. �����
*/

// ##################################  �ռ������� ################################## 
template<typename T>
class Allocator {
public:
	// �ĸ������������ڴ棬���죬�������ͷ��ڴ�
	T* allocate(size_t size) {  // �����ڴ濪�٣����ض�Ӧָ��
		return (T*)malloc(size * sizeof(T));
	}

	void construct(T* p, const T& val) {
		new (p) T(val);// ��ָ���ڴ��ϴ�������
	}

	void destroy(T* p) {
		p->~T();  // ������������
	}

	void deallocate(void* p) {
		free(p);  // �ͷ��ڴ�
	}
};
/*
	�ռ�����������������˵����Ϊ����Ҫ�ȿ���һ�������Ĵ�С/�������ڶ�������һ��
	SIZE��С��T������ʱ��Ϊ�˱���new��ʱ��͹���SIZE��T������Ҫ�õ��ռ�������
	�������ڴ�͹������ֿ���������

	������ε�vector�ײ�������û�����������ݵĸ���Ͳ���Ҫ�ȿ���һ����Ŀռ�
*/
// #################################  ������Test ###################################
class Test {
public:
	Test(int val = 3) :_val(val), _next(nullptr) { 
		cout << "Test()" << endl;
		_countConstruct++;
	};
	Test(const Test& t) {
		cout << "Test(const Test& t)" << endl;
		_val = t._val;
		_next = nullptr;
		_countConstruct++;
	}
	~Test() { 
		cout << "~Test()" << endl;
		_countDestroy++;
	}

	void* operator new(size_t size) {
		if (_itemPool == nullptr) {
			_itemPool = (Test*)new char[POOL_ITEM_SIZE * sizeof(Test)];
			Test* it = _itemPool;
			cout << "����" << POOL_ITEM_SIZE << "����С��Ϊ����ظ�Testʵ��" << endl;
			for (; it < _itemPool + POOL_ITEM_SIZE - 1; it++) {
				it->_next = it + 1;
			}
			it->_next = nullptr;
		}
		Test* it = _itemPool;
		_itemPool = _itemPool->_next;
		return it;
	}

	void operator delete(void* ptmp) {
		Test* it = (Test*)ptmp;
		it->_next = _itemPool;
		_itemPool = it;
	}
	
	static Test* _itemPool;
	static const int POOL_ITEM_SIZE = 1000;

	static int _countConstruct;
	static int _countDestroy;

private:
	int _val;
	Test* _next;  // ���һ��ָ��������ʵ�ֶ����

	friend ostream& operator<<(ostream& cout, const Test& t);
};

Test* Test::_itemPool = nullptr;
int Test::_countConstruct = 0;
int Test::_countDestroy = 0;

// ###############################  �Զ���vectorʵ�� ############################### 
template<typename T>
class vector {
public:
	// һ�㹹�캯��
	vector():_size(0) {
		_head = _tail = new Node();
	}

	// �������캯��
	vector(const vector<T>& v) {
		_head = _tail = new Node();
		if (v._size > 0) {  // v������ǿյ�����
			Node* p = v._head->_next;
			Node* q = _head;
			while (p != nullptr) {
				Node* qtmp = new Node(p->_data);  // ���⿪�٣���ָֹ��ͬ���Ľڵ�
				q->_next = qtmp;
				if (p->_next != nullptr) {
					q = q->_next;
					p = p->_next;
				}
				else {
					break;
				}
			}
			_tail = q->_next;
		}
		_size = v._size;
	}

	~vector() {
		Node* cur = _head;
		while (cur != nullptr) {
			Node* curNext = cur->_next;
			delete cur;
			cur = curNext;
		}
	}

	// ��ֵ
	vector<T>& operator=(const vector& v) {
		cout << "��ֵ" << endl;
		if (this == &v) {
			return *this;
		}
		Node* cur = _head;
		while (cur != nullptr) {
			Node* curNext = cur->_next;
			delete cur;
			cur = curNext;
		}

		_head = _tail = new Node();

		if (v._size > 0) {  // v������ǿյ�����
			Node* p = v._head->_next;
			Node* q = _head;
			while (p != nullptr) {
				Node* qtmp = new Node(p->_data);  // ���⿪�٣���ָֹ��ͬ���Ľڵ�
				q->_next = qtmp;
				if (p->_next != nullptr) {
					q = q->_next;
					p = p->_next;
				}
				else {
					break;
				}
			}
			_tail = q->_next;
		}
		_size = v._size;
		return *this;
	}

	void push_back(T* data) {
		Node* newNode = new Node(data);
		_tail->_next = newNode;
		_tail = _tail->_next;
		_size++;
	}

	void pop_front() {
		if (_size == 0) {
			return;
		}
		_size--;
		Node* headNext = _head->_next;
		delete _head;
		_head = headNext;
	}

	void push_front(T data) {
		Node* newNode = new Node(data);
		newNode->_next = _head->_next;
		_head->_next = newNode;
		_size++;
	}

	void pop_back() {
		if (_size == 0) {
			return;
		}
		_size--;
		Node* cur = _head;
		while (cur->_next != _tail) {
			cur = cur->_next;
		}
		delete _tail;
		_tail = cur;
		_tail->_next = nullptr;
	}

	T operator[](int index) {
		if (index <= -2 || index >= _size) {
			throw "Index is out of the range";
		}
		if (index == -1) {
			return _tail->_data;
		}
		Node* cur = _head->_next;
		for (int i = 0; i < index; i++) {
			cur = cur->_next;
		}
		return cur->_data;
	}

	void show() const {
		cout << "head: " << _head << endl;
		cout << "�ڵ���:" << _size << endl;
		Node* cur = _head->_next;
		int index = 0;
		cout << "�������: ";
		while (cur != nullptr) {
			cout << cur->_data << "/" << cur->_next << " ";
			cur = cur->_next;
		}
		cout << "\ntail: " << _tail << "\n" << endl;
	}

	// ############# ����ڵ㣬���������洢���� ##############
	struct Node {
		Node() : _data(nullptr), _next(nullptr) {
			cout << "Node()" << endl;
		}
		Node(T* data, Node* next = nullptr) :_data(data), _next(next) {
			cout << "Node(T*, Node*)" << endl;
		};
		void NodeShow() const{
			cout << _data << "/" << _next;
		}
		T* _data;
		Node* _next;
	};

	// ####################### ������ ########################
	class iterator {
		// ǰ�õ����������ڣ�������.....
	public:
		iterator(Node* pNde = nullptr) :_pNde(pNde) {}
		// ǰ�õ���
		void operator++() {
			_pNde = _pNde->_next;
		}
		// ������
		bool operator!=(const iterator& iter) {
			return _pNde != iter._pNde;
		}
		// ������
		Node& operator*() {
			return *_pNde;
		}

	private:
		Node* _pNde;
	};

	iterator begin() { return iterator(_head->_next); }  // ��һ�����
	iterator end() { return iterator(_tail->_next); }  // ���һ�����
	/*
		�����Ͼ���ָ�룿�������ڲ��ĵײ��������
	*/
	iterator insert(T data, int pos) {
		if (pos < 0 || pos >= _size) {
			throw "Index is out of range";
		}
		Node* cur = _head;
		Node* newNode = nullptr;
		int index = 0;
		while (cur != nullptr) {
			if (index++ == pos) {
				// ��λ����������ǰ��
				newNode = new Node(data);
				newNode->_next = cur->_next;
				cur->_next = newNode;
				break;
			}
			cur = cur->_next;
		}
		_size++;
		return iterator(newNode);
	}

	iterator erase(int pos) {
		if (pos < 0 || pos >= _size) {
			throw "Index is out of range";
		}
		if (pos == _size - 1) {
			pop_back();
			return iterator();
		}
		Node* cur = _head;
		int index = 0;
		while (cur != nullptr) {
			if (index++ == pos) {
				// ��λ����ɾ�����ǰ��
				Node* curNext = cur->_next;
				cur->_next = curNext->_next;
				delete curNext;
				break;
			}
			cur = cur->_next;
		}
		_size--;
		return iterator(cur->_next); 
	}

private:
	Node* _head;  // ��¼�����ͷ���
	Node* _tail;  // ��¼�����β���
	int _size;  // ��¼�����Ͻڵ����
};


ostream& operator<<(ostream& cout, const Test& t) {
	cout << t._val ;
	return cout;
}


int main() {
#if 0 // ���Թ���һ
	vector<int> v;
	for (int i = 0; i < 10; i++) {
		v.push_back(rand() % 200);
	}
	//v.show();

	vector<int> v1 = v;
	//v1.show();

	vector<int> v2;
	for (int i = 0; i < 10; i++) {
		v2.push_back(rand() % 200);
	}
	//v2.show();

	v2 = v1;
	v2.show();

	v2.push_back(12);
	v2.show();

	v2.pop_front();
	v2.show();

	v2.push_front(27);
	v2.show();

	v2.pop_back();
	v2.show();

	cout << v2[-1] << endl;
	
	auto it = v2.begin();
	for (; it != v2.end(); ++it) {
		(*it).NodeShow();
		cout << " ";
	}cout << endl;

	for (auto item : v2) {
		item.NodeShow();
		cout << " ";
	}cout << endl;

	v2.insert(5003, 2);
	v2.show();

	v2.erase(3);
	v2.show();
#endif 

#if 1
	vector<Test> vt;
	for (int i = 0; i < 6; i++) {
		system("pause");
		Test* data = new Test();  // Ĭ�Ϲ���
		vt.push_back(data);
	}
	/*
			vector<Test> vt;
		����vector��Ĭ�Ϲ��캯�����ڶ�������һ��Node���󡪡�Node()
				_head = _tail = new Node();

			Test* data = new Test();
		���������ذ汾��new��_itemPoll��ǰΪnullptr�������ڶ�������һ���ǳ���Ŀռ䣬
		Ȼ������_itemPool��λ���Ϲ���Test���󡪡�Test()
			
			vt.push_back(data)
		data��Test*���͵ģ�Node��new������Ĭ�ϵ�new�������Ŀ����ڴ�͹������
		����Node(T*, Node*),
				Node* newNode = new Node(data)

	*/
#endif
	return 0;
}