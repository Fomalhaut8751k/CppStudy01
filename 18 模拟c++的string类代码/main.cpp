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
		else{
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
 
int main(){

	String str1;
	String str2 = "aaa";
	String str3 = "bbb";
	String str4 = str2 + str3;
	//String str5 = str2 + "ccc";
	//String str6 = "ddd" + str2;

	cout << str1 << "\n" << str2 << "\n" << str3 << endl;

	/*if (str5 > str6) {
		cout << "pdcHelloWorld" << endl;
	}*/

	cout << str3[2] << endl;

	return 0;
}