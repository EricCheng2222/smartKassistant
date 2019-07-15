










#include <string>
#include <vector>
using namespace std;

struct confAndPointerReply;
struct confAndPointerNext;

struct dictionaryItem{
	string word;
	vector<confAndPointerNext> nextVect;
	vector<confAndPointerReply>replyVect;
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
	void feedInput(vector<string>);
	void feedOutput(vector<string>)


private:
};