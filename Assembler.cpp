#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
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
	if(line[0] == '\n'){
		return true;
	}
	return false;
}

typedef struct expression{
	string label;
	string operand;
	string operation;
}expr;

typedef struct assignExpression{
	string reg;
	string sym;
}assign;

bool isExpression(string line){
	istringstream __ss(line);
	string word;
	int count = 0;
	while(__ss >> word)
		count++;

	if(count > 1)
		return true;
	return false;
}

expr getExpression(string line){
	istringstream __iss(line);
	expr __e;
	__iss >> __e.label >> __e.operand >> __e.operation;
	return __e;
}

bool isEnd(string line){
	if(line.compare("END") == 0){
		return true;
	}
	return false;
}

int getOperationType(string str){
	for(int i = 0; i < str.length(); i++){
		if(str[i] == ',')
			return 1;
		if(str[i] == '\'')
			return 2;
	}

	if(isdigit(str[0])){
		if(str.length() > 1 && isdigit(str[1])){
			return 3;
		}
		else{
			return 2;
		}
	}
	return 99;
}

typedef struct Storage{
	bool isConstant;
	bool isStorage;
	string sym;
	string type;
	string value;
}store;

store getStorage(string sym, string type, string str){
	store __store;

	if(type.compare("DC") == 0){
		__store.isConstant = true;	
		__store.isStorage = false;
	}
	else if(type.compare("DS") == 0){
		__store.isStorage = true;
		__store.isConstant = false;
	}
	else{
		__store.isConstant = false;
		__store.isStorage = false;
	}

	__store.sym = sym;
	__store.type = str[0];
	int i;
	if(__store.isConstant){
		i = 1;
		while(str[i+1] != '\'')
			i++;
		__store.value = str.substr(2, i-1);
	}
	else if(__store.isStorage){
		__store.value = str;
	}
	

	return __store;
}

assign getOperation(string str){
	assign __op;

	__op.reg = str[0];
	int len = str.length();
	for(int i = 1; i < len; i++){
		if(str[i] == ','){
			__op.sym = str.substr(i+1, len - i - 1);
			break;
		}
	}

	return __op;
}

void runAssembler(){

	int scnt = 0, locctr = 0, endval = 0, errorFlag = 0;
	bool  flag = false;

	for(int i = 0; i < fileSize(); i++){

		flag = false;
		scnt = i;

		if(emptyLine(sourceLine[scnt])){
			continue;
		}

		if(isEnd(sourceLine[scnt])){
			cout << "Program ended" << endl;
			break;
		}

		//Comments handler
		if(comment(sourceLine[scnt]) && scnt < fileSize()){
			cout << "Comment : " << sourceLine[scnt] << endl;
			scnt++;
			flag = true;
		}

		if(flag){
			i = scnt-1;
			continue;
		}

		if(isExpression(sourceLine[scnt]) && scnt < fileSize()){
			expr e = getExpression(sourceLine[scnt]);
			cout << e.label << "|" << e.operand << "|" << e.operation << endl;

			if(e.label.compare("-") == 0){
				cout << "No label defined! " << endl;
			}
			assign op;
			store s;

			switch(getOperationType(e.operation)){
				case 1 :
					op = getOperation(e.operation);
					cout << op.reg << "|" << op.sym << endl;
					break;
				case 2 :
					cout << "Second type" << endl;
					s = getStorage(e.label, e.operand, e.operation);
					cout << s.isConstant << "|" << s.isStorage << "|" << s.sym << "|" << s.type << "|" << s.value << endl;
					break;
				case 3 :
					cout << "Numeric : " << e.operation << endl;
					break;
				default : cout << "Invalid operation!" << endl;
			}

			scnt++;
			flag = true;
		}
		if(flag){
			i = scnt-1;
			continue;
		}
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