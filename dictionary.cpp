


#ifndef dict_c
#define dict_c


#include "dictionary.hpp"
#include <string.h>
#include <stdio.h>


void dictionary::save(){
    FILE *fptr = fopen("/Users/eric/Desktop/kassistant/longTermMem.txt", "w");
    fprintf(fptr, "%lld\n", vocab.size());
	for(unsigned long i=0; i<vocab.size(); i++){
		vocab[i].print(fptr);
	}
    fclose(fptr);
}


void dictionary::load(){
    ;
}


void dictionary::printFirstToken(){
	printf("%s ", outVocab[maxIte].word.c_str());
}


void dictionary::popFirstItem(){
    bool found = false;
    for (unsigned int i=0; i<outVocab[maxIte].nextVect.size(); i++) {
        found = false;
        for (unsigned int j=0; j<outVocab.size(); j++) {
            if(strcmp(outVocab[maxIte].nextVect[i].next->word.c_str(), outVocab[j].word.c_str())==0){
                found = true;
                outVocab[j].pointedConfidence += outVocab[maxIte].pointedConfidence;
                break;
            }
        }
        if(!found){
            printToEmpty = true;
            outVocab.push_back(*outVocab[maxIte].nextVect[i].next);
            outVocab.back().pointedConfidence += outVocab[maxIte].nextVect[i].confidence;
        }
    }
	outVocab.erase(outVocab.begin() + maxIte);
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
    return maxConf;
}



void dictionary::feedInput(vector<string> &input){
    outVocab.clear();
	for(unsigned long i=0; i<input.size()-1; i++){
		int isExistInput = isExist(input[i]);
		if(isExistInput==-1)
			addWord(input[i]);
		learnNextWord(input[i], input[i+1]);
        visitWordToReply(input[i]);//visit input[i] to determine reply word
	}
    if(input.size()==1){
        int isExistInput = isExist(input[0]);
        if(isExistInput==-1)
            addWord(input[0]);
        visitWordToReply(input[0]);//visit input[i] to determine reply word
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
        for (unsigned long j=0; j<vectOut.size(); j++) {
            out = isExist(vectOut[j]);
            addReplyPointer(in, out);
        }
    }
    
    //add next pointer
    int dst, src;
    for (unsigned int i=0; i<vectOut.size()-1; i++) {
        dst = isExist(vectOut[i]);
        src = isExist(vectOut[i+1]);
        addNextPointer(dst, src);
    }
    
}



int dictionary::isExist(string s){
	for(unsigned long i=0; i<vocab.size(); i++){
		if(strcmp(vocab[i].word.c_str(), s.c_str())==0)
			return i;
	}
	return -1;
}


void dictionary::addWord(string s){
    vocab.push_back(dictionaryItem(globalID++));
	unsigned long ite = vocab.size() - 1;
	vocab[ite].word = s;
}


void dictionary::learnNextWord(string before, string after){
	int sIndex = isExist(before);
	int nextIndex = isExist(after);
	addNextPointer(sIndex, nextIndex);
}

void dictionary::addNextPointer(int src, int dst){
    // if such pointer exist
	for (unsigned long i=0; i<vocab[src].nextVect.size(); i++){
		if(vocab[src].nextVect[i].next == &vocab[dst]){
			if(vocab[src].nextVect[i].confidence<=1.0)
				vocab[src].nextVect[i].confidence += 0.01;
			return;
		}
	}
    
    
    //if such pointer not exist
    vocab[src].nextVect.push_back(confAndPointerNext(&vocab[dst]));
    if(vocab[src].nextVect[vocab[src].nextVect.size()-1].confidence<=1.0)
        vocab[src].nextVect[vocab[src].nextVect.size()-1].confidence += 0.01;
}


void dictionary::addReplyPointer(int src, int dst){
    // if such pointer exist
    for (unsigned long i=0; i<vocab[src].replyVect.size(); i++){
        if(vocab[src].replyVect[i].reply == &vocab[dst]){
            if(vocab[src].replyVect[i].confidence<=1.0)
                vocab[src].replyVect[i].confidence += 0.01;
            return;
        }
    }
    
    
    //if such pointer not exist
    vocab[src].replyVect.push_back(confAndPointerReply(&vocab[dst]));
    if(vocab[src].replyVect[vocab[src].replyVect.size()-1].confidence<=1.0)
        vocab[src].replyVect[vocab[src].replyVect.size()-1].confidence += 0.01;

}


void dictionary::visitWordToReply(string s){//heat map for reply
    vector<dictionaryItem> tmpOutVocab;
    tmpOutVocab.clear();
    int index = isExist(s);
    bool found = false;
    for (unsigned int i=0; i<vocab[index].replyVect.size(); i++) {
        tmpOutVocab.push_back(*vocab[index].replyVect[i].reply);
        tmpOutVocab.back().pointedConfidence += vocab[index].replyVect[i].confidence;
    }
    
    
    for (unsigned int i=0; i<tmpOutVocab.size(); i++) {
        found = false;
        for (unsigned int j=0; j<outVocab.size(); j++) {
            if(strcmp(tmpOutVocab[i].word.c_str(), outVocab[j].word.c_str())==0){
                outVocab[j].pointedConfidence += tmpOutVocab[i].pointedConfidence;
                found = true;
                break;
            }
        }
        if(!found){
            printToEmpty = true;
            outVocab.push_back(tmpOutVocab[i]);
            outVocab.back().pointedConfidence += tmpOutVocab[i].pointedConfidence;
        }
    }
}
#endif /* TDNet_h */
