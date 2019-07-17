



#include <cstdio>
#include "agent.hpp"
using namespace std;

int main(){
	agent kev;
	while(true){
		kev.getInput();
		kev.action();
	}
}
