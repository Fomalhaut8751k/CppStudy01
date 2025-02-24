#include<iostream>
#include<queue>
#include<vector>

using namespace std;

// ����operator()С������������غ����Ķ��󣬳�����������
// ���߽����º���

//template<typename T>
//bool compare(T a, T b) {
//	return a > b;  // ��������ʵ����Ŀ�в��ܸĳɴ���
//}

// c���Եķ�����ͨ������ָ��
//template<typename T>
//bool mygreater(T a, T b) {
//	return a > b;
//}
//
//template<typename T>
//bool myless(T a, T b) {
//	return a < b;
//}
//
//template<typename T, typename Compare>
//bool compare(T a, T b, Compare comp) {
//	return comp(a, b);
//}


// ͨ����������
template<typename T>
class mygreater {
public:
	bool operator()(T a, T b) {
		return a > b;
	}
};

template<typename T>
class myless {
public:
	bool operator()(T a, T b) {
		return a < b;
	}
};

template<typename T, typename Compare>
bool compare(T a, T b, Compare comp) {
	return comp(a, b);
}

int main() {
	// ͨ������ָ��
	/*cout << compare(10, 20, mygreater<int>) << endl;
	cout << compare(10, 20, myless<int>) << endl;*/
	// ����ͨ������ָ����ú�������û�취�����ģ�Ч�ʺܵͣ���Ϊ�к������ÿ���
	// �����Ƿ����ڱ���׶εģ��ڱ༭�׶��޷�ȷ�������ĸ�����

	// ͨ������������ã�����ʡ�Ժ����ĵ��ÿ���
	cout << compare(10, 20, mygreater<int>()) << endl;

	using MinHeap = priority_queue<int, vector<int>, greater<int>>;  // С���ѵ�ʵ��
	MinHeap que2;
	for (int i = 0; i < 10; ++i) {
		que2.push(rand() % 100);
	}
	while (!que2.empty()) {
		cout << que2.top() << " ";
		que2.pop();
	}cout << endl;

	return 0;
}