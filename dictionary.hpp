










#include <string>
#include <vector>
using namespace std;

struct confAndPointerReply;
struct confAndPointerNext;

struct dictionaryItem{
	int ID;
	string word;
	vector<confAndPointerNext> nextVect;
	vector<confAndPointerReply>replyVect;
	float pointedConfidence = 0.0;

	void print(){
		printf("<%d>", ID);
		printf("<%s>", word.c_str);
		printf("NEXT:");
		for(unsigned long i=0; i<nextVect.size(); i++)	
			printf("%d ", nextVect[i].ID);
		
		printf("REPLY:");
		for(unsigned long i=0; i<replyVect.size(); i++)	
			printf("%d ", replyVect[i].ID);
	}

};

struct confAndPointerNext{
	dictionaryItem* next;
	float confidence;
}

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
	void feedOutput(vector<string> &suggestedOutput);


private:
	int maxIte;
	vector<dictionaryItem> vocab;
	vector<dictionaryItem> outVocab;
	bool isExist(string s);
	void addWord(string s);
	void visitWord(string s, vector<string> &vect, int index);
	void addNextPointer(int src, int dst);
};