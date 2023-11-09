#include <cstdio>
#include <cctype>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <format>

using namespace std;


typedef struct DICTION{
    vector< pair <string, int> > nodes;
} DICTION;

DICTION d;


DICTION buildDictionary(string filePath);
void sortDiction(DICTION &d);
void printHorzHistogram(const DICTION &d);
void printVertHistogram(const DICTION &d);
void printDictionary(const DICTION &d);


void addToDiction(string s){

    cout << s << endl;

    if(d.nodes.size() == 0){
        d.nodes.push_back(make_pair(s, 1));
        return;
    }

    for(unsigned int i = 0; i < d.nodes.size(); i++){
        if(s.compare(d.nodes.at(i).first) == 0){
            d.nodes.at(i).second++;
            return;
        }
    }
    d.nodes.push_back(make_pair(s, 1));
    
}

DICTION buildDictionary(){
    
    string s;
    char ch;

    while(cin.good()){
        ch = cin.get();
        cout << "char: "<< int(ch) << endl;
        if(isalpha(ch)){
            if(isupper(ch)){
                s.push_back(tolower(ch));
            } else if(islower(ch)){
                s.push_back(ch);
            }
        } else{
            if(s.compare("") != 0){
                cout << "end of string" << endl;
                addToDiction(s);
                s.clear();
            }
        }
    }
    if(s.compare("") != 0){
        addToDiction(s);
    }

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
        for(unsigned int i = 0; i < maxStringSize; i++){
            cout << "  ";
        }
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
    for(unsigned int i = 0; i < d.nodes.size() + maxStringSize; i++){
        cout << "--";
    }
    cout << endl;

    int increment = 0;
    for(unsigned int i = 0; i < d.nodes.size(); i++){
        cout << std::format("{0:5}", d.nodes.at(i).first);

        for(unsigned int i = 0; i < maxStringSize - 1 + increment; i++){
            cout << "--";
        }
        cout << '/';
        
        cout << endl;
        increment++;
    }

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
    for(unsigned int i = 0; i < d.nodes.size(); i++){
        cout << d.nodes.at(i).first << "   " << d.nodes.at(i).second << endl;
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