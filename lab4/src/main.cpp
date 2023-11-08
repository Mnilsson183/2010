#include <cstdio>
#include <cctype>
#include <iostream>
#include <string>
#include <map>

using namespace std;


typedef struct DICTION{
    map<string, int> section;    
} DICTION;

DICTION d;


DICTION buildDictionary(string filePath);
void sortDiction(DICTION &d);
void printHorzHistogram(const DICTION &d);
void printVertHistogram(const DICTION &d);
void printDictionary(const DICTION &d);


void addToDiction(string s){
    d.section[s]++;
}

DICTION buildDictionary(){
    

    string s;
    char ch;

    while(cin.good()){
        ch = cin.get();
        if(isalpha(ch)){
            if(isupper(ch)){
                s.push_back(tolower(ch));
            } else{
                s.push_back(ch);
            }
        } else if (ch == ' '){
            addToDiction(s);
            s.clear();
        }
    }
    addToDiction(s);

    return d;
}

void sortDiction(DICTION &d){
    
}

void printHorzHistogram(const DICTION &d){
    // find the max amount of usage
    int max = 0;
    for(auto element : d.section){
        if(element.second > max){
            max = element.second;
        }
    }

    
}

void printVertHistogram(const DICTION &d){
    for(auto element:d.section){
        cout << element.first << "   " << '|';
        for(int i = 0 ; i < element.second; i++){
            cout << '*';
        }
        cout << endl;
    }
    cout << endl;
}

void printDictionary(const DICTION &d){
    cout << "Dictionary" << endl << endl;
    cout << "Word" << "  " << "Frequency" << endl;
    cout << "-------------------------";
    for(auto element :d.section){
        cout << element.first << "    " << element.second << endl;
    }
    cout << endl;
}

int main(){

    d = buildDictionary();


    printDictionary(d);
    printHorzHistogram(d);
    printVertHistogram(d);
    sortDiction(d /*pass the pointer to compare func for strings*/);
    printDictionary(d);
    sortDiction(d /*pass the pointer to compare func for ints*/);
    printDictionary(d);

    return 0;
}