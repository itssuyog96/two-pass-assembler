#ifndef _SRC_FILE
#define _SRC_FILE

string sourceLine[100];

typedef struct __FILE{
    string name;
    char line[80];
    int cnt;
    int argcnt;
}ABC;

ABC INFILE; 

int __global_argc;
char **__global_argv = NULL;

void makeglobal(int argc, char *argv[]){
    __global_argc = argc;
    __global_argv = argv;

    INFILE.argcnt = argc;
}

bool getSourceFile(){
	if (INFILE.argcnt < 2){
    	cerr << "No input file!" << endl;
    	cerr << "Usage : sasm <filename>" << endl;
    	return false;
    }

    INFILE.name = __global_argv[1];

    ifstream file(INFILE.name);

    if(!file){
    	cerr << "Unable to open file " << INFILE.name << endl;
    	return false;
    }

    while(file.getline(INFILE.line, 80)){
    	sourceLine[INFILE.cnt++] = INFILE.line;
    }

    if(!file.eof()){
    	cerr << "Error reading the file!" << endl;
    	return false;
    }
    return true;
}

inline int fileSize(){
    return INFILE.cnt;
}

#endif