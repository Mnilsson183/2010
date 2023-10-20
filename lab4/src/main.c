#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
int MAX_WORDS = 1000;

typedef struct DICTION_NODE
{
    string word = NULL;
    int occurrences = NULL;
} DICTION_NODE;

typedef struct DICTION{
    DICTION_NODE nodes[MAX_WORDS];
} DICTION;


DICTION buildDictionary(string filePath);
int hash(string name);
void sortDiction(DICTION &d);
void printHorzHistogram(const DICTION &d);
void printVertHistogram(const DICTION &d);
void printDictionary(const DICTION &d);

DICTION buildDictionary(string filePath){
    FILE infile = fopen(filePath, "r");
    if(!infile){
        printf("File was unable to be opened\n");
        return NULL;
    }
    DICTION* dictionary = malloc(sizeof(DICTION));
    while(fscanf(infile, "%s", str) == 1){
        DICTION_NODE* cursor = dictionary[hash(name)];
        if(cursor->word == NULL){
            cursor->word = str;
            cursor->occurrences = 1;
        } else{
            cursor->occurrences++;
        }
    }
    return dictionary;
}

int hash(string name){
    int index = 0;
    int sum = 0;
    while(name[index] != '\0'){
        sum = sum + name[index];
        index++;
    }
    return sum % MAX_WORDS;
}

void sortDiction(DICTION &d){
    
}

void printHorzHistogram(const DICTION &d){

}

void printVertHistogram(const DICTION &d){

}

void printDictionary(const DICTION &d){

}

int main(int argc, char **argv){
    if(argc != 2){
        printf("USAGE ./build/main [infile]\n");
        return -1;
    }
    static string FILEPATH = argv[1];

    DICTION d;

    d = buildDictionary(FILEPATH);
    if(d == NULL){
        return -1;
    }
    printDictionary(d);
    printHorzHistogram(d);
    printVertHistogram(d);
    sortDiction(d /*pass the pointer to compare func for strings*/);
    printDictionary(d);
    sortDiction(d /*pass the pointer to compare func for ints*/);
    printDictionary(d);

    return 0;
}