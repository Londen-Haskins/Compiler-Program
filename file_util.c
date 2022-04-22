#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include <stdbool.h>	//for boolean
#include "file_util.h"	//include file_util header
#include "scanner.h"	//include scannner header
#include "parser.h"	//include scannner header


void wrapUp(){			//closes opened files and delets them temp (deleting temp is currently disables "commented out")
	printf("Closed Files:\n");
	int closedNum = 0;
	if(inputFileFlag != 0){
		++closedNum;
		fclose(in_file);
		printf("%i. Input File (closed)\n", closedNum);
	}
	if(outputFileFlag != 0){
		++closedNum;
		fclose(out_file);
		printf("%i. Output File (closed)\n", closedNum);
	}
	if(listFileFlag != 0){
		++closedNum;
		fclose(list_file);
		printf("%i. Listing File (closed)\n", closedNum);
	}
	if(tempFileFlag != 0){
		++closedNum;
		fclose(temp_file);
//		remove(tempFile);
//		if(remove(tempFile) == 0){
//			printf("Tempory file destroyed\n");
//		}
//		else{
//			printf("TEMP FILE: Unable to destroy\n");
//		}
		printf("%i. Temporary File (closed)\n", closedNum);
	}
	if(inputFileFlag == 0 && outputFileFlag == 0 && listFileFlag == 0 && tempFileFlag == 0 ){
		printf("No files were opened or created.\n");
	}
	
	
	
	//DELETES THE TEMP FILE//
//	remove(tempFile);
//	if(remove(tempFile) == 0){
//		printf("Tempory file destroyed\n");
//	}
//	else{
//		printf("TEMP FILE: Unable to destroy\n");
//	}
}


void temporaryFileHandling(){		//parameter = temp_file (its a pointer to the temp file)
	//give the temp file a name (compare it to the output file name and give it a TEMP at the end)
	strcpy(tempFile, "tempFile.txt");
	tempExt = strchr(tempFile, '.');
	strcpy(tempBase, "tempFile");
	
	//if the name you are trying to use ALREADY EXISTS, try a different name
	if(doesFileExist(&temp_file, tempFile) != 0){
		char buffer[50];
		int addedNum = 0;
		do{
			snprintf(buffer, 100, "%s%i", tempBase, addedNum); 		//puts string into buffer and adds number
			strcpy(tempFile, buffer);	//stores buffer into "tempFile" to test if exists
			strcat(tempFile, ".txt");
			addedNum ++;
		}while(doesFileExist(&temp_file, tempFile) != 0);
	strcpy(tempFile, buffer);	//stores the buffer name into tempFile
	strcat(tempFile, ".txt");
	temp_file = fopen(tempFile, "w");
	tempFileFlag++;
	printf("TEMP FILE: New file name: %s\n", tempFile);
	}
	
	//else if temp file doesn't exist, make it
	else{
		temp_file = fopen(tempFile, "w");
		tempFileFlag++;
		printf("TEMP FILE: Create with name: %s\n\n", tempFile);
	}
	int x = 5, i = 0;
//	for(i=0; i<x; i){
//		printf("Destroying 'temp file' in %i second(s)\n", x);
//		sleep(1);
//		x--;
//	}
}




void listingFileHandling(char *file){	//this creates the LIS and Temporary file names from the output name
	strcpy(listingFile, outputBase);
	strcat(listingFile, ".LIS");
	if(doesFileExist(&list_file, file) == 1){	//if file does exist, open it
		list_file = fopen(listingFile, "w");
		printf("LISTING: File already exists and is now opened file: %s\n", listingFile);
		listFileFlag ++;
	}
	else{
		list_file = fopen(listingFile, "w");	//if file doesn't exist create
		listFileFlag ++;
		printf("LISTING: File did not exist and was created as file: %s\n", listingFile);
	}
	
	
	///////////////////////////////////////////////////////////////////
	//// This copies everything from the input to the listing file ////
//	in_file = fopen(inputFile, "r"); // open input file in here to write to the listing file
	inputFileFlag ++;
//	while(!feof(in_file)){
//		fgets(fileInformation, 1000, in_file);	//read from the input
//		//printf("\n%s", fileInformation);	//this just prints to console to check if the file is reading correctly
//		fprintf(list_file, fileInformation);	//put into the .LIS file
//	}
//	printf("\nProcessing listing file");
//	int i, x = 3;
//	for(i=0; i<x; i++){
//		printf(".");
//		sleep(1);
//	}
//	printf("\nInput file now copied all information (including comments) to the '.LIS' file.");
	
}






void takeAndTest(char *file){		//takes input from users and runs the tests on it
	if(fileType == 1){
		strcpy(fillerName, "INPUT");		
	}
	else if(fileType == 2){
		strcpy(fillerName, "OUTPUT");
	}
	
	printf("\n\n---------------------ERROR---------------------");
	printf("\n%s file does not exist.\n", fillerName);
	if(fileType == 1){
		printf("If you hit ENTER, program will terminate!\n");
	}
	else if(fileType ==2){
		printf("If you hit 'ENTER', program will assign file name.\n");
	}
	printf("-------------------------------------------------\n");
	printf("Enter new %s file: ", fillerName);
	
	

	gets(file);		
	tempExt = strchr(file, '.');
	sscanf(file, "%[a-zA-Z0-9 ]", tempBase);	//only reads letters and numbers input "tempBase" (stops at spaces)
	//strcpy(file, tempBase);	//stores new name into the correct variable to pass back to main.c
		
	////////////////////
	/* FOR INPUT FILE */			
		
	if(fileType == 1){
		//printf("\n\n(Input testing) ------ DELETE THIS WHEN DONE\n\n");
		if(strcmp(file, "") != 0){	//if user enters something other than ENTER
			if(doesFileExist(&in_file, file) == 0){		//if file doesn't exist
				if(extensionCheck(file) == 0){		//if there IS NOT a ".", make the ".IN" extension
					printf("(input) no extension entered\n");
					strcat(file, ".IN");
					in_file = fopen(file, "w");	//if the file doesn't exist, this creates it
					inputFileFlag ++;
				}
				else{
					in_file = fopen(file, "w");	//if the file doesn't exist, this creates it
					inputFileFlag ++;
				}
			}
			else{	//if the file exists, then open it
				in_file = fopen(file, "r");	//this may need to be "r" im not sure
				inputFileFlag ++;
			}
			printf("INPUT FILE: File is now open with the name: %s\n", file);
			strcpy(inputBase, tempBase);	//this is used to make the output file name if none is given
			inputExt = strchr(file, '.');
			
			// these just test the variables //
			//printf("(Var test) inputBase = %s\n", inputBase);
			//printf("(Var test) inputExt = %s\n", inputExt);	
		}
		else {
			flag ++;
		}
	}
		
		
		
		
	/////////////////////
	/* FOR OUTPUT FILE */
		
	else if(fileType == 2){
	//printf("\n\n(Output testing)------ DELETE THIS WHEN DONE\n\n");
		if(strcmp(file, "") != 0 || strcmp(inputFile, file)){						//if user enters SOMETHING other than "ENTER" key
			
			do{		//making sure there are duplicates (input -> output)
				if(strcmp(inputFile, file) == 0){	//if they ARE the same
					printf("\n---------------------ERROR---------------------\n");
					printf("Input and Output cannot be the same.\nIf you hit 'ENTER', program will assign one.\n");
					printf("-------------------------------------------------\n");
					printf("Enter new output file: ");
					gets(file);
					printf("\n");
				}
			}while(strcmp(inputFile, file) == 0 || strcmp(file, "") == 1);

			if(doesFileExist(&out_file, file) == 0){	//if file doesn't exist, but they entered SOMETHING
				if(strcmp(file,"") == 0){		//if they hit enter in the loop then give it the file name of "input base + ".OUT""
					strcpy(file, inputBase);
				}
				if(extensionCheck(file) == 0){			//if they don't have an extension, make the ".OUT"
					strcat(file, ".OUT");
				}
					out_file = fopen(file, "w");	//create the output file
					outputFileFlag ++;
					outputExt = strchr(file, '.');
					strcpy(outputBase, tempBase);
			}
			else{	//if the file does exist
				//i did this way bc we can't use breaks...
				//give choice to overwrite the exisiting output file, enter a new output file name, or terminate
				outputExt = strchr(file, '.');
				printf("Output file DOES exist. Choose between the following options:\n");
				printf("1. Overwrite the exisiting output file\n");
				printf("2. Enter a new ouput file name\n");
				printf("3. Terminate program\n");
				int outputOption = 0;
				int count = 0;
				scanf("%i", outputOption);
				do{					//did this because we can't use breaks
					if(count > 0){
						printf("You must've mistyped, retry\n");
					}
					if(outputOption == 1){		//overwrite the exisiting output file
						printf("Enter you");
						gets(file);
						strcpy(outputFile, file);
					}
					else if(outputOption == 2){	//enter a new output file name
					
					}
					else if(outputOption == 3){	//terminate program
						programTerminated();
					}
					count ++;
				}while(outputOption != 1 || outputOption != 2 || outputOption != 3 || count == 0);	
			}
			strcpy(outputBase, tempBase);	//this is used to make the output file name if none is given
			inputExt = strchr(file, '.');
			
			
			
		}
		else if(strcmp(file, "") == 0){	//if user doesn't type anything
			strcpy(file, inputBase);
			strcat(file, ".OUT");
			outputExt = strchr(file, '.');
			strcpy(outputBase, inputBase);
			outputFileFlag ++;
		}
	printf("OUTPUT FILE: Is now open now with the name: %s\n", file);
	}

	else{	//if user types "ENTER" then just exit program
		printf("Flag raised, exited program\n");
		flag++;
	}
}






int testForDupName(char *file){		//makes sure the output and input name are NOT the same (pass outputFile) into this
	if(!strcmp(inputFile, file)){
		do{
			printf("Input and output file cannot be the same. Please re-enter output file:");
			gets(file);
//			scanf("%s", file);
			fflush(stdin);
		}while(!strcmp(inputFile, file) || strcmp(file, "") != 0);
	}
	else{
		printf("Files are NOT the same. You are good to continue.\n\n");
	}
//	if(strcmp(file, "") != 0){
}

 

void init(int argc,char *argv[]){		//initalize the program (getting the input and output files working)
	flag = 0;
	inputFileFlag = 0;		//sets all of the flags to 0
	outputFileFlag = 0;
	listFileFlag = 0;
	tempFileFlag = 0;
	listNum = 1;
	lexErr = 0;
	synErr = 0;
	stateBufP = 0; //Position for statement buffer
	tkPtr = &tokenBuffer[0]; //Ptr to token buffer
	listPtr = &listBuffer[0];//Ptr to listing buffer
	newL = 0; //Toggle for new line list fault
	statePtr = &stateBuf[0];
	tokenList();

 	if(argc <= 3){
		if(argc == 2){
			strcpy(inputFile, argv[1]);			//copy the name from "argv[1]" to the inputFile (variable)
			readAndParse(inputFile, 1);			// "1" just means its the input file
		}
		else if(argc == 3){
			strcpy(inputFile, argv[1]);
			strcpy(outputFile, argv[2]);
			testForDupName(outputFile);
		}
		getInputFile(inputFile);
		//printf("\n\n");
		if(flag == 0){		//if the user actually enters an input file (not hitting ENTER) it asks for output
			
			
			////////////////////////////////////////////////////////
			//////////   REST OF MAIN GOES HERE    /////////////////
			
			getOutputFile(outputFile);
			listingFileHandling(listingFile);
	
			fprintf(list_file,"%d .		",listNum);
			parser();
			temporaryFileHandling();			
			
		}	
	}
	
	
	else{	//if the parameters are more than 3, terminate
		printf("Too many parameters entered.\n");
	}
	programTerminated();
}



void getInputFile(char *file){
	fileType = 1;		// just put this at the front of a function that is specifically for INPUT
	if(doesFileExist(&in_file, file) == 0){	//if file DOES NOT exist
		takeAndTest(file);
	}
	else{	//if it does exist, just open it
		readAndParse(file, 1);
		in_file = fopen(file, "rb+");
		printf("INPUT: File exists and is opened: %s\n", file);
		inputFileFlag++;
	}
}



void getOutputFile(char *file){
	fileType = 2; //set to "2" for the output file. just helps with print statements in other functions
	if(doesFileExist(&out_file, file) == 0){	//if the file DOESN'T exist, do this
		takeAndTest(file);
		outputFileFlag++;
	}
	else{	//if file does exists
		outputFileFlag++;	//set flag to know that file is open
		readAndParse(file, 2);
		printf("OUTPUT: File exists: %s\n", file);
	}
}


int extensionCheck(char *file){
	if(strchr(file, '.') != NULL){
		return 1;
	}
	else{
		return 0;
	}
}



int doesFileExist(FILE** filePointer, char *fileName){       //if((inf = fopen(fnamein, "r")) == NULL)
		if((*filePointer = fopen(fileName, "r")) == NULL)
		{
			//printf("File DOES NOT exist.\n");
			return 0;
		}
		else{
			//printf("File does exist\n");
			return 1;
		}
}



void printFileNames(){		//this is just for testing purposes
	printf("\n------INPUT FILE------\n");
	printf("Input: %s\n", inputFile);
	printf("InputBase = %s\nInputExt = %s\n\n", inputBase, inputExt);
	
	printf("------OUTPUT FILE------\n");
	printf("Output: %s\n", outputFile);
	printf("OutputBase = %s\nOutputExt = %s\n", outputBase, outputExt);

	printf("------OTHER FILE------\n");
	printf("Listing file: %s\n", listingFile);
	printf("Temp file: %s\n", tempFile);
	
	printf("\n-------------------------\n\n");
}



void programTerminated(){
	printf("\n\n------PROGRAM TERMINATED------\n");
}



void readAndParse(char *file, int fileType){ //reads the file name and parse's the information out to a base and ext (just to have the option)
	char fileName[50];
	strcpy(fileName, file);
	if(fileType == 1){
		inputExt = strchr(file, '.');				//save the extension name (if it has one)
		sscanf(file, "%[a-zA-Z0-9]", inputBase);	//read everything before the "." to save that name (inputBase)
	}
	else if(fileType == 2){
		outputExt = strchr(file, '.');				//save the extension name (if it has one)
		sscanf(file, "%[a-zA-Z0-9]", outputBase);	//read everything before the "." to save that name (inputBase)
	}
}


