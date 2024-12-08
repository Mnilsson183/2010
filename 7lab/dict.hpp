#include <set>
#include <map>
#include <queue>
#include <string>
#include <string>

struct funcObj {
    bool operator()(const std::string& a, const std::string& b) { return a.length() < b.length(); }
};
using WORD = std::string;
using WORD_LIST = std::set<WORD>;
using WORD_FREQ_LIST = std::map<char,int>;
using FREQ_WORD_LIST = std::multimap<int,WORD>;
using COUNTER = std::tuple<int,int,int>;
using LONGEST = std::priority_queue<WORD,std::vector<WORD>,funcObj>;

struct DICTION {
	COUNTER stats;
	WORD_LIST words;
	WORD_FREQ_LIST wordFreq;	// letter freq
	FREQ_WORD_LIST freqWord;	// word freq
	LONGEST longWord;
};

WORD getNextWord(DICTION &d);
void printDictionary(const DICTION &d);
void printDictionaryFreq(const DICTION &d);
void printLetterFreq(const DICTION &d);
void printHistogram(const DICTION &d);
void initDiction(DICTION &d);
void printStats(const DICTION &d);
void insertWord(WORD word, DICTION &d);
