#include <iostream>

int main(void) {
	// get the change
	extern int total;
	std::cout << "Enter the amount of change: ";
	std::cin >> total;
	while (total < 0 || total >= 100) {
		std::cout << "Please enter a num in range (0, 100]: ";
		std::cin >> total;
	}

	extern int r;			// remainder

	extern unsigned int quarter;		// calculate quarters
	r = total % quarter;
	total = total / quarter;
	std::cout << "Quarters: " << total << std::endl;
	total = r;

	extern unsigned int dime;		// calculate dime
	r = total % dime;
	total = total / dime;
	std::cout << "Dimes: " << total << std::endl;
	total = r;
	
	extern unsigned int nickel;		// calculate nickel
	r = total % nickel;
	total = total / nickel;
	std::cout << "Nickels: " << total << std::endl;
	total = r;

	extern unsigned int penny;		// calculate penny
	r = total % penny;
	total = total / penny;
	std::cout << "Pennies: " << total << std::endl;
	total = r;

	return 0;
}