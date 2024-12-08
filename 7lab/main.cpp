// Copyright 2024 Morgan Nilsson
#include "dict.hpp"

int main(void) {
	DICTION dict;
	initDiction(dict);

	WORD word = getNextWord(dict);
	while(!word.empty()) {
		insertWord(word, dict);
		word = getNextWord(dict);
	}

	printDictionary(dict);
	printStats(dict);
	printLetterFreq(dict);
	printDictionaryFreq(dict);
	printHistogram(dict);

	return 0;
}
