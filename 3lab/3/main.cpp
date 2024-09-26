#include <iostream>

typedef int* VEC;
typedef VEC* MATRIX;

int main(void) {
	int a = 5;
	VEC v = &a;
	MATRIX m = &v;
	std::cout << "a: " << a << '\n';
	std::cout << "a through a VEC: " << *v << '\n';
	std::cout << "a through a MATRIX: " << **m << '\n';
	return 0;
}
