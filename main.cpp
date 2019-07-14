



#include <cstdio>
#include "agent.cpp"
using namespace std;

int main(){
	agent kev;
	while(true){
		kev.getInput();
		kev.action();
	}
}
