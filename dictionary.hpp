








#ifndef dict_h
#define dict_h


#include <string>
#include <vector>
using namespace std;

struct confAndPointerReply;
struct confAndPointerNext;
struct dictionaryItem;


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