#ifndef PARSER
#define PARSER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "code_gen.h" //For expression record data type

#define TKLEN 1000

char stateBuf[TKLEN];
char tokenBuffer[TKLEN];
char *tkPtr, *statePtr;
int listNum, lexErr, synErr, stateBufP;
fpos_t posN, posA; //File pointer position for parser and position for match()
enum token tok,tokTemp,tkTmp;
const char *tkList[32];
bool listT;


void parser();
bool match(enum token token, char *tokBuf);
enum token next_token();
int system_goal();
int program_rule();
int statement_list();
int statement();
int id_list();
int expr_list();
void expression(expr_recStr *record);
void term(expr_recStr*operand);
void factor(expr_recStr*operand);
void add_op(op_recStr *op);
void mult_op(op_recStr *op);
expr_recStr condition();
void addition(expr_recStr *operand);
void multiplication(expr_recStr operand);
void unary(expr_recStr operand);
void lprimary(expr_recStr operand);
void rel_op(op_recStr *op);
expr_recStr ident();


#endif
