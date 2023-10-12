#include <iostream>
#include <ncurses.h>

using namespace std;

const int HEIGHT = 40;
const int WIDTH = 100;
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
        printw(" |");
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
    refresh();
}

void checkNext(int y, int x){
    short numberOfFriends;
    // straight angles
    if (y - 1 >= 0){
        if(display[y - 1][x] == true) numberOfFriends++;
        //cout << "Cell at" << x << ',' << y << "has a friend down one" << endl;
    }
    if(y + 1 <= HEIGHT - 1){
        if(display[y + 1][x] == true) numberOfFriends++;
        //cout << "Cell at" << x << ',' << y << "has a friend up one" << endl;
    }
    if(x - 1 >= 0){
        if(display[y][x - 1] == true) numberOfFriends++;
        //cout << "Cell at" << x << ',' << y << "has a friend left one" << endl;
    }
    if(x + 1 <= WIDTH - 1){
        if(display[y][x + 1] == true) numberOfFriends++;
        //cout << "Cell at" << x << ',' << y << "has a friend right one" << endl;
    }

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

    // Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
    if (numberOfFriends < 2) nextDisplay[y][x] = false;
    else if((alive == true) && (numberOfFriends == 2 || numberOfFriends == 3)) nextDisplay[y][x] = true;
    else if((alive == false) && numberOfFriends == 3) nextDisplay[y][x] = true;
    else if((alive == true) && numberOfFriends > 3) nextDisplay[y][x] = false;

    if (nextDisplay[y][x]){
        //cout << "Cell at " << x << ',' << y << "  NUMBER OF FRIENDS: " << numberOfFriends << " ALIVE LAST? " <<  alive << " ALIVE NEXT? " << nextDisplay[y][x] << endl;
    }
    if (alive){

    }

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

int main(void){
    initscr();
    // the first display to all blanks
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            display[i][j] = false;
        }
    }
    // some small test cases
    display[HEIGHT / 2][WIDTH / 2] = true;
    display[10][10] = true;
    display[11][11] = true;
    display[10][11] = true;
    display[11][10] = true;

    // display the first frame of the simulation
    printDisplay();
    // run the quit logic
    while(true){
        char c;
        c = getch();
        if (c == 'q'){
            endwin();
            return 0;
        }
        generation();
        printDisplay();
    }
    endwin();
}