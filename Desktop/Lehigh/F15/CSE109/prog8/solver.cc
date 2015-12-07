#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <iterator>
#include "solver.h"

using namespace std;

Solver::Solver(string& first, string& last, vector<string>& wordlist){
	firstWord = first;
	lastWord=last;
	words = wordlist;
	result = "";
	length = first.length();
	construct();
}

Solver::~Solver(){
}

bool Solver::isAWord(string& w){
	return (binary_search(words.begin(), words.end(), w));
}

void Solver::construct(){
	string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (vector<string>::iterator it = words.begin(); it != words.end(); ++it){
		string word = *it;
		if (word.length() == length){
			vector<string> linkedWords;
			string test = "";
			//loop through the word 
			for (int i = 0; i<length; ++i){
				for (int j = 0; j< letters.length(); ++j){
					if (word[i] != letters[j]){
						string test = word;
						test[i] = letters[j];
                        if (isAWord(test)){
                        	//add test to end of vector
                        	linkedWords.push_back(test);
						}
					}
				}	
            }
            graphOfWordsWithSameLength[word] = linkedWords;
		}
	}
}

string Solver::output(){
	bool found =false;
	if (firstWord.length() != lastWord.length() || !(isAWord(firstWord)) || !(isAWord(lastWord))  ){
		result += "INVALID " + firstWord + " " + lastWord +" - at least one entry not in words\n";
	} else {
		//compare each character of the w words
		for (int i = 0; i<firstWord.length(); i++){
			if (firstWord.at(i) == lastWord.at(i)){
				result += "INVALID " + firstWord + " " + lastWord +" - pair has same a common letter-position \n";
				return result;
			}
		}
		//solve for the chain using breadth first search
		queue<Node*> q; //the queue of bfs
		Node* root = new Node (firstWord, NULL);
		Node* current = root;
		//enqueue root
		q.push(root);
		vector<string> visitedString; //store the string of visited nodes
		while (!q.empty() && !found){
			//dequeue current
			current = q.front();
			q.pop();
			//create adjacent nodes
			vector <string> children = graphOfWordsWithSameLength.find(current->value)->second;
			vector <Node*> testChildren;
			for (vector<string>::iterator it = children.begin(); it != children.end(); ++it){
				Node* newChild = new Node(*it, current);
				testChildren.push_back(newChild);
			}
			//test the new children and enqueue the unvisited children into q
			for (vector<Node*>::iterator it = testChildren.begin(); it != testChildren.end(); ++it){
				Node* testingChild = *it;
				string testVal = testingChild->value;
				//test if lastWord is found
				if(testVal == lastWord) {
					found = true;
				}

				if(find(visitedString.begin(), visitedString.end(), testVal) != visitedString.end()) {
					// found
				} else {
					// not found
					visitedString.push_back(testVal);
					q.push(testingChild);
				}
			}
		}
		if (!found) {
			result += "INVALID " + firstWord + " " + lastWord +"\n";
		} else {
			result = firstWord + " ";
			stack<string> solvedChain;
			while(current!= nullptr) {
				solvedChain.push(current->value);
				current = current->parent;
			}
			while (!solvedChain.empty()){
				result+= solvedChain.top() +" ";
     			solvedChain.pop();
			}
			result += "\n";
		}

	 }
	return result;
}

