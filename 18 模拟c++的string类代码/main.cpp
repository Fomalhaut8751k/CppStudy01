#pragma warning( disable : 4996)
#include<iostream>

using namespace std;


class String {
public:
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
private:
	char* _pstr; 
};


int main(){




	return 0;
}