#include <ncurses.h>

#define HEIGHT 40
#define WIDTH 90

/*
    Display is for the current state of the program 
    NextDisplay is the intermediate state of the program before pushing to display
*/


void printDisplay(bool display[HEIGHT][WIDTH], int gen){
	clear();
	mvprintw(0, 0, "Generation: %d", gen);
	for (int h = 0; h < HEIGHT; h++) {
		for (int w = 0; w < WIDTH; w++) {
			if (display[h][w]) {
				mvprintw(h + 1, w, "*");
			}
		}
	}
	refresh();
}

void populate(int y, int x, bool* alive, bool display[HEIGHT][WIDTH]) {
	short numberOfFriends = 0;

    // straight angles
	if (y - 1 >= 0){
		if(display[y - 1][x] == true) numberOfFriends++;
	}
	if(y + 1 <= HEIGHT - 1) {
		if(display[y + 1][x] == true) numberOfFriends++;
	}
	if(x - 1 >= 0) {
		if(display[y][x - 1] == true) numberOfFriends++;
	}
	if(x + 1 <= WIDTH - 1) {
		if(display[y][x + 1] == true) numberOfFriends++;
	}

	// corners
	if ((y - 1 >=0) && (x - 1 >= 0)){
		if(display[y - 1][x - 1] == true) numberOfFriends++;
	}
	if ( ( y + 1 <= HEIGHT - 1 ) && ( x + 1 <= WIDTH - 1 ) ){
		if(display[y + 1][x + 1] == true) ++numberOfFriends;
	}
	if ((y - 1 >= 0) && (x + 1 <= WIDTH - 1)){
		if(display[y - 1][x + 1] == true) numberOfFriends++;
	}
	if ((y + 1 <= HEIGHT - 1) && (x - 1 >= 0)){
		if(display[y + 1][x - 1] == true) numberOfFriends++;
	}

	*alive = display[y][x];

	/*
	    Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
	    Any live cell with two or three live neighbors lives on to the next generation.
	    Any live cell with more than three live neighbors dies, as if by overpopulation.
	    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
	*/

	if (*alive) {
		if (numberOfFriends < 2) *alive = false;
		else if (numberOfFriends > 3) *alive = false;
		else *alive = true; // I dont need this line but nice to read
	} else {
		if (numberOfFriends == 3) *alive = true;
	}
}

void generation(bool last[HEIGHT][WIDTH], bool next[HEIGHT][WIDTH]){
    for (int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
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

	bool buf1[HEIGHT][WIDTH];
	bool buf2[HEIGHT][WIDTH];
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			buf1[i][j] = false;
		}
	}

	while(1) {
		int c = getch();
		if (c == KEY_MOUSE) {
			if (getmouse(&event) == OK) {
				if (event.bstate & BUTTON1_PRESSED) {
					buf1[event.y][event.x] = true;
					mvprintw(event.y, event.x, "*");
					refresh();
				}
			}
		}
		if (c == 'q') break;
	}
	int gen = 0;

	// display the first frame of the simulation
    	printDisplay(buf1, 0);
    	while(true){
    	    	if (getch() == 'q'){
			endwin();
			return 0;
    	    	} else {
			generation(buf1, buf2);
    	    		gen++;
			printDisplay(buf1, gen);
		}
    	}
}
