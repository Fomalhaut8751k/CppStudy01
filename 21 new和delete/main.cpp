#include<iostream>

using namespace std;

void* operator new(size_t size) {
	void* p = malloc(size);
	if (p == nullptr) {
		throw bad_alloc();
	}
	cout << "operator new addr: " << p << endl;
	return p;
}

void* operator new[](size_t size) {
	void* p = malloc(size);
	if (p == nullptr) {
		throw bad_alloc();
	}
	cout << "operator new[] addr: " << p << endl;
	return p;
}

void operator delete(void* ptr) {
	cout << "operator delete addr: " << ptr<< endl;
	free(ptr);
}

void operator delete[](void* ptr) {
	cout << "operator delete[] addr: " << ptr << endl;
	free(ptr);
}


class Test {
public:
	Test(int data = 10):ptr(new int(data)) { cout << "Test()" << endl; }
	~Test() { delete ptr; cout << "~Test()" << endl; }
private:
	int* ptr;
};

int main() {
	/*try {
		int* p = new int;
		delete[] p;

		int* q = new int[10];
		delete q;
	}
	catch (const bad_alloc& err) {
		cerr << err.what() << endl;
	}*/
	Test* p1 = new Test;
	delete []p1;


	return 0;
}