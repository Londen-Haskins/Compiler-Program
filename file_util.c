#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include <stdbool.h>	//for boolean
#include "file_util.h"	//include file_util header
#include "scanner.h"	//include scannner header

enum token scanner(char *tokBuf,FILE *inFile,FILE *out_file,FILE *listFile){	
	char c,k;
	int p;
	
	clear_buffer(tokBuf);
	fpos_t pos;
			
	//Eat whitespace and start main scanner loop
	do{
		c = fgetc(inFile);
		//Change to while loop
		if(isspace(c)){
			if(c == '\n'){
				listNum++;
				fprintf(listFile,"\n%d .		",listNum);
			}
			else{
				fprintf(listFile,"%c",c);
			}
			//DO A CHECK HERE TO LOOK AHEAD AND SEE IF NEXT CHARACTER IS WHITESPACE
			//THEN RETREAT IN_FILE POINTER IF IT'S NOT
		}
	}while(isspace(c));

	if(!isspace(c)){
		p = 0;
		//If character is alphabetical
		if(isalpha(c)){
			k = c;
			do{
				add_char(tokBuf,k,p);
				p++;
				k = fgetc(inFile);
				if(!isalpha(k)){
					//Retreat file pointer
					fgetpos(inFile, &pos);
					pos--;
					fsetpos(inFile, &pos);
				}
			}while(isalpha(k));
			printf("Current buffer: %s\n",tkPtr);
		}
		else if(isdigit(c)){
			k = c;
			do{
				add_char(tokBuf,k,p);
				p++;
				k = fgetc(inFile);
				if(!isdigit(k)){
					fgetpos(inFile, &pos);
					pos--;
					fsetpos(inFile, &pos);
				}
			}while(isdigit(k));
			printf("Current intliteral buffer: %s\n",tkPtr);

		}
			
		//Remaining test cases
		
		else if(c == '<'){
			add_char(tokBuf,c,p);
			k = getc(inFile);
			if(k == '='){
				p++;
				add_char(tokBuf,k,p);
			}
			else{
				fgetpos(inFile, &pos);
				pos--;
				fsetpos(inFile, &pos);
			}
		}
		else if(c == '>'){
			add_char(tokBuf,c,p);
			k = getc(inFile);
			if(k == '='){
				p++;
				add_char(tokBuf,k,p);
			}
			else{
				fgetpos(inFile, &pos);
				pos--;
				fsetpos(inFile, &pos);
			}
		}

		else if(c == ':'){
			k = c;
			add_char(tokBuf,k,p);
			k = getc(inFile);
			if(k == '='){
				p++;
				add_char(tokBuf,k,p);
				printf("Current buffer: %s\n",tkPtr);
			}
			else{
				fgetpos(inFile, &pos);
				pos--;
				fsetpos(inFile, &pos);
			}
		}
		
		else if(c == '-'){
			add_char(tokBuf,c,p);
			k = getc(in_file);
			if(isdigit(k)){
				while(isdigit(k)){
					p++;
					add_char(tokBuf,k,p);	
					k = getc(inFile);
					
				}
				if(!isdigit(k)){
					fgetpos(inFile, &pos);
					pos--;
					fsetpos(inFile, &pos);
				}
				
			}
			else if(k == '-'){
				
				while(k != '\n'){
					p++;
					add_char(tokBuf,k,p);	
					k = getc(inFile);
					if(k == '\n'){
						fgetpos(inFile, &pos);
						pos--;
						fsetpos(inFile, &pos);
					}
				}
			}
		}
		else{
			add_char(tokBuf,c,p);	
		}
	fputs(tokBuf,listFile); //Add buffer to listing file	
	}
	return check_reserved(tokBuf);		
}

//Returns enum of the buffer	
enum token check_reserved(char *tk)
{
	if(!strcmp(tk, "begin")){
		return BEGIN;
	}
	else if(!strcmp(tk, "end")){
		return END;
	}
    else if(!strcmp(tk, "read")){
		return READ;
	}
	else if(!strcmp(tk, "write")){
		return WRITE;
	}
	else if(!strcmp(tk, "if")){
		return IF;
	}
	else if(!strcmp(tk, "then")){
		return THEN;
	}
	else if(!strcmp(tk, "else")){
		return ELSE;
	}
	else if(!strcmp(tk, "endif")){
		return ENDIF;
	}
	else if(!strcmp(tk, "while")){
		return WHILE;
	}
	else if(!strcmp(tk, "endwhile")){
		return ENDWHILE;
	}
	else if(!strcmp(tk, "true")){
		return TRUEOP;
	}
	else if(!strcmp(tk, "false")){
		return FALSEOP;
	}
	else if(!strcmp(tk, ":=")){
		return ASSIGNOP;
	}
	else if(!strcmp(tk, "<>")){
		return NOTEQUALOP;
	}
	else if(!strcmp(tk, "==")){
		return EQUALOP;
	}
	else if(!strcmp(tk, "<=")){
		return LESSEQUALOP;
	}
	else if(!strcmp(tk, "<")){
		return LESSOP;
	}
	else if(!strcmp(tk, ">=")){
		return GREATEREQUALOP;
	}
	else if(!strcmp(tk, ">")){
		return GREATEROP;
	}
	else if(!strcmp(tk, "*")){
		return MULTOP;
	}
	else if(!strcmp(tk, "/")){
		return DIVOP;
	}
	else if(!strcmp(tk, "!")){
		return NOTOP;
	}
	else if(!strcmp(tk, ",")){
		return COMMA;
	}
	//else if(!strcmp(tk, ";")){
	else if(tk[0] == ';'){
		return SEMICOLON;
	}
	else if(!strcmp(tk, "+")){
		return PLUSOP;
	}
	else if(!strcmp(tk, "-")){
		return MINUSOP;
	}
	else if(!strcmp(tk, "(")){
		return LPAREN;
	}
	else if(!strcmp(tk, ")")){
		return RPAREN;
	}
	//else if(tk[0] == "\n" || tk[0] == "\f"){
//		return EOL;
//	}
	else if(isalpha(tk[0])){
		return ID;
	}
	else if(isdigit(tk[0])){
		return INTLITERAL;
	}
	else if(!strcmp(tk," ")){
		return SPACE;
	}
	printf("Token does not have match in reserved words or is EOL\n");
	return ERROR;

}

void tokenList(){

	tkList[0] = "begin";
	tkList[1] = "end";
	tkList[2] = "read";
	tkList[3] = "write";
	tkList[4] = "if";
	tkList[5] = "then";
	tkList[6] = "else";
	tkList[7] = "endif";
	tkList[8] = "while";
	tkList[9] = "endwhile";
	tkList[10] = "id";
	tkList[11] = "intliteral";
	tkList[12] = "falseop";
	tkList[13] = "trueop";
	tkList[14] = "nullop";
	tkList[15] = "lparen";
	tkList[16] = "rparen";
	tkList[17] = "semicolon";
	tkList[18] = "comma";
	tkList[19] = "assinop";
	tkList[20] = "plusop";
	tkList[21] = "minusop";
	tkList[22] = "multop";
	tkList[23] = "divop";
	tkList[24] = "notop";
	tkList[25] = "lessequalop";
	tkList[26] = "greaterop";
	tkList[27] = "greaterequalop";
	tkList[28] = "equalop";
	tkList[29] = "notequalop";
	tkList[30] = "EOF";
	tkList[31] = "SPACE";
	tkList[32] = "ERROR";
	
	return;
}

//Clears the token buffer
void clear_buffer(char* buf){
	//tkPtr = &tokenBuffer[0];
	memset(buf,0,TKLEN);
}

//Adds character to the end of the buffer
void add_char(char* buf,char c,int p){
	//printf("Adding '%c' to the buffer\n",c);   
	buf[p] = c;
}

//The parser will facilitate printing to list file.
//Listing will delimit at new line token, increase listing file line number, and repeat
void parser(){

	bool accepted = false;
	while(!accepted){
		//errorC = system_goal();
//		if(errorC = 0){
//			accepted = true;
		if(system_goal() == 0){
			accepted = true;
		};
	}	
	return;
}

//Function that allows matching of parse stack symbols and input stack symbols
//Token is the exected token value that we're looking for
bool match(enum token token, char *tokBuf){
	enum token nxtTk;
	int i = 0;
	nxtTk = next_token();
	if(nxtTk == token){
		printf("Match for token %d is true\n", token);
		while(tokenBuffer[i] != '\0'){
			add_char(tokBuf,tokenBuffer[i],stateBufP);
			i++;
			stateBufP++;
		}
		fsetpos(in_file, &posA);
		fprintf(out_file,"EXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",tkList[token],tkPtr);
		return true;
	}
	else{
		//Lexical error
		printf("Match for token %d is false\n", token);
		while(tokenBuffer[i] != '\0'){
			add_char(tokBuf,tokenBuffer[i],stateBufP);
			i++;
			stateBufP++;
		}
		fsetpos(in_file, &posA);
		//error(Expected token);
		//fprintf("EXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",,);
		return false;
	}
}

enum token next_token(){
	fgetpos(in_file, &posN);
	//Calls scanner for a token and returns the next token(non-destructive) and doesn't change file pointer
	enum token nTk = scanner(tkPtr,in_file,out_file,list_file);
	fgetpos(in_file,&posA);
	//Retreat in_file pointer that scanner() advanced
	fsetpos(in_file, &posN);
	//Used to find appropriate production
	return nTk;
}

int system_goal(){
	program_rule();
	printf("\n PARSER SUCCESSFUL\n");
	
	return 0;
}

//Production 1
int program_rule(){
	if(!match(BEGIN,statePtr)){
		lexErr++;
	}
	statement_list();
	if(!match(END,statePtr)){
		lexErr++;
	}	
	return 0;
}

//Production 2
int statement_list(){
	bool stateExist = false;
	int stateS = 0;
	enum token nxtTk;
	
	do{
		statement();
		nxtTk = next_token(tkPtr);
		printf("\nToken used for loop check in statement_list: %d \n",nxtTk);
		switch(nxtTk){
			case ID:
				stateExist=true;
				break;
			case READ:
				stateExist=true;
				break;
			case WRITE:
				stateExist=true;
				break;
			case IF:
				stateExist=true;
				break;
			default:
				stateExist=false;
		}
		
	}while(stateExist);

	return stateS;
}

int statement(){
	//enum token nxtTk;
	int nxtTk;

	printf("\nRunning statement production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 3
		case 10:
			printf("\nRunning statement production rule 3\n");
			if(!match(ID,statePtr)){
				lexErr++;
			}
			if(!match(ASSIGNOP,statePtr)){
				lexErr++;
			}			
			expression();
			if(!match(SEMICOLON,statePtr)){
				lexErr++;
			}
			break;
		//Production 4
		case 2:
			printf("\nRunning statement production rule 4\n");
			if(!match(READ,statePtr)){
				lexErr++;
			}
			if(!match(LPAREN,statePtr)){
				lexErr++;
			}
			id_list();
			if(!match(RPAREN,statePtr)){
				lexErr++;
			}
			if(!match(SEMICOLON,statePtr)){
				lexErr++;
			}
			break;
		//Production 5
		case 3:
			printf("\nRunning statement production rule 5\n");
			if(!match(WRITE,statePtr)){
				lexErr++;
			}
			if(!match(LPAREN,statePtr)){
				lexErr++;
			}
			expr_list();
			if(!match(RPAREN,statePtr)){
				lexErr++;
			}
			if(!match(SEMICOLON,statePtr)){
				lexErr++;
			}
			break;
		//Production 6
		case IF:
			printf("\nRunning statement production rule 6\n");
			if(!match(IF,statePtr)){
				lexErr++;
			}
			condition();
			if(!match(THEN,statePtr)){
				lexErr++;
			}
			statement_list();
			if_tail();
			break;
		//Production 9
		case 8:
			printf("\nRunning statement production rule 8\n");
			if(!match(WHILE,statePtr)){
				lexErr++;
			}
			condition();
			statement_list();
			if(!match(ENDWHILE,statePtr)){
				lexErr++;
			}
			break;	
	}
	fprintf(out_file,"\nCurrent statement: %s \n", statePtr);
	stateBufP = 0;
	clear_buffer(statePtr);
	return 0;
}

int if_tail(){
	enum token nxtTk;
	printf("\nRunning if_tail production\n");
	nxtTk = scanner(tkPtr,in_file,out_file,list_file);
	
	switch(nxtTk){
		//Production 7
		case ELSE:
			printf("\nRunning if_tail production rule 7\n");
			if(!match(ELSE,statePtr)){
				lexErr++;
			}
			statement_list();
			if(!match(ENDIF,statePtr)){
				lexErr++;
			}
			break;
		
		//Production 8
		case ENDIF:
			printf("\nRunning if_tail production rule 8\n");
			if(!match(ENDIF,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;
}

//Production 10
int id_list(){
	enum token repeat;
	printf("\nRunning id_list production\n");
	if(!match(ID,statePtr)){
		lexErr++;
	}
	repeat = next_token(tkPtr);
	while(repeat==COMMA){
		if(!match(COMMA,statePtr)){
			lexErr++;
		}
		id_list();
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 11
int expr_list(){
	enum token repeat;
	printf("\nRunning expr_list production\n");
	expression();
	repeat = next_token(tkPtr);
	while(repeat==COMMA){
		if(!match(COMMA,statePtr)){
			lexErr++;
		}
		expr_list();
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 12
int expression(){
	enum token repeat;
	printf("\nRunning expression production\n");
	term();
	repeat = next_token(tkPtr);
	while(repeat==PLUSOP || repeat==MINUSOP){
		add_op();
		term();
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 13
int term(){
	enum token repeat;
	printf("\nRunning term production\n");
	factor();
	repeat = next_token(tkPtr);
	printf("\n Using this token for production 13 check loop\n");
	while(repeat==MULTOP || repeat==DIVOP){
		mult_op();
		factor();
		repeat = next_token(tkPtr);
	}
	return 0;
}

int factor(){
	enum token nxtTk;
	printf("\nRunning factor production\n");
	nxtTk = next_token(tkPtr);
	printf("\n Token for factor switch: %d\n", nxtTk);
	switch(nxtTk){
		//Production 14
		case LPAREN:
			printf("\nRunning factor production rule 14\n");
			if(!match(LPAREN,statePtr)){
				lexErr++;
			}
			expression();
			if(!match(RPAREN,statePtr)){
				lexErr++;
			}
			break;
		//Production 15
		case MINUSOP:
			printf("\nRunning factor production rule 15\n");
			if(!match(MINUSOP,statePtr)){
				lexErr++;
			}
			factor();
			break;
		//Production 16
		case ID:
			printf("\nRunning factor production rule 16\n");
			if(!match(ID,statePtr)){
				lexErr++;
			}
			break;
		//Production 17
		case INTLITERAL:
			printf("\nRunning factor production rule 17\n");
			if(!match(INTLITERAL,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;	
}

int add_op(){
	enum token nxtTk;
	printf("\nRunning add_op production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 18
		case PLUSOP:
			printf("\nRunning add_op production rule 18\n");
			if(!match(PLUSOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 19
		case MINUSOP:
			printf("\nRunning add_op production rule 19\n");
			if(!match(MINUSOP,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;
}

int mult_op(){
	enum token nxtTk;
	printf("\nRunning mult_op production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 20
		case MULTOP:
			printf("\nRunning mult_op production rule 20\n");
			if(!match(MULTOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 21
		case DIVOP:
			printf("\nRunning mult_op production rule 21\n");
			if(!match(DIVOP,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;
}

//Production 22
int condition(){
	enum token repeat;
	printf("\nRunning condition production\n");
	addition();
	repeat = next_token(tkPtr);
	while(repeat==LESSOP || repeat==LESSEQUALOP || repeat==GREATEROP || repeat==GREATEREQUALOP || repeat==NOTEQUALOP || repeat==EQUALOP){
		rel_op();
		addition();
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 23
int addition(){
	enum token repeat;
	printf("\nRunning addition production\n");
	multiplication();
	repeat = next_token(tkPtr);
	while(repeat==PLUSOP || repeat==MINUSOP){
		add_op();
		multiplication();
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 24
int multiplication(){
	enum token repeat;
	printf("\nRunning multiplication production\n");
	unary();
	repeat = next_token(tkPtr);
	while(repeat==MULTOP || repeat==DIVOP){
		mult_op();
		unary();
		repeat = next_token(tkPtr);
	}
	return 0;
}

int unary(){
	enum token nxtTk;
	printf("\nRunning unary production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 25
		case NOTOP:
			if(!match(NOTOP,statePtr)){
				lexErr++;
			}
			unary();
			break;
		//Production 26
		case MINUSOP:
			if(!match(MINUSOP,statePtr)){
				lexErr++;
			}
			unary();
			break;
		//Production 27
		case INTLITERAL:
			lprimary();
			break;
		case ID:
			lprimary();
			break;
		case LPAREN:
			lprimary();
			break;
		case FALSEOP:
			lprimary();
			break;
		case TRUEOP:
			lprimary();
			break;
		case NULLOP:
			lprimary();
			break;
	}
	return 0;
}

int lprimary(){
	enum token nxtTk;
	printf("\nRunning lprimary production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 28
		case INTLITERAL:
			printf("\nRunning lprimary production rule 28\n");
			if(!match(INTLITERAL,statePtr)){
				lexErr++;
			}
			break;
		//Production 29
		case ID:
			printf("\nRunning lprimary production rule 29\n");
			if(!match(ID,statePtr)){
				lexErr++;
			}
			break;
		//Production 30
		case LPAREN:
			printf("\nRunning lprimary production rule 30\n");
			if(!match(LPAREN,statePtr)){
				lexErr++;
			}
			condition();
			if(!match(RPAREN,statePtr)){
				lexErr++;
			}
			break;
		//Production 31
		case FALSEOP:
			printf("\nRunning lprimary production rule 31\n");
			if(!match(FALSEOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 32
		case TRUEOP:
			printf("\nRunning lprimary production rule 32\n");
			if(!match(TRUEOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 33
		case NULLOP:
			printf("\nRunning lprimary production rule 33\n");
			if(!match(NULLOP,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;
}

int rel_op(){
	enum token nxtTk;
	printf("\nRunning rel_op production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 34
		case LESSOP:
			printf("\nRunning rel_op production rule 34\n");
			if(!match(LESSOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 35
		case LESSEQUALOP:
			printf("\nRunning rel_op production rule 35\n");
			if(!match(LESSEQUALOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 36
		case GREATEROP:
			printf("\nRunning rel_op production rule 36\n");
			if(!match(GREATEROP,statePtr)){
				lexErr++;
			}
			break;
		//Production 37
		case GREATEREQUALOP:
			printf("\nRunning rel_op production rule 37\n");
			if(!match(GREATEREQUALOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 38
		case EQUALOP:
			printf("\nRunning rel_op production rule 38\n");
			if(!match(EQUALOP,statePtr)){
				lexErr++;
			}
			break;
		//Production 39
		case NOTEQUALOP:
			printf("\nRunning rel_op production rule 39\n");
			if(!match(LESSOP,statePtr)){
				lexErr++;
			}
			break;
	}
	return 0;
}

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
			//copyAndPaste(inputFile, outputFile);	//copies information from file 1 (input) to file 2 (output) and listing always gets it
			
			//THIS LOOP WILL BE REPLACED BY THE PARSER
			//Loop until the 'end token is read
			
//			while(tok != END){
//				//Print token information to output file
//				//Use char tokenBuffer
//				tok = scanner(tkPtr,in_file,out_file,list_file);	//this is to make the program use the token functions
//				fprintf(list_file,"\n");
//				printf("Token type num: %d	Token string: %s \n",tok,tkPtr);
//			}
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
		//sscanf(file, "%[a-zA-Z0-9]", tempBase);
		//strcpy(inputBase, tempBase);
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
		//out_file = fopen(file, "r");
		printf("OUTPUT: File exists: %s\n", file);
	}
}



void copyAndPaste(char *file1, char *file2){	//setup to work as (from, to) (from, destination) THIS ONLY WORKS FOR INPUT / OUTPUT RIGHT NOW
	in_file = fopen(file1, "r");
	out_file = fopen(file2, "w");
//	list_file = fopen(listingFile, "w");
	while(!feof(in_file)){
		fgets(fileInformation, 1000, in_file);	//read the "from" file
		printf("\n%s", fileInformation);
		//int tkFlg = scanner(fileInformation);
		fprintf(out_file, fileInformation);		//put onto the "destination" file
		
	}
}



int extensionCheck(char *file){
	if(strchr(file, '.') != NULL){
//		printf("There is a '.' for %s\n", file);
		return 1;
	}
	else{
//		printf("There is NOT '.' for %s\n", file);
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


