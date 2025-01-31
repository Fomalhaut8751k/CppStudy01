#pragma warning( disable : 4996)
#include<iostream>

using namespace std;

class Person {
public:
	// ��ͨ���캯��
	Person(int age, const char* name)
	:_age(age){
		if (name != nullptr) {
			_name = new char[strlen(name) + 1];
			strcpy(_name, name);
		}
		else {
			_name = new char[1];
			*_name = '\0';
		}
		_age = age;
		_number++;

	}

	// �������캯��
	Person(const Person& per) {
		_name = new char[strlen(per._name) + 1];
		/*for (int i = 0; i < strlen(per._name); i++) {
			_name[i] = per._name[i];
		}*/
		strcpy(_name, per._name);
		_age = per._age;
		_number++;
	}

	// ��ֵ
	Person& operator=(const Person& per) {
		if (this == &per) {
			return *this;
		}
		delete[] _name;
		_name = new char[strlen(per._name) + 1];
		/*for (int i = 0; i < strlen(per._name); i++) {
			_name[i] = per._name[i];
		}*/
		strcpy(_name, per._name);
		_age = per._age;
		return *this;
	}

	void show() {
		cout << "������" << _name << "\t" << "���䣺" << _age << endl;
	}

	// ��Ҫ�β���const Person*����
	// ����Ա����
	void show() const{
		cout << "������" << _name << "\t" << "���䣺" << _age << endl;
		// _name = "awl";
	}

	int count() {
		return _number;
	}

	// ��������
	~Person() {
		delete[] _name;
		_name = nullptr;
	}

private:
	int _age;
	char* _name;

	static int _number;
};

// ��̬��Ա����
// ���������������ʼ��
int Person::_number = 0;

// ��̬��Ա����
/*
	1. �������������
	2. �����������������÷���
	3. ����������ʶ����˽�г�Ա�������ڲ���������ĳ�Ա(��̬��)
*/

int main() {

	Person p1(23, "wudongwei");
	cout << "�Ѵ�����Ա����" << p1.count() << endl;
	Person p2 = p1;
	cout << "�Ѵ�����Ա����" << p1.count() << endl;
	Person p3(21, "yezhenhao");
	p3 = p2;
	cout << "�Ѵ�����Ա����" << p1.count() << endl;
	p1.show();
	p2.show();
	p3.show();

	const Person p4(24, "zhoujunbo");
	// p4.show(); ǰ��˵�������ó�Ա�����ǻ�Ѷ���ĵ�ַ��Ϊ��������
	// ������һ��const���ͣ������ַΪ const Person*����show���β���Person*
	// ���൱��Person* <= const Person* �Ǵ����
	p4.show();
	// ˵����ͨ�ķ����������ǵ��ò��˵�
	// ������ֻ�ܵ��ó�����������ͨ������Ե��ò�ͬ�����ͳ�����
	// һ�㽨��ֻ�������ĳ�Ա����һ��д�ɳ�����
	// �������ﲻ���޸ĳ�Ա����������_age,��Ϊ�൱��this->_age����this��const����
	// �ģ�����ָ��ָ��������޷��޸�


	return 0;
}