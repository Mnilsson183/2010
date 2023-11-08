#include <cstdio>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>

using namespace std;


typedef struct DICTION{
    vector<pair<string, int>> nodes;
} DICTION;

DICTION d;


DICTION buildDictionary(string filePath);
void sortDiction(DICTION &d);
void printHorzHistogram(const DICTION &d);
void printVertHistogram(const DICTION &d);
void printDictionary(const DICTION &d);


void addToDiction(string s){

    if(d.nodes.size() == 0){
        d.nodes.push_back(make_pair(s, 0));
        return;
    }

    for(unsigned int i = 0; i < d.nodes.size(); i++){
        if(d.nodes.at(i).first.compare(s) == 0){
            d.nodes.at(i).second++;
        } else{
            d.nodes.push_back(make_pair(s, 0));
        }
    }
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
        } else{
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
    int maxUsage = 0;
    for(auto element : d.nodes){
        if(element.second > maxUsage){
            maxUsage = element.second;
        }
    }

    // find the longest string
    unsigned int maxStringSize = 0;
    for(auto element : d.nodes){
        if(element.first.size() > maxStringSize){
            maxStringSize = element.first.size();
        }
    }

    int column = maxUsage;
    while (column > 0){
        for(auto element : d.nodes){
            if(element.second >= column){
                cout << "* ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
        column--;
    }
    for(unsigned int i = 0; i < d.nodes.size(); i++){
        cout << "--";
    }
    cout << endl;

}

void printVertHistogram(const DICTION &d){
    for(auto element:d.nodes){
        cout << element.first << "   " << '|';
        int displaySize = (element.second <= 20) ? element.second : 20;
        for(int i = 0 ; i < displaySize; i++){
            cout << '*';
        }
        if(element.second > 20){
            cout << " (" << element.second - 20 << ')'; 
        }
        cout << endl;
    }
    cout << endl;
}

void printDictionary(const DICTION &d){
    cout << "Dictionary" << endl << endl;
    cout << "Word" << "  " << "Frequency" << endl;
    cout << "-------------------------" << endl;
    for(auto element :d.nodes){
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