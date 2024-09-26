#include <iostream>

int main(void) {
	double x, y;

	std::cout << "Enter a value for X: ";
	std::cin >> x;
	std::cout << "Enter a value for Y: ";
	std::cin >> y;

	double* x_ptr = &x;
	double* y_ptr = &y;
	double sum = *x_ptr + *y_ptr;

	std::cout << "X value: " << *x_ptr << "\nY value: " << *y_ptr << "\nSum: " << sum << '\n';
	return 0;
}
