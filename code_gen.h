#ifndef CODE_GEN
#define CODE_GEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TABLEC 100
#define TABLEL 30
char symbolTable[TABLEC][TABLEL];
int tableIndex,tempNum;
enum exprType{idEXPR,litEXPR,tempEXPR};

typedef struct {
	char operation[2];
}op_recStr;

typedef struct {
	char expression[70];
	enum exprType type;
}expr_recStr;

//Checks if symbol table contains symbol string
bool lookup(char*symbol);

//Adds symbol string to table
void enter(char*symbol);

void check_id(char*symbol);

//Generates intermediate code string
//Recieves up to 5 strings and writes to temp with ';'
void generate(char*strA);

//Creates a temporary ID
//Returns next temporary id string
char*getTemp();

void startAct();
void finishAct();
void assignAct();
void read_idAct();
void write_exprAct();
expr_recStr gen_infixAct(expr_recStr left,op_recStr op,expr_recStr right);
expr_recStr process_literalAct();
expr_recStr process_idAct();
op_recStr process_opAct();



#endif
