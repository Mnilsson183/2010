#include <ncurses.h>

#define HEIGHT 40
#define WIDTH 90

/*
	Display is for the current state of the program
	NextDisplay is the intermediate state of the program before pushing to display
*/

int count(bool display[HEIGHT][WIDTH]) {
	int count = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (display[i][j] == true) count++;
		}
	}
	return count;
}

void printDisplay(bool display[HEIGHT][WIDTH], int gen) {
	clear();
	mvprintw(0, 0, "Generation: %d", gen);
	mvprintw(1, 0, "n: %d", count(display));
	for (int h = 0; h < HEIGHT; h++) {
		for (int w = 0; w < WIDTH; w++) {
			if (display[h][w]) {
				mvprintw(h, w, "*");
			}
		}
		mvprintw(h, WIDTH, "#");
	}
	for (int i = 0; i < WIDTH; i++) {
		mvprintw(HEIGHT, i, "#");
	}
	refresh();
}

void populate(int y, int x, bool *alive, bool display[HEIGHT][WIDTH]) {
	short numberOfFriends = 0;

	// straights
	if (y - 1 >= 0) {
		if (display[y - 1][x] == true)
			numberOfFriends++;
	}
	if (y + 1 <= HEIGHT - 1) {
		if (display[y + 1][x] == true)
			numberOfFriends++;
	}
	if (x - 1 >= 0) {
		if (display[y][x - 1] == true)
			numberOfFriends++;
	}
	if (x + 1 <= WIDTH - 1) {
		if (display[y][x + 1] == true)
			numberOfFriends++;
	}

	// corners
	if ((y - 1 >= 0) && (x - 1 >= 0)) {
		if (display[y - 1][x - 1] == true)
			numberOfFriends++;
	}
	if ((y + 1 <= HEIGHT - 1) && (x + 1 <= WIDTH - 1)) {
		if (display[y + 1][x + 1] == true)
			++numberOfFriends;
	}
	if ((y - 1 >= 0) && (x + 1 <= WIDTH - 1)) {
		if (display[y - 1][x + 1] == true)
			numberOfFriends++;
	}
	if ((y + 1 <= HEIGHT - 1) && (x - 1 >= 0)) {
		if (display[y + 1][x - 1] == true)
			numberOfFriends++;
	}

	*alive = display[y][x];

	/*
		Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
		Any live cell with two or three live neighbors lives on to the next generation.
		Any live cell with more than three live neighbors dies, as if by overpopulation.
		Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
	*/

	if (*alive) {
		if (numberOfFriends < 2)
			*alive = false;
		else if (numberOfFriends > 3)
			*alive = false;
		else
			*alive = true; // I dont need this line but nice to read
	}
	else {
		if (numberOfFriends == 3)
			*alive = true;
	}
}

void generation(bool last[HEIGHT][WIDTH], bool next[HEIGHT][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			populate(i, j, &next[i][j], last);
		}
	}
}

int main(void) {
	MEVENT event;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	mouseinterval(3);
	mousemask(ALL_MOUSE_EVENTS, NULL);

	// what is the heap
	bool buf1[HEIGHT][WIDTH];
	bool buf2[HEIGHT][WIDTH];
	auto curr = &buf1;
	auto next = &buf2;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			buf1[i][j] = false;
		}
	}

	for (int h = 0; h < HEIGHT; h++) {
		mvprintw(h, WIDTH, "#");
	}

	for (int i = 0; i < WIDTH; i++) {
		mvprintw(HEIGHT, i, "#");
	}

	while (1) {
		int c = getch();
		if (c == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					if (event.y < HEIGHT - 1 && event.x < WIDTH - 1 && event.y >= 0 && event.x >= 0) {
						if (buf1[event.y][event.x] == false) {
							buf1[event.y][event.x] = true;
							mvprintw(event.y, event.x, "*");
						} else {
							buf1[event.y][event.x] = false;
							mvprintw(event.y, event.x, " ");
						}
						refresh();
					}
				}
			}
		}
		if (c == 'q')
			break;
	}
	int gen = 0;

	// display the first frame of the simulation
	printDisplay(buf1, gen);
	while (true) {
		if (getch() == 'q') {
			endwin();
			return 0;
		}
		else {
			generation(*curr, *next);
			gen++;
			curr = next;
			printDisplay(*curr, gen);
		}
	}
}
