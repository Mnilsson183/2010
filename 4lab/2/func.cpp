// Copyright 2024 Morgan Nilsson
#include "./func.h"
#include <ncurses.h>
#include <iostream>

#define DEFAULT_HEIGHT 24
#define DEFAULT_WIDTH 80
#define DEFAULT_TIMEOUT 100

int count(const Mat& display, int height, int width) {
	int count = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (display[i][j]) count++;
		}
	}
	return count;
}

void printDisplay(const Mat& display, int gen, int height, int width) {
	clear();
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			if (display[h][w]) {
				mvprintw(h, w, LIVE);
			}
		}
		mvprintw(h, width, "#");
	}
	if (width > 11) mvprintw(height, 0, "C is better");
	for (int i = 0; i < width + 1; i++) {
		mvprintw(height, i, "#");
	}
	mvprintw(0, 0, "Generation: %d", gen);
	mvprintw(1, 0, "n: %d", count(display, height, width));
	mvprintw(2, 0, "'q' to exit");
	refresh();
}

void populate(int y, int x, Mat& next, const Mat& display, int height, int width) {
	u_int16_t numberOfFriends = 0;

	if (y - 1 >= 0) {
		if (display[y - 1][x]) numberOfFriends++;
	}
	if (y + 1 <= height - 1) {
		if (display[y + 1][x]) numberOfFriends++;
	}
	if (x - 1 >= 0) {
		if (display[y][x - 1]) numberOfFriends++;
	}
	if (x + 1 <= width - 1) {
		if (display[y][x + 1]) numberOfFriends++;
	}

	if ((y - 1 >= 0) && (x - 1 >= 0)) {
		if (display[y - 1][x - 1]) numberOfFriends++;
	}
	if ((y + 1 <= height - 1) && (x + 1 <= width - 1)) {
		if (display[y + 1][x + 1]) numberOfFriends++;
	}
	if ((y - 1 >= 0) && (x + 1 <= width - 1)) {
		if (display[y - 1][x + 1]) numberOfFriends++;
	}
	if ((y + 1 <= height - 1) && (x - 1 >= 0)) {
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

void generation(const Mat& last, Mat& next, int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			populate(i, j, next, last, height, width);
		}
	}
}

void init_board(Mat& mat, int height, int width) {
	MEVENT event;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	mouseinterval(3);
	mousemask(ALL_MOUSE_EVENTS, NULL);
	nodelay(stdscr, true);

	printDisplay(mat, 0, height, width);
	mvprintw(2, 0, "Please Populate screen press 'q' to exit");

	int count = 0;
	while (1) {
		int c = getch();
		if (c == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					if (event.y < height - 1 && event.x < width - 1
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

void runGOL(int height, int width, int timeout_time) {
	int maxgen = 0;
	while (maxgen <= 0) {
		std::cout << "Please enter a max generations: ";
		std::cin >> maxgen;
	}
	if (!height) height = DEFAULT_HEIGHT;
	if (!width) width = DEFAULT_WIDTH;
	if (!timeout_time) timeout_time = DEFAULT_TIMEOUT;
	Mat front(height, std::vector<bool>(width, false));
	Mat back(height, std::vector<bool>(width, false));

	init_board(front, height, width);

	int gen = 0;
	printDisplay(front, 0, height, width);
	while(gen <= maxgen && getch() != 'q') {
		generation(front, back, height, width);
		front = back;
		printDisplay(front, ++gen, height, width);
		timeout(timeout_time);
	}
	endwin();
}
