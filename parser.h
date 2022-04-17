#ifndef PARSER
#define PARSER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TKLEN 1000

enum token{
		BEGIN,END,READ,WRITE,IF,THEN,ELSE,
		ENDIF,WHILE,ENDWHILE,ID,INTLITERAL,
		FALSEOP,TRUEOP,NULLOP,LPAREN,RPAREN,
		SEMICOLON,COMMA,ASSIGNOP,PLUSOP,MINUSOP,
		MULTOP,DIVOP,NOTOP,LESSOP,LESSEQUALOP,
		GREATEROP,GREATEREQUALOP,EQUALOP,NOTEQUALOP,SCANEOF,SPACE,ERROR
	};

char stateBuf[TKLEN];
char tokenBuffer[TKLEN];
char *tkPtr, *statePtr;
int listNum, lexErr, synErr, stateBufP;
fpos_t posN, posA; //File pointer position for parser and position for match()
enum token tok,tokTemp,tkTmp;
const char *tkList[32];


void parser();
bool match(enum token token, char *tokBuf);
enum token next_token();
int system_goal();
int program_rule();
int statement_list();
int statement();
int id_list();
int expr_list();
int expression();
int term();
int factor();
int add_op();
int mult_op();
int condition();
int addition();
int multiplication();
int unary();
int lprimary();
int rel_op();


#endif
