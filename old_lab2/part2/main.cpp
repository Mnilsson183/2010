#include <iostream>
#include <ncurses.h>

using namespace std;

const short HEIGHT = 40;
const short WIDTH = 90;
int gen = 0;

/*
    Display is for the current state of the program 
    NextDisplay is the intermediate state of the program before pushing to display
*/

bool display[HEIGHT][WIDTH];
bool nextDisplay[HEIGHT][WIDTH];

void printDisplay(){
    erase();
    for(int i = 0; i < WIDTH + 1; i++){
        printw("_");
    }
    printw("\n");
    for(int i = 0; i < HEIGHT; i++){
        if(i != 0) printw("\n");
        printw("|");
        for(int j = 0; j < WIDTH; j++){
            if (display[i][j] == false){
                printw(" ");
            } else{
                printw("*");
            }
        }
        printw("|");
    }
    printw("\n");
    for(int i = 0; i < WIDTH + 1; i++){
        printw("¯");
    }
    printw("\n");
    printw("Generation %d.", gen);
    refresh();
}

void checkNext(int y, int x){
    short numberOfFriends = 0;

    // straight angles
    if (y - 1 >= 0)           if(display[y - 1][x] == true) numberOfFriends++;
    if(y + 1 <= HEIGHT - 1)   if(display[y + 1][x] == true) numberOfFriends++;
    if(x - 1 >= 0)            if(display[y][x - 1] == true) numberOfFriends++;
    if(x + 1 <= WIDTH - 1)    if(display[y][x + 1] == true) numberOfFriends++;

    // corners
    if ((y - 1 >=0) && (x - 1 >= 0)){
        if(display[y - 1][x - 1] == true) numberOfFriends++;
    }
    if ((y + 1 <= HEIGHT - 1) && (x + 1 <= WIDTH - 1)){
        if(display[y + 1][x + 1] == true) numberOfFriends++;
    }
    if ((y - 1 >= 0) && (x + 1 <= WIDTH - 1)){
        if(display[y - 1][x + 1] == true) numberOfFriends++;
    }
    if ((y + 1 <= HEIGHT - 1) && (x - 1 >= 0)){
        if(display[y + 1][x - 1] == true) numberOfFriends++;
    }
    bool alive = display[y][x];

/*
    Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by overpopulation.
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

    if (numberOfFriends < 2) nextDisplay[y][x] = false;
    else if((alive == true) && (numberOfFriends == 2 || numberOfFriends == 3)) nextDisplay[y][x] = true;
    else if((alive == false) && numberOfFriends == 3) nextDisplay[y][x] = true;
    else if((alive == true) && numberOfFriends > 3) nextDisplay[y][x] = false;
}

void generation(){

    for (int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            checkNext(i, j);
        }
    }

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            display[i][j] = nextDisplay[i][j];
        }
    }
}

void checkDisplayToPaste(int mouse_x, int mouse_y){
    for(int y = 0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            if((y == mouse_y) && (x == mouse_x)){
                display[y][x] = true;
                printDisplay();
                return;
            }
        }
    }
}

int makeInitLayout(void){
    printw("Please make inital configuration");

    mousemask(BUTTON1_CLICKED, NULL);
    MEVENT event;

    char ch;
    noecho();
    while(true){
        ch = getch();

        checkDisplayToPaste(event.x, event.y);

        if(ch == 'q'){
            gen++;
            printDisplay();
            echo();
            return 0;
        }
    }
}

int main(void){
    initscr();
    // the first display to all blanks
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            display[i][j] = false;
        }
    }

    // display the first frame of the simulation
    printDisplay();
    makeInitLayout();
    char c; 
    // run the quit logic
    while(true){
        mousemask(0, NULL);
        // while(c == KEY_MOUSE){
            c = getch();
        //}
        if (c == 'q'){
            endwin();
            return 0;
        }
        generation();
        gen++;
        printDisplay();
    }
    endwin();
}