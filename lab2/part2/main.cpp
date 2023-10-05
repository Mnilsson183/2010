/*
    Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by overpopulation.
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <iostream>
#include <ncurses.h>

using namespace std;

const int HEIGHT = 40;
const int WIDTH = 100;
bool display[HEIGHT][WIDTH];

void printDisplay(){
    for(int i = 0; i < WIDTH + 1; i++){
        cout << "_";
    }
    cout << endl;
    for(int i = 0; i < HEIGHT; i++){
        if(i != 0) cout << endl;
        for(int j = 0; j < WIDTH; j++){
            if (display[i][j] == false){
                cout << ' ';
            } else{
                cout << "*";
            }
        }
        cout << "|";
    }
    cout << endl;
    for(int i = 0; i < WIDTH + 1; i++){
        cout << "¯";
    }
    cout << endl;
}


void generation(){
    bool tempDisplay[HEIGHT][WIDTH];
}

int main(void){
    // init to blanks
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            display[i][j] = false;
        }
    }
    display[HEIGHT / 2][WIDTH / 2] = true;


    while(true){
        printDisplay();
        char c = cin.get();
        if (c == 'q'){
            return 0;
        }
        generation();
    }
}