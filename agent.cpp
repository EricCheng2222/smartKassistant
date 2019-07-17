




#ifndef agent_c
#define agent_c

#include "dictionary.hpp"
#include "agent.hpp"
#include <string>
#include <ctype.h>
#include <string.h>
using namespace std;

void agent::getInput(){
    getline(cin, input);
    tokenize();
}


void agent::action(){
    float confidence;
    if(strcmp("QUIT", tokens[0].c_str())==0){
        printf("saving files...");
        dict.save();
        return;
    }
    else if(strcmp("LOAD", tokens[0].c_str())==0){
        printf("loading files...");
        dict.load();
    }
    else{
        dict.feedInput(tokens);
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
                    dict.feedOutput(suggestedReply);
                }
            }
            else{
                //learn
                printf("please give me suggested reply:");
                getline(cin, suggestedReply);
                parse();
                dict.feedOutput(suggestedReply);
            }
        }
    }
}


void agent::tokenize(){
    tokens.clear();
    tokens.push_back(string());
    unsigned long lastToken = tokens.size()-1;
    for (unsigned long i=0; i<input.size(); i++) {
        if(input[i]==' '){
            tokens.push_back(string());
            lastToken = tokens.size()-1;
        }
        tokens[lastToken].push_back(input[i]);
    }
}


#endif /* TDNet_h */