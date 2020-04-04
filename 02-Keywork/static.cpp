#include <iostream>
using namespace std;

class test{
public:
	test() :a(0), b(0) {
	}
	~test() {
	}
	void add() {
		a++; b++;
		c++;   // �Ǿ�̬��������ʹ�þ�̬��Ա����
	}
	static void adds() {
		//a++; b++;  // ���뱨����̬��Ա�����޷�ʹ�÷Ǿ�̬����
		c++;
	}
	static int getC() {
		cout << "static c : " << c << endl;
		return c;
	}

	void print() {
		cout << "a : " << a << endl;
		cout << "b : " << b << endl;
		cout << "c : " << c << endl;
	}

private:
	int a;
	int b;
	static int c; //��̬��Ա����
};

class subTest:test {
public:
	void print() {
		cout << "subTest c:" << c << endl;
	}

private:
	static int c;
};

//��̬���Ա������ʼ��
int test::c = 10;
int subTest::c = 100;

void main()
{

	test  a1, a2, a3;
	subTest b;
	a1.print(); //0,0,10
	a2.adds();  //0,0,12
	a2.add();   //1,1,12
	a3.print(); //0,0,12
	b.print();  // 100

	//��̬��Ա�����ĵ��÷���
	a3.getC();   //�ö���.
	test::getC();  //��::

	cout << "end..." << endl;
	system("pause");
	return;
}
