#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

typedef struct DICTION{

} DICTION;

String getNextWord();
DICTION buildDictionary();
void sortDiction(DICTION &d);
void printHorzHistogram(const DICTION &d);
void printVertHistogram(const DICTION &d);
void printDictionary(const DICTION &d);

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "./main [file]"
    }

    DICTION d;

    d = buildDictionary();
    printDictionary();
    printHorzHistogram();
    printVertHistogram();
    sortDiction(d, /*pass the pointer to compare func for strings*/);
    printDictionary();
    sortDiction(d, /*pass the pointer to compare func for ints*/);
    printDictionary();

    return 0;

}