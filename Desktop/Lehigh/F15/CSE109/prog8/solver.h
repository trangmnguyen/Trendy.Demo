#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>

using namespace std;

class Solver {
private:
	string result;
	string firstWord;
	string lastWord;
	vector<string> words;
	int length;
	map< string, vector<string> > graphOfWordsWithSameLength;
public:
	Solver(string& first, string& last, vector<string>& wordlist);
	~Solver();
	string output();
	bool isAWord(string& w);
	
	class Node{
		public:
			Node(string val, Node *n){
				value = val;
				parent = n;
				visited = false;
			}
			Node(string val){
				value = val;
			}
			bool visited;
			string value;
			Node *parent;
	};
	void construct();
};
#endif