// Copyright 2024 Morgan Nilsson
#include "./func.h"
#include <iostream>

int main(void) {
	int maxgen = 0;
	while (maxgen <= 0) {
		std::cout << "Please enter a max generations: ";
		std::cin >> maxgen;
	}
	Mat front(HEIGHT, std::vector<bool>(WIDTH, false));
	Mat back(HEIGHT, std::vector<bool>(WIDTH, false));

	init_board(front);

	int gen = 0;
	printDisplay(front, 0);
	time_t last = time(NULL);
	while(gen <= maxgen) {
		while(difftime(time(NULL), last)) {
			generation(front, back);
			front = back;
			printDisplay(front, ++gen);
			last = time(NULL);
		}
	}
	endwin();
}
