





#include "dictionary.hpp"

void dictionary::save(){
	for(unsigned long i=0; i<vocab.size(); i++){
		vocab[i].print();
	}
}


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


void dictionary::feedOutput(vector<string> &vectIn, vector<string> &vectOut){
    int in, out;
    
    //add none-existing words
    for(unsigned int i=0; i<vectIn.size(); i++){
        in =  isExist(vectIn[i]);
        if(in==-1)
            addWord(vectIn[i]);
    }
    for(unsigned int i=0; i<vectOut.size(); i++){
        out =  isExist(vectOut[i]);
        if(out==-1)
            addWord(vectOut[i]);
    }
    
    //add reply pointer
    for (unsigned long i=0; i<vectIn.size(); i++) {
        in =  isExist(vectIn[i]);
        for (unsigned long j=0; j<vectOut; j++) {
            out = isExist(vectOut[j]);
            addReplyPointer(in, out);
        }
    }
    
    //add next pointer
    for (unsigned int i=0; i<vectOut.size(); i++) {
        
    }
}



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
    // if such pointer exist
	for (unsigned long i=0; i<vocab[src].nextVect.size(); i++){
		if(vocab[src].nextVect[i] == &vocab[dst]){
			if(vocab[src].nextVect[i].confidence<=1.0)
				vocab[src].nextVect[i].confidence += 0.01;
			return;
		}
	}
    
    
    //if such pointer not exist
}


void dictionary::addReplyPointer(int src, int dst){
    // if such pointer exist
    for (unsigned long i=0; i<vocab[src].replyVect.size(); i++){
        if(vocab[src].replyVect[i] == &vocab[dst]){
            if(vocab[src].replyVect[i].confidence<=1.0)
                vocab[src].replyVect[i].confidence += 0.01;
            return;
        }
    }
    
    
    //if such pointer not exist
}
