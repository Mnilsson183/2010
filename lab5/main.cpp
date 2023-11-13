#include <iostream>
#include <cctype>
#include <string>
#include <func.h>

using namespace std;

int main(void){
    
    string command;
    while(true){
        cin >> command;

        if(parse(command) == 1){
            cout << endl <<"Good bye" << endl;
            return;
        }

    }
}