// Copyright 2024 Morgan Nilsson
#include "dict.hpp"
#include <iostream>

#define HISTOGRAM_SPACING_SIZE 1

char l;  // im too lazy to put this in its caller it belongs to updateStats
void updateStats(const char c, DICTION &d) {
	if (!isalpha(l) && isalpha(c)) std::get<1>(d.stats)++;
	else if (c =='\n') std::get<2>(d.stats)++;  // nl and whitespace is not letters
	else std::get<0>(d.stats)++;
	l = c;
}

void insertWord(const WORD word, DICTION &d) {
	d.words.insert(word);
	d.longWord.push(word);
	for (auto it = d.freqWord.begin(); it != d.freqWord.end(); it++) {
		if (it->second == word) {
			int freq = it->first;
			d.freqWord.erase(it);
			d.freqWord.insert({++freq, word});
			return;
		}
	}
	d.freqWord.insert({1, word});
}

void printStats(const DICTION &d) {
	std::cout << "Number of Letters : " << std::get<0>(d.stats) << '\n';
	std::cout << "Number of Words   : " << std::get<1>(d.stats) << '\n';
	std::cout << "Number of Lines   : " << std::get<2>(d.stats) << '\n';
}

void printDictionary(const DICTION &d) {
	std::cout << '\n';
	std::cout << "Words in dictionary – ";
	for (auto &el : d.words) {
		std::cout << el;
		if (el != *d.words.end()) std::cout << ", ";
	}
	std::cout << '\n';
}

void printDictionaryFreq(const DICTION &d) {
	std::cout << "\n/------------\\\n| Dictionary |\n\\------------/\n\n";
	std::cout << "Word	     Frequency\n-------------------------\n";
	for (const auto &el : d.freqWord) {
		std::cout << el.second;
		for (size_t i = el.second.size(); i < d.longWord.top().size()+9; i++) {
			std::cout << ' ';
		}
		std::cout << el.first << '\n';
	}
}

void updateLetterFreq(const char ch, DICTION &d) {
	d.wordFreq[ch]= d.wordFreq[ch] + 1;
}

void printLetterFreq(const DICTION &d) {
	std::cout << "\n/--------------\\\n| Letter Freq  |\n\\--------------/\n\n";
	WORD word;
	for (const auto el: d.wordFreq) {
		word = "";
		if (el.second >= 10) {
			word = "********** (" + std::to_string(el.second) + ')';
		} else {
			for (int i = 0; i < el.second; i++) word += "*";
		}
		std::cout << el.first << " |" << word << '\n';
	}
}

void printHistogram(const DICTION &d) {
	std::cout << "\n/------------\\\n| Histogram  |\n\\------------/\n";
	int highFreq = 0;
	int longestWord = d.longWord.top().size();
	for (const auto &el: d.freqWord) {
		if (el.first > highFreq) highFreq = el.first;
	}
	std::string spacer;
	for (int i = 0; i < HISTOGRAM_SPACING_SIZE; i++) spacer += ' ';

	// make the spacer for the dots
	std::string longestSpacer;
	for (int i = 0; i < longestWord; i++) longestSpacer += ' ';

	// print dots
	for (int i = highFreq; i >= 0; i--) {
		std::cout << longestSpacer;
		for (auto it = d.freqWord.begin(); it != d.freqWord.end(); it++) {
			if (it->first > i) std::cout << '*';
			else std::cout << ' ';
			std::cout << spacer;
		}
		std::cout << '\n';
	}

	// print bar consisting of longest word size + the size of all words
	for (int i = 0; i < longestWord; i++) std::cout << '-';
	for (size_t i = 0; i < d.freqWord.size()*(HISTOGRAM_SPACING_SIZE + 1); i++) std::cout << '-';
	std::cout << '\n';

	// print the arrows
	std::cout << longestSpacer;
	for (size_t i = 0; i < d.freqWord.size(); i++) {
		std::cout << '^';
		std::cout << spacer;
	}
	std::cout << '\n';

	// print the words and stuff
	for (auto it = d.freqWord.begin(); it != d.freqWord.end(); it++) {
		// word
		std::cout << it->second;
		// spacing to the longest word
		for (int i = it->second.size(); i < longestWord; i++) std::cout << ' ';
		// bars to the up arrow
		for (size_t i = 0; i < (d.freqWord.size() - std::distance(it, d.freqWord.end())) * (HISTOGRAM_SPACING_SIZE + 1); i++) {
			std::cout << '-';
		}
		// direction switchers
		std::cout << '/';
		std::cout << spacer;
		// vertical lines
		for (int i = 1; i < std::distance(it, d.freqWord.end()); i++) {
			std::cout << '|';
			std::cout << spacer;
		}

		std::cout << '\n';
	}
}

void initDiction(DICTION &d) {
	for (int i = 'a'; i <= 'z'; i++) {
		d.wordFreq[(char)i] = 0;
	}
	std::get<1>(d.stats) = 0;
}

WORD getNextWord(DICTION &d) {
	WORD w;
	char ch;
	bool inWord = false;
	std::cin.get(ch);
	while( !std::cin.eof() ) {
		// "Words with different cases are considered to be different"
		// uncomment the lines if not true
		// ch = (ch >= 65 && ch <= 90) ? ch+32: ch
		updateStats((ch >= 65 && ch <= 90) ? ch+32: ch, d); // updateStats(ch, d);
		if ( isalpha(ch) ) {  // is ch in [A-Z, a-z]
			updateLetterFreq((ch >= 65 && ch <= 90) ? ch+32: ch, d); // updateLetterFreq(ch, d);
			w.push_back(ch);
			inWord = true;
		} else if (inWord) {
			return w;
		}
		std::cin.get(ch);
	}
	return w;
}
