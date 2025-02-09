#include<iostream>

using namespace std;

/*		目标：一个集大成者的vector容器
* 1. 深拷贝
* 2. 模板
* 3. 空间配置器(用不上)
* 4. 迭代器失效
* 5. 对象池
*/

// ##################################  空间适配器 ################################## 
template<typename T>
class Allocator {
public:
	// 四个方法：开辟内存，构造，析构，释放内存
	T* allocate(size_t size) {  // 负责内存开辟，返回对应指针
		return (T*)malloc(size * sizeof(T));
	}

	void construct(T* p, const T& val) {
		new (p) T(val);// 在指定内存上创建对象
	}

	void destroy(T* p) {
		p->~T();  // 调用析构函数
	}

	void deallocate(void* p) {
		free(p);  // 释放内存
	}
};
/*
	空间配置器对于数组来说，因为数组要先开辟一个定长的大小/容量，在堆区开辟一个
	SIZE大小的T类数组时，为了避免new的时候就构造SIZE个T对象，需要用到空间配置器
	将开辟内存和构造对象分开。。。。

	但是这次的vector底层是链表，没有容量和扩容的概念，就不需要先开辟一个大的空间
*/
// #################################  测试类Test ###################################
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
			cout << "开辟" << POOL_ITEM_SIZE << "个大小作为对象池给Test实现" << endl;
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
	Test* _next;  // 添加一个指针域，用于实现对象池

	friend ostream& operator<<(ostream& cout, const Test& t);
};

Test* Test::_itemPool = nullptr;
int Test::_countConstruct = 0;
int Test::_countDestroy = 0;

// ###############################  自定义vector实现 ############################### 
template<typename T>
class vector {
public:
	// 一般构造函数
	vector():_size(0) {
		_head = _tail = new Node();
	}

	// 拷贝构造函数
	vector(const vector<T>& v) {
		_head = _tail = new Node();
		if (v._size > 0) {  // v如果不是空的容器
			Node* p = v._head->_next;
			Node* q = _head;
			while (p != nullptr) {
				Node* qtmp = new Node(p->_data);  // 额外开辟，防止指向同样的节点
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

	// 赋值
	vector<T>& operator=(const vector& v) {
		cout << "赋值" << endl;
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

		if (v._size > 0) {  // v如果不是空的容器
			Node* p = v._head->_next;
			Node* q = _head;
			while (p != nullptr) {
				Node* qtmp = new Node(p->_data);  // 额外开辟，防止指向同样的节点
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
		cout << "节点数:" << _size << endl;
		Node* cur = _head->_next;
		int index = 0;
		cout << "遍历结果: ";
		while (cur != nullptr) {
			cout << cur->_data << "/" << cur->_next << " ";
			cur = cur->_next;
		}
		cout << "\ntail: " << _tail << "\n" << endl;
	}

	// ############# 链表节点，用链表来存储对象 ##############
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

	// ####################### 迭代器 ########################
	class iterator {
		// 前置递增，不等于，解引用.....
	public:
		iterator(Node* pNde = nullptr) :_pNde(pNde) {}
		// 前置递增
		void operator++() {
			_pNde = _pNde->_next;
		}
		// 不等于
		bool operator!=(const iterator& iter) {
			return _pNde != iter._pNde;
		}
		// 解引用
		Node& operator*() {
			return *_pNde;
		}

	private:
		Node* _pNde;
	};

	iterator begin() { return iterator(_head->_next); }  // 第一个结点
	iterator end() { return iterator(_tail->_next); }  // 最后一个结点
	/*
		本质上就是指针？但容器内部的底层就是链表
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
				// 定位到待插入点的前面
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
				// 定位到待删除点的前面
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
	Node* _head;  // 记录链表的头结点
	Node* _tail;  // 记录链表的尾结点
	int _size;  // 记录链表上节点个数
};


ostream& operator<<(ostream& cout, const Test& t) {
	cout << t._val ;
	return cout;
}


int main() {
#if 0 // 测试功能一
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
		Test* data = new Test();  // 默认构造
		vt.push_back(data);
	}
	/*
			vector<Test> vt;
		调用vector的默认构造函数，在堆区开辟一个Node对象——Node()
				_head = _tail = new Node();

			Test* data = new Test();
		调用了重载版本的new，_itemPoll当前为nullptr，故先在堆区开辟一个非常大的空间，
		然后再在_itemPool的位置上构造Test对象——Test()
			
			vt.push_back(data)
		data是Test*类型的，Node的new操作是默认的new，正常的开辟内存和构造对象
		——Node(T*, Node*),
				Node* newNode = new Node(data)

	*/
#endif
	return 0;
}