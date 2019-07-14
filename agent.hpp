




#include "dictionary.cpp"
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
    vector<string> tokens;
    
    
    void tokenize();//for input
    void parse();   //for suggestedReply
    
};







