








#ifndef dict_h
#define dict_h


#include <string>
#include <vector>
using namespace std;

struct confAndPointerReply;
struct confAndPointerNext;

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

struct confAndPointerNext{
	dictionaryItem* next;
	float confidence;
};

struct confAndPointerReply{
	dictionaryItem* reply;
	float confidence;
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


private:
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