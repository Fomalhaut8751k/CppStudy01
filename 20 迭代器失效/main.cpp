#include<iostream>
#include<vector>

using namespace std;

int main() {
	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(rand() % 100 + 1);
	}
	for (auto item : v1) {
		cout << item << " ";
	}cout << endl;

#if 0  // ɾ��

	// ɾ����һ�����
	auto it = v1.begin();
	/*  ����Ϊ������ʧЧ������  */
	//for (; it != v1.end(); ++it) {    
	//	if (*it % 2 == 0) {  // �����ż����ɾ��
	//		v1.erase(it);
	//	}
	//}

	while (it != v1.end()) {
		if (*it % 2 == 0) {
			it = v1.erase(it);  // ������һ����Ч�ĵ�����λ�� 
		}
		else {
			++it;
		}
	}
#endif

#if 1  // ���
	auto it = v1.begin();
	for (; it != v1.end(); ++it) {
		if (*it % 3 == 0) { 
			it = v1.insert(it, *it-1);  // ԭ���ı���������ȥ�ˣ����Ҫ�����β��ܵ���һ��
			++it;
		}
	}

	for (auto item : v1) {
		cout << item << " ";
	}cout << endl;
#endif

	return 0;
}