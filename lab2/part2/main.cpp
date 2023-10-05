/*
    Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by overpopulation.
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
#include <iostream>
#include <ncurses.h>

using namespace std;

void generation(){

}

int main(void){
    while(true){
        generation();
        getch();
        if (int c = 3 == 'q'){
            return 0;
        }
    }
}