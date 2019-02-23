#ifndef FUNCTIONS_H_INCLUDE
#define FUNCTIONS_H_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

/***********************************************************
 *This function will read one line from a file at a 
 *time from a given starting position.
 *
 *@param filename ~ the name of the file.
 *@param buffer ~ buffer that reads one line from the file.
 *@param pos ~ the position the file will be read from.
 *@return the position of the file after reading.
 **********************************************************/
int read_file( char* filename, char **buffer, int pos);

/************************************************************
 *This function will write one line to a file.
 *
 *@param filename ~ the name of the file.
 *@param buffer ~ contains the line that will be written to the file. 
 *@param size ~ the size of the line to be written to the file.
 *@return returns zero if writing went okay.
 ***********************************************************/
int write_file( char* filename, char *buffer, int size);

/*************************************************************
 *Save the world to a text file via the write file function.
 *First write the row then col number, then writes the contents
 *of the world to the file.
 *
 *@param world ~ 2D char array.
 *@param filename ~ name of the file that will be saved to.
 *@param row ~ number of rows in the world.
 *@param col ~ number of columns in the world.
 *@return returns zero if all went well.     
 ************************************************************/
int save(char ** world, char * filename,int row, int col);

/******************************************************
 *Load a game from a file.
 *
 *@param world ~ pointer to 2D char array representing the world.
 *@param filename ~ the name of the file.
 *@param row ~ the row number of the board.
 *@param col ~ the col number of the board.
 *@return returns zero if all went well.
 *****************************************************/
int load(char *** world, char * filename, int * row, int * col);

/**********************************************************
 *Allocate memory for 2D char array. 
 *
 *@param world ~ pointer to a 2D char array
 *@param row ~ the number of rows the array will have
 *@param col ~ the number of columns the array will have.
 *********************************************************/
void mem_alloc(char *** world, int row, int col);
 
/********************************************************
 *Populates the board randomly with cells.
 * 
 *@param world ~ 2D char array.
 *@param row ~ the number of rows in the board.
 *@param col ~ the number of columns in the board.
 *******************************************************/
void populate(char ** world, int row, int col, int amt);

/*************************************************************
 *Updates the board after count number of cell generations.
 *Does this by using the update method.
 *
 *@param world  ~ Pointer to a 2D char array. 
 *@param row  ~ the number of rows in the world.
 *@param col  ~ the number of columns in the world.
 *@param count  ~ the number generations. 
 *@return returns zero if all is well.
 ************************************************************/
int generation(char *** world, int row, int col, int count);

/*************************************************************
 *Determines if cells are either dead alive or revived by 
 *counting how many cells are around it.
 *
 *@param world ~ 2D char array.
 *@param row ~ the number of rows in the array.
 *@param col ~ the number of columns in the array
 *@return returns zero if all is well.
 ************************************************************/
int update(char ** world, int row, int col);

/***********************************************************
 *Clears all the dead cells from the world.
 *
 *@param world ~ 2D char array.
 *@param row ~ the number of rows in the board.
 *@param col ~ the number of columns in the board.
 **********************************************************/
void bring_out_your_dead(char ** world, int row, int col);

/**************************************************************
 *Prints out the contents of a 2D char array with row and col.
 *
 *@param world ~ 2D char array
 *@param row ~ the number of rows in the array
 *@param col ~ the number of columns in the array
 *************************************************************/
void print(char ** world, int row, int col);

/*******************************************************
 *Frees a 2D char array of the memory it was allocated
 *to use.
 *
 *@param world ~ 2D char array.
 *@param row ~ the number of rows in the char array.
 *@return returns zero if all is well.
 ******************************************************/
int free_mem(char *** world, int row);

/***********************************************************************
 *Converts a int to a string.
 *
 *@param num ~ the number that will be converted to a string.
 *@param str ~ the string that will contain the number as a string. 
 **********************************************************************/
void toString(int num, char * str);

/*********************************************************************
 *Replaces all characters in a 2D char array with blank spaces.
 *
 *@param world ~ 2D char array
 *@param row ~ the number of rows in the array
 *@param col ~ the number of columns in the array
 ********************************************************************/
void clear(char ** world, int row, int col);

/**********************************************************************
 *Runs the game. Provides a text interface for the user and responds
 *accordingly to user input.
 *
 *@param world ~ 2D char array that represents the cell world.  
 *@param row ~ the number of rows in the array.
 *@param col ~ the number of columns in the array.
 *********************************************************************/
void doit(char ** world, int row, int col);

/***********************************************************************
 * Gets user input. 
 *
 *@param input ~ pointer to a char array that takes in the users input. 
 **********************************************************************/
void input(char * input);
	
#endif

