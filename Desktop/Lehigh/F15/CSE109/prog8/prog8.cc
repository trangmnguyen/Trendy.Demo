/*
CSE 109
Sami Nguyen
tmn218
Program transform one word to another using word pairs put in by classmates in classwords.txt
Output INVALID word1 word2 if no transformation can be done to change from word1 to word2
Program #8
*/
#include "solver.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

	//store words file into a vector
	vector<string> words;
	string lineInWords;
	ifstream wordList ("words");
	if(wordList){
		while (getline(wordList, lineInWords)){
			words.insert(words.end(), lineInWords);
		}
	}
	string lineInClasswords;
	ifstream classwords ("classwords.txt");
	if (classwords){
		bool empty = true;
		string firstWord, lastWord;
		while (getline(classwords, lineInClasswords)){ 
			if (lineInClasswords.length() == 6) {continue;}
			for (int i=7; i< lineInClasswords.length(); i++){
				if (lineInClasswords[i] == ' '){
					empty = false;
					firstWord = lineInClasswords.substr(7, i-7);
					lastWord = lineInClasswords.substr(i+1, i-7);
					break;
				}
			}
			if (!(empty)) {
				Solver solver (firstWord,lastWord, words);
				cout << solver.output() << endl;
			}
		}
	}
}


