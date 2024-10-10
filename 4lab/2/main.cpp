// Copyright 2024 Morgan Nilsson
#include "./func.h"

int main(void) {
	Mat vec1(HEIGHT, std::vector<bool>(WIDTH, false));
	Mat vec2(HEIGHT, std::vector<bool>(WIDTH, false));
	Mat &front = vec1;
	Mat &back = vec2;

	init_board(front);

	int gen = 0;
	printDisplay(vec1, 0);
	while (true) {
		if (getch() == 'q') {
			endwin();
			return 0;
		} else {
			generation(front, back);
			front = back;
			printDisplay(front, ++gen);
		}
	}
}