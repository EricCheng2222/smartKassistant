


#ifndef dict_c
#define dict_c


#include "dictionary.hpp"

struct confAndPointerNext{
    dictionaryItem* next;
    float confidence;
};

struct confAndPointerReply{
    dictionaryItem* reply;
    float confidence;
};

struct dictionaryItem{
    int ID;
    string word;
    vector<confAndPointerNext> nextVect;
    vector<confAndPointerReply> replyVect;
    float pointedConfidence = 0.0;


    void print(){
        printf("%d ", ID);
        printf("%s ", word.c_str);
        //printf("NEXT:");
        printf("%d ", nextVect.size());
        for(unsigned long i=0; i<nextVect.size(); i++)  
            printf("%d ", nextVect[i].next->ID);
        

        //printf("REPLY:");
        printf("%d ", replyVect.size());
        for(unsigned long i=0; i<replyVect.size(); i++) 
            printf("%d ", replyVect[i].reply->ID);
    }

};




void dictionary::save(){
	for(unsigned long i=0; i<vocab.size(); i++){
		vocab[i].print();
	}
}


void dictionary::load(){
    ;
}


void dictionary::printFirstToken(){
	printf("%s ", outVocab[maxIte].word);
}


void dictionary::popFirstItem(){
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
}



void dictionary::feedInput(vector<string> &input){
	for(unsigned long i=0; i=input.size()-1; i++){
		int isExistInput = isExist(input[i]);
		if(isExistInput==-1)
			addWord(input[i]);
		learnNextWord(input[i], input[i+1]);
        visitWordToReply(input[i]);//visit input[i] to determine reply word
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
        for (unsigned int j=i+1; j<vectOut.size(); j++) {
            dst = isExist(vectOut[i]);
            src = isExist(vectOut[j]);
            addNextPointer(dst, src);
        }
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


void dictionary::learnNextWord(string before, string after){
	int sIndex = isExist(before);
	int nextIndex = isExist(after);
	addNextPointer(sIndex, nextIndex);
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
    vocab[src].push_back(struct confAndPointerNext*(&vocab[dst]));
    if(vocab[src].nextVect[vocab[src].nextVect.size()-1].confidence<=1.0)
        vocab[src].nextVect[vocab[src].nextVect.size()-1].confidence += 0.01;
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
    vocab[src].push_back(struct confAndPointerReply*(&vocab[dst]));
    if(vocab[src].replyVect[vocab[src].replyVect.size()-1].confidence<=1.0)
        vocab[src].replyVect[vocab[src].replyVect.size()-1].confidence += 0.01;

}


void dictionary::visitWordToReply(string s){//heat map for reply
    int index = isExist(s);
    bool found = false;
    for (unsigned int i=0; i<vocab[index].replyVect.size(); i++) {
        for(unsigned int j=0; j<outVocab.size(); j++){
            found = false;
            if(strcmp(outVocab[j].word.c_str(), vocab[index].replyVect[i].reply->word.c_str())){
                outVocab[j].pointedConfidence += 0.01;
                found = true;
                break;
            }
        }
        if(found == false){
            outVocab.push_back(vocab[index].replyVect[i]);
            outVocab[outVocab.end()].pointedConfidence += 0.01;
        }
    }
}
#endif /* TDNet_h */