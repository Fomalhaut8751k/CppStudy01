#include<iostream>

using namespace std;

// c++����ģ��
/*
	ģ������壺������Ҳ���Խ��в�������
	����ģ�����޷�����ģ���Ϊ��֪���������ͣ��ڵ��õ����ʵ����
*/

template<typename T>  // ����һ��ģ������б�
bool compare(T a, T b);

/*
�ں������õ㣬���������û�ָ�������ͣ���ԭģ��ʵ����һ�ݺ����������
bool compare<int>(int a, int b) {  
	return a > b.
}

bool compare<double>(double a, double b) {
	return a > b.
}
��Щʵ���������Ľ���ģ�庯��

*/

// ���compare����ģ�壬�ṩconst char* ���͵��������汾
template<>
bool compare(const char* a, const char* b);

// ��ͨ����
bool compare(const char* a, const char* b);

// ����ģ�壬ģ�������������ģ��(��ͨ)�����������ع�ϵ

template<typename T, int SIZE>
void show(T a);

template<typename T, char s>
void show2(T a);

int main() {

	// cout << compare<int>(10, 20) << endl;  // ����ģ��Ӿ������Ͳ��Ǿ��庯��

	// cout << compare(10, 20) << endl;  // ��ʹ������������ͣ�Ҳ���Ը����û������ʵ������
	// �����Ƶ�����ģ���ʵ������
	// ĳ������ʵ������ģ������ĺ���ֻ����һ�ݣ�
	// compare<int>(10, 20)��һ��ʹ��int���ͣ�����һ��
	// compare(10, 20)ʵ�����ݷ���Ҳ��int���Ͳ��������ʹ��֮ǰ��

	// cout << compare<int>(10, 9.5) << endl;  // ����ת��
	// cout << compare(10, 9.5) << endl; �޷�����ʵ�����ݣ��Ҳ�����Ӧ��ģ��

	// cout << compare("aaa", "bbb") << endl;  // T = const char*
	// ���ǱȽϵ������ߵĵ�ַ������ϣ���ǰ�ascii���бȽϣ�������Ӧ����strcmp()
	// ģ���������(ר�û�)
	
	// �������ģ�������������ͨ�����������ȵ�����ͨ����
	compare("aaa", "bbb");  // ������ͨ
	compare<const char*>("aaa", "bbb");  // ����������

	// ģ����벻����һ���ļ��ж��壬����һ���ļ���ʹ�õġ�ģ��������֮ǰ��һ��Ҫ����
	// ģ�嶨��ĵط��������Ļ���ģ����ܹ�����������ʵ�����������ܹ�������������Ĵ���
	// ����һ��ģ����붼�Ƿ���ͷ�ļ����еģ�Ȼ����Դ�ļ�����ֱ�ӽ���#include����
	show<int, 4>(3);
	show2<int, 'a'>(3);

	return 0;
}

// �����Ͳ��� 
template<typename T, int SIZE>
void show(T a) {
	for (int i = 0; i < SIZE; i++) {
		cout << a << endl;
		a++;
	}
}

template<typename T, char s>
void show2(T a) {
	cout << a << ": " << s << endl;
}

