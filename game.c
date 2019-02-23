#include "functions.h"

//Main function.
int main(int argc, char ** argv){
	char ** world;
	int row;
	int col;
	
	if(argc == 3){
		row = atoi(argv[1]);//Grab row
		col = atoi(argv[2]);//Grab col
		doit(world,row,col);//Start game.
	}

	return 0;
}

