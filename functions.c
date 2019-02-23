#include "functions.h"

//Read one line from a file
int read_file(char*filename, char ** buffer, int pos){
	FILE * file = fopen(filename, "r");
	fseek(file,pos,SEEK_SET);
	fgets(*buffer,1024,file);	
	int new_pos = ftell(file);
	fclose(file);

	return new_pos;
}

//Write one line to a file
int write_file(char * filename, char * buffer, int size){
	FILE * file = fopen(filename, "a");
	fprintf(file,"%s\n",buffer);//print a line to the file.
	fclose(file);

	return 0;
}

//Load
int load(char *** world, char * filename, int * row2, int * col2){
	//Temporary buffer and position.
	char * buffer = (char*) malloc(sizeof(char));	
	int pos;

	
	//Read in row #.
	pos = read_file(filename,&buffer,0);
	int row = atoi(buffer);
	*row2 = row;	

	//Read in the column #.
	pos = read_file(filename,&buffer,pos);
	int col = atoi(buffer);
	*col2 = col; 
	
	//Allocate mem for array.
	mem_alloc(world,row,col);

	//Read in universe
	for(int r = 0; r < row; r++)
		pos = read_file(filename,&(*world)[r],pos);

	//free memory
	free(buffer);

	return 0;
}

//Save
int save(char ** world, char * filename, int row, int col){
	//Clear file
	FILE * file = fopen(filename, "w");
	fclose(file);
	
	//temp buffer
	char * buffer = (char*) malloc(sizeof(char)*2); 

	//Write row number.	
	toString(row,buffer);
	write_file(filename,buffer,0);

	//Write col number.
	toString(col,buffer);
	write_file(filename,buffer,0);

	//Write universe to the file.
	for(int idx = 0; idx < row; idx++){
		write_file(filename,world[idx],0);
	}

	//Free memory
	free(buffer);

	return 0;
}

//Convert a int to a string
//Got the idea for this on stack overflow
void toString(int num, char * str){
	sprintf(str,"%d",num);
}

//Allocate mem
void mem_alloc(char *** world, int row, int col){

	//ALLOCATE MEMORY FOR ROWS.
        *world = (char**) malloc(sizeof(char*) * row);
 
        //ALLOCATE MEMORY FOR COLUMNS.
        for(int r = 0; r < row; r++)
        	(*world)[r] = (char*)malloc(sizeof(char) * col);	      
}

//Populate board with cells TODO let user pick % of board that is cells
void populate(char ** world, int row, int col, int amt){

	//Seed random number generator
	time_t t;
	srand((unsigned)time(&t));	//GOT FROM STACK OVERFLOW
	
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			int seed = rand() % 100; //random number 1 thru 100.
			
			if(seed > 40)
				world[r][c] = '@';//populate with cell.
			else
				world[r][c] = 'O';//populate with dead cell.	
		}	
}

//TODO Calculates count number of generations
int generation(char *** world, int row, int col, int count){

	int death_toll = 0;
	int revives = 0;
	int live = 0;
	int gen_num = 0;
	
	/*READ IN OVERPOPULATED CELLS*/
	while(gen_num < count){
		update(*world,row,col);
		print(*world,row,col);
		gen_num++;
	}

//	printf("\nDEATH TOLL: %d\n", death_toll - revives);
//	printf("\nREVIVED CELLS: %d\n", revives);
//	printf("\nLIVING CELLS: %d\n", live);

	return 0;
}

//TEST Count nbhs surrounding each cell
int update(char ** world,int row, int col){
	int tcc = 0;//Total cell count of the given state.
	char ** nbh_count;//The number of naighbors around each cell.
	mem_alloc(&nbh_count,row,col);//allocate mem for nbh_count	

	for(int r = 0; r < row; r++)
		for(int c = 0; c < col;c++){
			//////////////////////////
			//COUNT NBHS AROUND CELL//
			//////////////////////////
				/////////
				//1 2 3//
				//8 @ 4//
				//7 6 5//
				/////////
			
				int count = 0;
				if(r-1 >= 0)//////////////////////cell 1
					if(world[r-1][c] == '@')
						count++;		
				if(r-1 >= 0 && c+1 <= col-1)////////cell 2
					if(world[r-1][c+1] == '@')
						count++;
				if(c+1 <= col-1)////////////////////cell 3
					if(world[r][c-1] == '@')
						count++;
				if(r+1 <= row-1 && c+1 <= col-1)//////cell 4
					if(world[r+1][c+1] == '@')
						count++;
				if(r+1 <= row-1)////////////////////cell 5
					if(world[r+1][c] == '@')
						count++;
				if(r+1 <= row-1 && c-1 >= 0)////////cell 6
					if(world[r+1][c-1] == '@')
						count++;
				if(c-1 >= 0)//////////////////////cell 7
					if(world[r][c-1] == '@')
						count++;
				if(r-1 >= 0 && c-1 >= 0)//////////cell 8
					if(world[r-1][c-1] == '@')
						count++;
				//SET THE NUMBER OF NBHS FOR THIS CELL
				nbh_count[r][c] = count;

		}
				//Determine if cell is dead, alive, or revived.
				for(int r = 0; r < row; r++)
					for(int c = 0; c < col; c++){
						if(nbh_count[r][c] < 2){//DEAD
							world[r][c] = 'O';
							tcc++;
						}
						if(nbh_count[r][c] > 3){//DEAD
							world[r][c] = 'O';
							tcc++;
						}
						if(nbh_count[r][c] == 3){//REVIVED
							world[r][c] = '@';
							tcc++;
						}
				}
		
	return tcc; //Return the number of cells in the given state.
}

void get_input(char * input){
	fflush(stdin);
	scanf(" %s", input);
}

void doit(char ** world, int row, int col){
	char * input = malloc(sizeof(char)*4);//Gets user input.
	char prompt[100] = "~MENU~\n\t1~New Game\n\t2~Load Game\n\t3~Generation\n\t4~Save Game\n\t0-Quit\n";//Prompt for user.
	int mem_al = 0;//Flag for if the memory is allocated or not.

	//PRINT INTRO
	system("clear");
	puts("~GAME OF LIFE~");
	puts("\t1~New Game\n\t2~Load Game\n\t0~Quit\n");
	get_input(input);
	
	while(atoi(input) != 0){
		switch(atoi(input)){
			case 1 ://USER SELECTS NEW GAME
				if(mem_al == 1){
					free_mem(&world,row);//FREE MEM
					mem_al = 0;
				}		
				mem_alloc(&world,row,col);//ALLOCATE MEM
				mem_al = 1;
				populate(world,row,col,atoi(input));	//Populate board with cells.
				system("clear");
				print(world,row,col);
			break;
			case 2 ://USER SELECTS LOAD GAME
				if(mem_al == 1){
					free_mem(&world,row);
					mem_al = 0;
				}
				puts("ENTER FILE NAME: ");
				get_input(input);
				load(&world,input,&row,&col);
				system("clear");
				print(world,row,col);
			break;
			case 3 ://USER SELECTS GENERATION
				puts("ENTER THE NUMBER OF GENERATIONS: ");
				get_input(input);
				generation(&world,row,col,atoi(input));
				system("clear");
				print(world,row,col);	
			break;
			case 4 ://USER SELECTS SAVE GAME
				puts("ENTER FILE NAME: ");
				get_input(input);
				save(world,input,row,col);
				system("clear");
				printf("GAME SAVED IN FILE : %s", input);
				print(world,row,col);
			break;
			case 0 ://USER QUITS
			break;
			default :
				system("clear");
			 
			break;
		}
		puts(prompt);
		get_input(input);
		//system("clear");
		printf("\nSelected : %c\n", input[0]);
	}
	system("clear");
	//FREE MEMORY
	free(input);
	if(mem_al == 1)
		free_mem(&world,row);		
}
	
//Print world
void print(char ** world, int row, int col){
	for(int r = 0; r < row; r++){
		printf("\n");
		for(int c = 0; c < col; c++)
			putchar(world[r][c]);
		
	}
	printf("\n\n");
}

//Fill board with blank spaces
void clear(char ** world, int row, int col){
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++)
			world[r][c] = ' ';
}

//Clears dead cells from the board
void bring_out_your_dead(char ** world, int row, int col){
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++)
			if(world[r][c] == 'X')
				world[r][c] = 'O';
}

//Free_mem
int free_mem(char *** world, int row){
	//Free each row
	for(int r = 0; r < row; r++)
		free((*world)[r]);
	//Free the original array
	free(*world);
	
	return 0;
}
