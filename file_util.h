#ifndef FILE_UTIL
#define FILE_UTIL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>	//for boolean

FILE *in_file, *out_file;	//pointers for files (input/output)
FILE *list_file;			//listing file pointer
FILE *temp_file;			//temp file pointer
FILE *backup_file;



///////////////////////
// WORKING VARIABLES //
char inputFile[50];		//INPUT file.
char outputFile[50];	//OUTPUT file.
char listingFile[50];	//LISTING file
char tempFile[50];		//TEMPORARY file
char fileInformation[1000];		//used to store large files

char randomInformation[100]; 	//use this for anything random
int flag;				//add to this if you want to terminate program

int fileType;			//when working with input functions, type "1" at top, "2" for output.
char fillerName[15];	//just for print functions in the "takeAndTest" functions

char tempBase[50];		//just used to fix the name of the file (the file name without the ext) (used to be "tempFileName")
char *tempExt;			//makes a temporary extension incase they do enter an extension after an input with a bunch of spaces

char inputBase[50];		//stores the name of the input name (w/o) extension
char *inputExt;			//stores input extension

char outputBase[50];	//stores the name of the output file name (w/o) extension
char *outputExt;		//stores output extension

char inputName[50];		//to make sure the input and output names are NOT the same
char outputName[50];	//to make sure the input and output names are NOT the same



	//////////////
	//file flags//		Flag that lets us know if they files are open so they can use the function to close them
	//////////////
	
int inputFileFlag;	//input file flag
int outputFileFlag;	//output file flag
int listFileFlag;	//list file flag
int tempFileFlag;	//temporary file flag

///////////////////////
// WORKING FUNCTIONS //
void init();	//start program
void getInputFile(char *file);
void getOutputFile(char *file);
int doesFileExist(FILE** filePointer, char *fileName);
void printFileNames();
void programTerminated();
int extensionCheck(char *file);
void takeAndTest(char *file); 
void listingFileHandling(char *file);	//this is going to be for the listing file when we need it
void readAndParse(char *file, int fileType);	//gets the base and ext of a file name
void openFile(char inName[50]);
int testForDupName(char *file);
void closeOpenedFiles();
void temporaryFileHandling();



#endif
