#include<iostream>

#include<set>
#include<map>

#include<algorithm>

using namespace std;

/* ����������� => ����� ��ɾ��O(log2n) 2�ǵ���(n�����Ĳ��������ĸ߶�)
	set
	multiset
	map
	multimap

	��ɾ��
	1. ����insert()
	2. ����iterator������find
	3. erase(key), erase(it)
*/

class Student {  // �Զ��������������Ҫ����< , ��Ȼ��set�в�֪����ô����
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
	cout << "ѧ��: " << s._id << "\t" << "����: " << s._name;
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
	}cout << endl;  // ����Ǵ�С��������ġ�����������������

	set1.insert(5003);
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;
	set1.erase(5003);
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;
	set1.erase(set1.begin());
	for_each(set1.begin(), set1.end(), pdc<int>); cout << endl;

	set<Student> set2;
	set2.insert(Student(5003, "��ΰ��"));
	set2.insert(Student(1876, "�Ӳ���"));
	set2.insert(Student(3111, "������"));
	for_each(set2.begin(), set2.end(), pdc<Student>); cout << endl;

	map<int, Student> stuMap;  
	stuMap.insert({ 1000, Student(5003, "��ΰ��") });
	stuMap.insert({ 2000, Student(6004, "��ΰ��") });
	stuMap.insert({ 3000, Student(7005, "��ΰ��") });
	for (auto item : stuMap) {
		cout << item.first << ": " << item.second << endl;
	}
	cout << stuMap[4000] << endl;  // ��ҪStudent��Ĭ�ϵĹ��캯��
	return 0;
}