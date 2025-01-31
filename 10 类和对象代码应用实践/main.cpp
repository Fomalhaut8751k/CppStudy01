#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

// �Զ����ַ�������
class String {
public:
	// ��ͨ���캯��
	String(const char* str = nullptr) {
		if (str != nullptr) {  // ���ж�ָ���Ƿ�Ϊnullptr��nullptr���ܸ���strlen����
			m_data = new char[strlen(str) + 1];  // ����ĩβ��\0
			strcpy(m_data, str);
		}
		else {
			m_data = new char[1];
			*m_data = '\0';
		}
	}

	// �������캯��
	String(const String& other) {
		m_data = new char[strlen(other.m_data) + 1];
		/*for (int i = 0; i < strlen(other.m_data); i++) {
			m_data[i] = other.m_data[i];
		}*/
		strcpy(m_data, other.m_data);
	}

	// ��������
	~String() {
		delete[] m_data;
		m_data = nullptr;
	}

	// ��ֵ����
	String& operator = (const String& other){
		// Ϊ��֧��������ֵ���ʷ���ֵ��Ϊvoid
		if (this == &other) {
			return *this;
		}
		delete[] m_data;
		m_data = new char[strlen(other.m_data) + 1];
		strcpy(m_data, other.m_data);
		return *this;
	}

	const char* getMData() {
		return m_data;
	}

private:
	char* m_data;  // ���ڱ����ַ���
};


// ѭ������
class Queue {
public:
	// ��ͨ���캯��
	Queue(int size = 20) {
		_pQue = new int[size];
		_size = size;
		_front = _rear = 0;
	}

	// �������캯��
	Queue(const Queue& q) {
		_pQue = new int[q._size];
		for (int i = q._front; i < q._rear; i = (i + 1) % q._size) {
			_pQue[i] = q._pQue[i];
		}
		_size = q._size;
		_front = q._front;
		_rear = q._rear;
	}
	
	// operator
	Queue& operator=(const Queue& q) {
		if (this == &q) {
			return *this;
		}
		delete[] _pQue;
		_pQue = new int[q._size];
		for (int i = q._front; i < q._rear; i = (i + 1) % q._size) {
			_pQue[i] = q._pQue[i];
		}
		_size = q._size;
		_front = q._front;
		_rear = q._rear;
		return *this;
	}

	// ����ͨ�����²���ɾ��Ĭ�ϵĿ�������͸�ֵ����������ֱ�ӿ�������͸�ֵ�ͻᱨ��
	// Queue(const Queue& q) = delete;
	// Queue& operator=(const Queue& q) = delete;

	// ��������
	~Queue() {
		delete[] _pQue;
		_pQue = nullptr;
	}

	// ���
	void addQue(int val) {
		if (full())
			resize();
		_pQue[_rear] = val;
		_rear = (_rear + 1) % _size;
	}

	// ����
	void pop() {
		if (empty())
			return;
		_front = (_front + 1) % _size;
	}

	// ��ȡ��ͷԪ��
	int top() {
		return _pQue[_front];
	}

	// �ж϶���
	bool full() {
		return (_rear + 1) % _size == _front;
	}

	//
	bool empty() {
		return _front == _rear;
	}

private:
	int* _pQue;  // ������е�����ռ�
	int _front;  // ָʾ��ͷ��λ��
	int _rear;  // ָʾ��β��λ��
	int _size;  // �ܵĴ�С

	void resize() {
		int* ptmp = new int[2 * _size];
		int index = 0;
		for (int i = _front; i != _rear; i = (i + 1) % _size) {
			ptmp[index++] = _pQue[i];
		}
		delete[] _pQue;
		_pQue = ptmp;
		_front = 0; _rear = index; _size *= 2;
	}
};

int main() {
	String str1("pdchelloworld");
	String str2 = str1;
	String str3;
	str3 = str2 = str1;

	cout << "str1: " << str1.getMData() << endl;
	cout << "str2: " << str2.getMData() << endl;
	cout << "str3: " << str3.getMData() << endl;

	Queue queue;
	for (int i = 0; i < 20; i++) {
		queue.addQue(rand() % 100);
	}

	Queue queue2 = queue;
	Queue queue3;
	queue3 = queue;

	while (!queue.empty()) {
		cout << queue.top() << " ";
		queue.pop();
	}cout << endl;


	return 0;
}