#pragma warning( disable : 4996)
#include<iostream>

using namespace std;


class String {
public:
	// Ĭ�Ϲ���
	String(const char* p = nullptr) {
		if (p == nullptr) {
			_pstr = new char[1];
			*_pstr = '\0';
		}
		else {
			_pstr = new char[strlen(p) + 1];  // ��Ч�ַ�����+ĩβ'\0'
			strcpy(_pstr, p);
		}
	}

	// Ĭ������
	~String() {
		delete[] _pstr;
		_pstr = nullptr;
	}

	// ��������
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

	// ����
	int length() const {
		return strlen(_pstr);
	}

	// ����c_Str;
	const char* c_Str() const {
		return _pstr;
	}

	// ����
	char& operator[](int index) {  // �ɶ��������������޸�
		return _pstr[index];
	}


	// ��string�ַ��������ṩ��������ʵ��
	class iterator {
	public:
		iterator(char* p = nullptr) : _p(p) {};
		// ǰ�õ���
		iterator& operator++() {
			++_p;
			return *this;
		}
		bool operator!=(const iterator& it) {
			return _p != it._p;
		}
		// ������
		char& operator*() {
			return *_p;
		}

	private: 
		char* _p;  // ��λ��(ָ��)�ķ�װ
	};
	// �����ķ������ǵ�����
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
		// ���ﲻ�� it < str1.end()����Ϊ��ͬ�����ĸ���Ԫ�صĹ�����ʽ���ܲ�ͬ
		// ���������飬�����޷�ֱ���ж�˭��λ�ô�˭��λ��С��
		// ��it++��������Ϊ�����ж�Ӧ�����������ʵ��
		cout << *it;
	}cout << endl;

	String str2 = "12345678";
	for (String::iterator it = str2.begin(); it != str2.end(); ++it) {
		cout << *it;
	}cout << endl;

	for (auto item : str2) {  // �ײ���Ȼ�ǵ���������Ҫ�ֶ�ʵ��
		cout << item;
	}cout << endl;

	// Ϊ16��vector������ӵ�����������
}