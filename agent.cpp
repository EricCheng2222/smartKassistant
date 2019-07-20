




#ifndef agent_c
#define agent_c

#include "dictionary.hpp"
#include "agent.hpp"
#include <string>
#include <ctype.h>
#include <string.h>
using namespace std;

void agent::getInput(){
    printf(">");
    getline(cin, input);
    tokenize();
}


void agent::action(){
    float confidence;
    if(strcmp("QUIT", inputTokens[0].c_str())==0){
        printf("saving files...");
        dict.save();
        return;
    }
    else if(strcmp("LOAD", inputTokens[0].c_str())==0){
        printf("loading files...");
        dict.load();
    }
    else{
        dict.feedInput(inputTokens);
        while (true) {
            confidence = dict.firstResponseConf();
            if(confidence>=0.9){
                //reply
                dict.printFirstToken();
                dict.popFirstItem();
            }
            else if(confidence>=0.5){
                //ask if response correct, yes-->respond, no-->learn
                char ans;
                dict.printFirstToken();
                ans = getchar();    getchar();//get rid off input
                tolower(ans);
                
                if(ans == 'y'){
                    dict.printFirstToken();
                    dict.popFirstItem();
                }
                else if(ans == 'n'){
                    printf("please give me suggested reply:");
                    getline(cin, suggestedReply);
                    parse();
                    dict.feedOutput(inputTokens, outputTokens);
                }
            }
            else{
                //learn
                printf("please give me suggested reply:");
                getline(cin, suggestedReply);
                parse();
                dict.feedOutput(inputTokens, outputTokens);
            }
        }
    }
}


void agent::tokenize(){
    inputTokens.clear();
    inputTokens.push_back(string());
    unsigned long lastToken = inputTokens.size()-1;
    for (unsigned long i=0; i<input.size(); i++) {
        if(input[i]==' '){
            inputTokens.push_back(string());
            lastToken = inputTokens.size()-1;
        }
        inputTokens[lastToken].push_back(input[i]);
    }
    ;
}

void agent::parse(){
    outputTokens.clear();
    outputTokens.push_back(string());
    unsigned long lastToken = outputTokens.size()-1;
    for (unsigned long i=0; i<suggestedReply.size(); i++) {
        if(suggestedReply[i]==' '){
            outputTokens.push_back(string());
            lastToken = outputTokens.size()-1;
        }
        outputTokens[lastToken].push_back(suggestedReply[i]);
    }
}


#endif /* TDNet_h */
