#pragma warning( disable : 4996)
#include<iostream>

using namespace std;


class String {
public:
	// 默认构造
	String(const char* p = nullptr) {
		if (p == nullptr) {
			_pstr = new char[1];
			*_pstr = '\0';
		}
		else {
			_pstr = new char[strlen(p) + 1];  // 有效字符个数+末尾'\0'
			strcpy(_pstr, p);
		}
	}

	// 默认析构
	~String() {
		delete[] _pstr;
		_pstr = nullptr;
	}

	// 拷贝构造
	String(const String& str) {
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
	}

	// operator=
	String& operator=(const String& str) {
		if (this == &str) {
			return *this;
		}
		delete[] _pstr;
		_pstr = new char[strlen(str._pstr) + 1];
		strcpy(_pstr, str._pstr);
		return *this;
	}

	// >
	bool operator>(const String& s2) const {
		return strcmp(_pstr, s2._pstr) > 0;
	}

	// <
	bool operator<(const String& s2) const {
		return strcmp(_pstr, s2._pstr) < 0;
	}

	// ==
	bool operator==(const String& s2) const {
		return strcmp(_pstr, s2._pstr) == 0;
	}

	// !=
	bool operator!=(const String& s2) const {
		return strcmp(_pstr, s2._pstr) != 0;
	}

	// 长度
	int length() const {
		return strlen(_pstr);
	}

	// 返回c_Str;
	const char* c_Str() const {
		return _pstr;
	}

	// 索引
	char& operator[](int index) {  // 可读，读出来可以修改
		return _pstr[index];
	}


	// 给string字符串类型提供迭代器的实现
	class iterator {
	public:
		iterator(char* p = nullptr) : _p(p) {};
		// 前置递增
		iterator& operator++() {
			++_p;
			return *this;
		}
		bool operator!=(const iterator& it) {
			return _p != it._p;
		}
		// 解引用
		char& operator*() {
			return *_p;
		}

	private: 
		char* _p;  // 对位置(指针)的封装
	};
	// 容器的方法而非迭代器
	iterator begin() { return iterator(_pstr); }
	iterator end() { return iterator(_pstr + length()); }

	

private:
	char* _pstr;

	// operator+
	friend String operator+(const String& s1, const String& s2);
	// cout
	friend ostream& operator<<(ostream& cout, const String& str);
};

// operator+
String operator+(const String& s1, const String& s2) {
	//char* ptmp = new char[strlen(s1._pstr) + strlen(s2._pstr) + 1];

	String tmp;
	tmp._pstr = new char[strlen(s1._pstr) + strlen(s2._pstr) + 1];
	strcpy(tmp._pstr, s1._pstr);
	strcat(tmp._pstr, s2._pstr);

	/*String tmp(ptmp);
	delete[] ptmp;*/

	return tmp;
}

// cout
ostream& operator<<(ostream& cout, const String& str) {
	cout << str._pstr;
	return cout;
}



int main() {
	string str1 = "12345678";
	for (string::iterator it = str1.begin(); it != str1.end(); it++) {
		// 这里不用 it < str1.end()；因为不同容器的各个元素的关联方式可能不同
		// 可能是数组，链表，无法直接判断谁的位置大谁的位置小；
		// 而it++可行是因为容器有对应的运算符重载实现
		cout << *it;
	}cout << endl;

	String str2 = "12345678";
	for (String::iterator it = str2.begin(); it != str2.end(); ++it) {
		cout << *it;
	}cout << endl;

	for (auto item : str2) {  // 底层依然是迭代器，需要手动实现
		cout << item;
	}cout << endl;

	// 为16的vector容器添加迭代器。。。
}