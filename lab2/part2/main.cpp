#include <iostream>
#include <ncurses.h>

using namespace std;

const int HEIGHT = 40;
const int WIDTH = 100;
bool display[HEIGHT][WIDTH];
bool nextDisplay[HEIGHT][WIDTH];

void printDisplay(){
    for(int i = 0; i < WIDTH + 1; i++){
        cout << "_";
    }
    cout << endl;
    for(int i = 0; i < HEIGHT; i++){
        if(i != 0) cout << endl;
        cout << " |";
        for(int j = 0; j < WIDTH; j++){
            if (nextDisplay[i][j] == false){
                cout << ' ';
            } else{
                cout << '*';
            }
        }
        cout << "|";
    }
    cout << endl;
    for(int i = 0; i < WIDTH + 1; i++){
        cout << "¯";
    }
    cout << endl;

    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            display[i][j] = nextDisplay[i][j];
        }
    }
}

void checkNext(int y, int x){
    short numberOfFriends
    // straight angles
    if (y - 1 >= 0){
        if(display[y - 1][x] == true) numberOfFriends++;
    }
    if(y + 1 <= HEIGHT - 1){
        if(display[y + 1][x] == true) numberOfFriends++;
    }
    if(x - 1 >= 0){
        if(display[y][x - 1] == true) numberOfFriends++;
    }
    if(x + 1 <= WIDTH - 1){
        if(display[y][x + 1] == true) numberOfFriends++;
    }

    // corners
    if ((y - 1 >=0) && (x - 1 >= 0)){
        if(display[y - 1][x - 1] == true) numberOfFriends++;
    }
    if ((y + 1 <= HEIGHT) && (x + 1 <= WIDTH)){
        if(display[y + 1][x + 1] == true) numberOfFriends++;
    }
    if ((y - 1 >= 0) && (x + 1 <= WIDTH)){
        if(display[y - 1][x + 1] == true) numberOfFriends++;
    }
    if ((y + 1 <= HEIGHT) && (x - 1 >= 0)){
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
    else if((alive) && (numberOfFriends == 2 || numberOfFriends == 3)) nextDisplay[y][x] = true;
    else if((alive) && numberOfFriends > 3) nextDisplay[y][x] = false;
    else if((!alive) && numberOfFriends == 3) nextDisplay[y][x] = true;

}

void generation(){

    for (int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            checkNext(i, j);
        }
    }
}

int main(void){
    // the first display to all blanks
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            display[i][j] = false;
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
        char c = cin.get();
        if (c == 'q'){
            return 0;
        }
        generation();
        printDisplay();
    }
}