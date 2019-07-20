


#ifndef agent_h
#define agent_h


#include "dictionary.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


class agent{
public:
    void getInput();
    void action();
    
    
    
private:
    string input, suggestedReply;
    vector<string> inputTokens, outputTokens;
    dictionary dict;
    
    void tokenize();//for input
    void parse();   //for suggestedReply
    
};

#endif /* TDNet_h */





