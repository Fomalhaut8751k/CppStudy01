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

#if 0  // 删除

	// 删除的一般情况
	auto it = v1.begin();
	/*  会因为迭代器失效而出错  */
	//for (; it != v1.end(); ++it) {    
	//	if (*it % 2 == 0) {  // 如果是偶数就删除
	//		v1.erase(it);
	//	}
	//}

	while (it != v1.end()) {
		if (*it % 2 == 0) {
			it = v1.erase(it);  // 返回下一个有效的迭代器位置 
		}
		else {
			++it;
		}
	}
#endif

#if 1  // 添加
	auto it = v1.begin();
	for (; it != v1.end(); ++it) {
		if (*it % 3 == 0) { 
			it = v1.insert(it, *it-1);  // 原来的被挤到后面去了，因此要加两次才能到下一个
			++it;
		}
	}

	for (auto item : v1) {
		cout << item << " ";
	}cout << endl;
#endif

	return 0;
}