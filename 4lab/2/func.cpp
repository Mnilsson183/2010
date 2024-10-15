// Copyright 2024 Morgan Nilsson
#include "./func.h"

int count(const Mat& display) {
	int count = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (display[i][j]) count++;
		}
	}
	return count;
}

void printDisplay(const Mat& display, int gen) {
	clear();
	for (int h = 0; h < HEIGHT; h++) {
		for (int w = 0; w < WIDTH; w++) {
			if (display[h][w]) {
				mvprintw(h, w, LIVE);
			}
		}
		mvprintw(h, WIDTH, "#");
	}
	if (WIDTH > 11) mvprintw(HEIGHT, 0, "C is better");
	for (int i = 0; i < WIDTH + 1; i++) {
		mvprintw(HEIGHT, i, "#");
	}
	mvprintw(0, 0, "Generation: %d", gen);
	mvprintw(1, 0, "n: %d", count(display));
	refresh();
}

void populate(int y, int x, Mat& next, const Mat& display) {
	u_int16_t numberOfFriends = 0;

	if (y - 1 >= 0) {
		if (display[y - 1][x]) numberOfFriends++;
	}
	if (y + 1 <= HEIGHT - 1) {
		if (display[y + 1][x]) numberOfFriends++;
	}
	if (x - 1 >= 0) {
		if (display[y][x - 1]) numberOfFriends++;
	}
	if (x + 1 <= WIDTH - 1) {
		if (display[y][x + 1]) numberOfFriends++;
	}

	if ((y - 1 >= 0) && (x - 1 >= 0)) {
		if (display[y - 1][x - 1]) numberOfFriends++;
	}
	if ((y + 1 <= HEIGHT - 1) && (x + 1 <= WIDTH - 1)) {
		if (display[y + 1][x + 1]) numberOfFriends++;
	}
	if ((y - 1 >= 0) && (x + 1 <= WIDTH - 1)) {
		if (display[y - 1][x + 1]) numberOfFriends++;
	}
	if ((y + 1 <= HEIGHT - 1) && (x - 1 >= 0)) {
		if (display[y + 1][x - 1]) numberOfFriends++;
	}

	/*
		Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
		Any live cell with two or three live neighbors lives on to the next generation.
		Any live cell with more than three live neighbors dies, as if by overpopulation.
		Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
	*/

	next[y][x] = display[y][x];

	if (next[y][x]) {
		if (numberOfFriends < 2)
			next[y][x] = false;
		else if (numberOfFriends > 3)
			next[y][x] = false;
		else
			next[y][x] = true;
	} else {
		if (numberOfFriends == 3)
			next[y][x] = true;
	}
}

void generation(const Mat& last, Mat& next) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			populate(i, j, next, last);
		}
	}
}

void init_board(Mat& mat) {
	MEVENT event;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	mouseinterval(3);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	printDisplay(mat, 0);
	mvprintw(2, 0, "Please Populate screen press 'q' to exit");

	int count = 0;
	while (1) {
		int c = getch();
		if (c == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					if (event.y < HEIGHT - 1 && event.x < WIDTH - 1
					&& event.y >= 0 && event.x >= 0) {
						if (mat[event.y][event.x] == false) {
							mat[event.y][event.x] = true;
							mvprintw(event.y, event.x, LIVE);
							count++;
						} else {
							mat[event.y][event.x] = false;
							mvprintw(event.y, event.x, " ");
							count--;
						}
						mvprintw(1, 0, "n: %d", count);
						mvprintw(2, 0, "Please Populate screen");
						refresh();
					}
				}
			}
		}
		if (c == 'q') break;
	}
}
