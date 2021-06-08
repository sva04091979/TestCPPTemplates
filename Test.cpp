#include <iostream>
#include <string>
#include "Lib.h"

using namespace std;


/*template <typename T, typename... Types>
constexpr bool is_any_of = disjunction_v<is_same<T, Types>...>;

template<typename Type>
enable_if_t<is_any_of<Type,char*,wchar_t*>,void> Revers(Type text) {
	if (*text == '\0') return;
	Type front = text;
	Type back = text;
	while (*back != '\0') ++back;
	--back;
	while (front != back) {
		*front ^= *back; *back ^= *front; *front ^= *back;
		if (++front == back) break;
		else --back;
	}
}

bool CheckMask(unsigned long long left, unsigned long long right) {
	return ((left ^ right) & right) == right;
}

class A{
protected:
	void Print() { cout << "A" << endl; }
};
class B{};
class C:public A{};
class D:public A,B{};

template<typename ...Type>
class E :public Type ... {
public:
	void Print() {
		if constexpr (disjunction_v<is_base_of<A, Type>...>)
			A::Print();
		else
			cout << "E" << endl;
	}
};
*/

struct A {
	int a;
};

struct AA{};

template<typename ...Type>
struct B :public Type...{
	int b;
};

int main() {
	/*E<B> a;
	E<A, B> b;
	E<D> c;
	a.Print();
	b.Print();
	c.Print();
	*/
}
