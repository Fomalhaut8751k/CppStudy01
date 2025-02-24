#include<iostream>

#include<set>
#include<map>

#include<algorithm>

using namespace std;

/* 有序关联容器 => 红黑树 增删查O(log2n) 2是底数(n是树的层数，树的高度)
	set
	multiset
	map
	multimap

	增删查
	1. 增加insert()
	2. 遍历iterator，调用find
	3. erase(key), erase(it)
*/

class Student {  // 自定义的数据类型需要重载< , 不然在set中不知道怎么排序
public:
	Student() { _id = 5000; _name = "aaa"; }
	Student(int id, string name):_id(id), _name(name){}
	bool operator<(const Student& s) const {
		return this->_id < s._id;
	}

private:
	int _id;
	string _name;

	friend ostream& operator<<(ostream& cout, const Student& s);
};

ostream& operator<<(ostream& cout, const Student& s) {
	cout << "学号: " << s._id << "\t" << "姓名: " << s._name;
	return cout;
}

template<typename T>
void pdc(T item) {
	cout << item << " ";
}


int main() {
	set<int> set1;
	for (int i = 0; i < 20; ++i) {
		set1.insert(rand() % 20 + 1);
	}
	cout << "size: " << set1.size() << endl;
	for (int v : set1) {
		cout << v << " ";
	}cout << endl;  // 输出是从小到大有序的【红黑树的中序遍历】

	set1.insert(5003);
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;
	set1.erase(5003);
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;
	set1.erase(set1.begin());
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;

	set<Student> set2;
	set2.insert(Student(5003, "阿伟罗"));
	set2.insert(Student(1876, "朴昌罗"));
	set2.insert(Student(3111, "菌鞭罗"));
	for_each(set2.begin(), set2.end(), pdc<Student>); cout << endl;

	map<int, Student> stuMap;  
	stuMap.insert({ 1000, Student(5003, "阿伟罗") });
	stuMap.insert({ 2000, Student(6004, "阿伟罗") });
	stuMap.insert({ 3000, Student(7005, "阿伟罗") });
	for (auto item : stuMap) {
		cout << item.first << ": " << item.second << endl;
	}
	cout << stuMap[4000] << endl;  // 需要Student有默认的构造函数
	return 0;
}