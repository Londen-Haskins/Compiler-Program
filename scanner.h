#ifndef SCANNER
#define SCANNER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TKLEN 1000
char tokenBuffer[TKLEN];
char listBuffer[TKLEN];
char *tkPtr, *statePtr, *listPtr;
int listNum, lexErr, synErr, stateBufP,newL;




//EOL is token 32
enum token{
		BEGIN,END,READ,WRITE,IF,THEN,ELSE,
		ENDIF,WHILE,ENDWHILE,ID,INTLITERAL,
		FALSEOP,TRUEOP,NULLOP,LPAREN,RPAREN,
		SEMICOLON,COMMA,ASSIGNOP,PLUSOP,MINUSOP,
		MULTOP,DIVOP,NOTOP,LESSOP,LESSEQUALOP,
		GREATEROP,GREATEREQUALOP,EQUALOP,NOTEQUALOP,SCANEOF,SPACE,ERROR
	};
	
const char *tkList[32];

enum token tok,tokTemp,tkTmp;
enum token scanner(char *buffer,FILE *inFile,FILE *out_file,FILE *listFile);
fpos_t posN, posA; //File pointer position for parser and position for match()


void clear_buffer(char*);
enum token check_reserved(char*tk);
void tokenList();
void add_char(char* buf,char c,int p);




#endif
