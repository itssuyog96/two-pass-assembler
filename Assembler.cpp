#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "srcfile.h"

void initialize(int, char*);
bool comment(string);
bool emptyLine(string);
void runAssembler(void);

void initialize(int argc, char *argv[]){
	makeglobal(argc, argv);
}

bool comment(string line){

	if(!emptyLine(line)){
		for(int i = 0; i < line.length(); i++){
			switch(line[i]){
				case ' ':
				case '\t':
					break;
				case '/':
					if(line[i+1] == '/')
						return true;
				default :
					return false;
			}
		}
	}

	return false;
}

bool emptyLine(string line){
	if(line[0] == '\n')
		return true;
	return false;
}

void runAssembler(){

	int scnt = -1, locctr = 0, endval = 0, errorFlag = 0;

	for(int i = 0; i < fileSize(); i++){

		//Comments handler
		while(comment(sourceLine[++scnt]) && scnt < fileSize()){
			cout << "Comment : " << sourceLine[scnt] << endl;
		}

		i = scnt;	
	}
	


}

int main(int argc, char *argv[])
{    
	initialize(argc, argv);

	if(getSourceFile()){
    	
    	runAssembler();
    }

    return 0;
	
}