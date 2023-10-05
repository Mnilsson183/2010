#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;


int credits = 100;
int die1;
int die2;


int die(){
    return rand() % 6 + 1;
}

int gameThrow(void){
    // ret 1 if player and 2 if house
    const int DICELENGTH = 2;
    int* dice = new int[DICELENGTH];
    for (int i = 0; i < DICELENGTH; i++){
        dice[i] = die();
    }

    // first roll
    int sum = dice[0] + dice[1];
    cout << endl << "player rolled " << dice[0] << " + " << dice[1] << " = " << sum << endl;
    if (sum == 7 || sum == 11){
        return 1;
    } else if(sum == 2 || sum == 3 || sum == 12){
        return -1;
    } else{
        int roll = sum;
        cout << "The point is set at " << roll << endl;
        while (true){
            for (int i = 0; i < DICELENGTH; i++){
                dice[i] = die();
            }
            die1 = dice[0];
            die2 = dice[1];
            sum = dice[0] + dice[1];
            cout << "player rolled " << dice[0] << " + " << dice[1] << " = " << sum << endl;
            if (sum == 7){
                return -1;
            }
            if (roll == sum){
                return 1;
            }
        }
    }
}
void playGame(void){
    int wager;
    cout << "You have " << credits << " credits. How much do you wager? ";
    cin >> wager;
    int winner = gameThrow();
    credits = credits + (wager * winner);
    if (winner == 1){
        cout << "Player Wins" << endl << endl;
        cout << "You have won " << wager << " credits. Your new balance is now " << credits << " credits";
    } else {
        cout << "Player Loses" << endl << endl;
        cout << "You have lost " << wager << " credits. Your new balance is now " << credits << " credits" << endl;
    }

}

int main(void){
    char ans;
    bool done = false;
    srand(time(NULL));
    while(!done){
        playGame();
        cout << "Play again (Y/N)? ";
        cin >> ans;
        if (ans == 'n' || ans == 'N'){
            done = true;
        } else{
            done = false;
        }
    }
    return 0;
}