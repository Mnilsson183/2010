#include <iostream>
#include <cstdlib>
#include <time.h>

#define DEFAULT_CREDITS 100

int die(void) {
	return rand() % 6 + 1;
}

int gameThrow(void) {
	int die1 = die();
	int die2 = die();

	// first roll
	int sum = die1 + die2;
	std::cout << std::endl
			  << "player rolled " << die1 << " + " << die2 << " = " << sum << std::endl;
	if (sum == 7 || sum == 11) return 1;
	else if (sum == 2 || sum == 3 || sum == 12) return -1;
	else {
		int roll = sum;
		std::cout << "The point is set at " << roll << std::endl;
		while (true) {
			int die1 = die();
			int die2 = die();
			sum = die1 + die2;
			std::cout << "player rolled " << die1 << " + " << die2 << " = " << sum << std::endl;
			if (sum == 7) {
				return -1;
			}
			if (roll == sum) {
				return 1;
			}
		}
	}
}

void playGame(int *credits) {
	int wager;
	std::cout << "You have " << *credits << " credits. How much do you wager? ";
	std::cin >> wager;

	while (wager < 0 || wager > *credits) {
		std::cout << "Please enter a value in range (0, " << *credits << "] :";
		std::cin >> wager;
	}
	int winner = gameThrow();
	*credits = *credits + (wager * winner);
	if (winner == 1) {
		std::cout << "Player Wins" << std::endl
				  << std::endl;
		std::cout << "You have won " << wager << " credits. Your new balance is now " << *credits << " credits" << std::endl;
	}
	else {
		std::cout << "Player Loses" << std::endl
				  << std::endl;
		std::cout << "You have lost " << wager << " credits. Your new balance is now " << *credits << " credits" << std::endl;
	}
}

int main() {
	char ans;
	bool done = false;
	int credits = DEFAULT_CREDITS;
	while (!done) {
		playGame(&credits); // YOU MUST WRITE THIS FUNCTION
		if (credits == 0) {
			std::cout << "your a broke boy\n";
			return 0;
		}
		std::cout << " Play again (y/n) ? ";
		std::cin >> ans;
		if (ans == 'n' || ans == 'N')
			done = true;
		else
			done = false;
	}
	return 0;
}
