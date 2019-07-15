





#include "dictionary.hpp"

void dictionary::save();


void dictionary::load();


void dictionary::printFirstToken(){
	printf("%s ", outVocab[maxIte].word);
}


void dictionary::popFirstItem(){
	outVocab.erase(outVocab.begin() + matIte);
}


float dictionary::firstResponseConf(){
	float maxConf = -1.0;
	maxIte = -1;
	for (unsigned long i=0; i<outVocab.size(); i++){
		if(maxConf < outVocab[i].pointedConfidence){
			maxConf = outVocab[i].pointedConfidence;
			maxIte = i;
		}
	}
	
}



void dictionary::feedInput(vector<string> &input){
	for(unsigned long i=0; i=input.size(); i++){
		int isExistInput = isExist(input[i]);
		if(isExistInput==-1)
			addWord(input[i]);
		visitWord(input[i], input);//this function is for learning the next word
	}
}


void dictionary::feedOutput(vector<string>);



int dictionary::isExist(string s){
	for(unsigned long i=0; i<vocab.size(); i++){
		if(strcmp(vocab[i].word.c_str, s.c_str)==0)
			return i;
	}
	return -1;
}


void dictionary::addWord(string s){
	vocab.push_back(dictionaryItem());
	unsigned long ite = vocab.size() - 1;
	vocab[ite].word = s;
}


void dictionary::visitWord(string s, vector<string> &vect, int index){
	/*NOT DONE!!!!!!*/
	int sIndex = isExist(s);
	int nextIndex;
	for(unsigned long i=index; i<vect.size(); i++){
		nextIndex = isExist(vect[i]);
		if(nextIndex==-1){
			addWord(vect[i]);
			nextIndex = isExist(vect[i]);
		}
		addNextPointer(sIndex, nextIndex);
	}
}

void dictionary::addNextPointer(int src, int dst){
	for (unsigned long i=0; i<vocab[src].nextVect.size(); i++){
		if(vocab[src].nextVect[i] == &vocab[dst]){
			if(vocab[src].nextVect[i].confidence<=1.0)
				vocab[src].nextVect[i].confidence += 0.01;
			return;
		}
	}
}