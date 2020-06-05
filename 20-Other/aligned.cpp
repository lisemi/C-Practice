/*
�ṩ���ڴ洢�������ͺ�����Ĵ�С�� POD �����㹻�󣬲��ʵ����롣
ʹ�ô�ģ��������ȡ�Ķ��뷽ʽ��δ��ʼ���Ĵ洢�д洢һ����������Ĵ�С�� 
��Ա typedef type ���� POD ������ʵĴ洢���г����κ����͵� Types; ��
С��С�� Len�� ��̬��Ա alignment_value ���͵� std::size_t �������г�
���������͵���������ϸ�Ķ��뷽ʽ Types��
*/
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <type_traits>
using namespace std;

#if 1
#if defined __GNUC__ && __GNUC__ < 5 && !defined(_LIBCPP_VERSION)
constexpr std::size_t max(std::size_t a){
	return a;
}

constexpr std::size_t max(std::size_t a, std::size_t b){
	return a > b ? a : b;
}

template <typename... Vals>
constexpr std::size_t max(std::size_t a, std::size_t b, Vals... v){
	return max(a, max(b, v...));
}

// this is for backwards compatibility with not-quite C++11 compilers
// �û�ʵ��C++11��aligned_union���ܡ�
template <std::size_t Len, typename... Types>
struct aligned_union{
	struct type{
		alignas(max(alignof(Types)...))
		char buffer[max(Len, max(sizeof(Types)...))];
	};
};
#else
// Obtains a POD type suitable for use as storage for any object whose type is listed in Types, and a size of at least Len.
using std::aligned_union;
#endif
/*
union U_type {
	std::list<char> l;
	std::map<std::string, char> m;
	std::vector<int> v;
	int i;
	string s;
	U_type(string s) : s(s) {}
	//U_type(int i) : i(i) {}
};*/

int main() {
	aligned_union<1		// ��С����ռ�
		, std::list<char>
		, std::map<std::string, char>
		, std::vector<int>
		, int
		, string
	>::type data;
	// placement new
	string* t = new(&data) string("hello");  // ���û�ж���U_type�����壬"U_type"ֱ���滻�ɾ������ͼ��ɡ���string("hello")
	std::cout << t << endl;		
	//std::cout << t->s << endl;	// ȡֵ����Ҫ����һ�����������ʹ��ȡֵ����
	reinterpret_cast<string*>(&data)->~string(); //һ��Ҫ��������������˹����壬��Ӧ����������ִ�й�����������ͱ�������: reinterpret_cast<string*>(&data)->~s
	cin.get();
	return 0;
}

#else
// ��2��
union U_type{
	int i;
	float f;
	double d;
	U_type(float e) : f(e) {}
};

typedef std::aligned_union<16, int, float, double>::type aligned_U_type;

int main(){
	// allocate memory for a U_type aligned on a 16-byte boundary
	aligned_U_type au;
	// do placement new in the aligned memory on the stack
	U_type* u = new (&au) U_type(1.0f);
	if (nullptr != u){
		std::cout << "value of u->i is " << u->i << std::endl;
		// must clean up placement objects manually!
		u->~U_type();
	}
	cin.get();
	return 0;
}
#endif