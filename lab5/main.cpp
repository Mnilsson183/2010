#include <iostream>
#include <cctype>
#include <string>
#include <func.h>

using namespace std;

int main(int argc, char* argv){

    if(argc != 2){
        cout << "USAGE: <command> Target or CLOSE";
        return -1;
    }
    if(buildDB(argv[1]) == -1){
        cout << "Error building database";
        return -1;
    }
    
    string command;
    while(true){
        cin >> command;

        if(parseCommand(command) == 1){
            cout << endl <<"Good bye" << endl;
            return;
        }

    }
}