








#ifndef dict_h
#define dict_h


#include <string>
#include <vector>
using namespace std;



struct dictionaryItem;
struct confAndPointerNext{
    confAndPointerNext(){;}
    confAndPointerNext(struct dictionaryItem* item){
        next = item;
    }
    struct dictionaryItem* next;
    float confidence = 0.0;
};


struct confAndPointerReply{
    confAndPointerReply(){;}
    confAndPointerReply(struct dictionaryItem *item){
        reply = item;
    }
    struct dictionaryItem* reply;
    float confidence = 0.0;
};
struct dictionaryItem{
    dictionaryItem(int gID){
        ID = gID;
    }
    int ID;
    string word;
    vector<confAndPointerNext>  nextVect;
    vector<confAndPointerReply> replyVect;
    float pointedConfidence = 0.0;
    
    
    void print(FILE *fp){
        fprintf(fp, "%d ", ID);
        fprintf(fp, "%s ", word.c_str());
        //printf("NEXT:");
        fprintf(fp, "%d ", nextVect.size());
        for(unsigned long i=0; i<nextVect.size(); i++){
            fprintf(fp, "%d ", nextVect[i].next->ID);
            fprintf(fp, "%f ", nextVect[i].confidence);
        }
        
        
        
        //printf("REPLY:");
        fprintf(fp, "%d ", replyVect.size());
        for(unsigned long i=0; i<replyVect.size(); i++){
            fprintf(fp, "%d ", replyVect[i].reply->ID);
            fprintf(fp, "%f ", replyVect[i].confidence);
        }
        fprintf(fp, "\n");
    }
    
};



class dictionary{

public:
	void save();
	void load();
	void printFirstToken();
	void popFirstItem();
	float firstResponseConf();
	void feedInput(vector<string> &input);
	void feedOutput(vector<string> &input, vector<string> &suggestedOutput);
    bool printToEmpty = false;


private:
    int globalID = 0;
	int maxIte;
	vector<dictionaryItem> vocab;
	vector<dictionaryItem> outVocab;
	int isExist(string s);
	void learnNextWord(string before, string next);
	void addWord(string s);
	void visitWord(string s, vector<string> &vect, int index);
	void addNextPointer(int src, int dst);
    void addReplyPointer(int src, int dst);
    void visitWordToReply(string s);
};

#endif /* TDNet_h */
