#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include <stdbool.h>	//for boolean
#include "code_gen.h"	//include code_gen header


//Checks if symbol table contains symbol string
bool lookup(char*symbol){
	bool flag = false;
	
	return flag;
}

//Adds symbol string to table
void enter(char*symbol){
	
	return;
}

//Generates intermediate code string
//Recieves up to 5 strings and writes to temp with ';'
void generate(char*strA){
	
	return;
}

//Creates a temporary ID
//Returns next temporary id string
char*getTemp(){
	char*nxtTemp;
	
	return nxtTemp;
}

void startAct(){
	//write descriptive heading to list and output files
	//init code_gen variables
}

void finishAct(){
	//write descriptive closing to list and output files
	//concatenate the two parts of C code
}

void assignAct(expr_recStr left,expr_recStr right){
	//Use 'left' = operator and 'right' to create C
	//ie. assign(target,source) Makes "X = Temp1;"
}

void read_idAct(expr_recStr temp){
	//Generate scanf statement
	//i.e. "scanf("%d",&x);"
	
	return;
}

void write_exprAct(expr_recStr temp){
	//Generate scanf statement
	//i.e. "printf("%d\n",x);"
	
	return;
}

expr_recStr gen_infixAct(expr_recStr left,expr_recStr right){
	expr_recStr temp;
	
	//set expr_rec temp to enum TEMPEXPR
	//set temp string to new temp ID by using getTemp()
	//Assign to temp: 'left' operation 'right'
	
	return temp;
}

expr_recStr process_literalAct(){
	expr_recStr litEXPR;
	
	//set new expr_rec to enum LITERAL EXPR
	//set string to token buffer (which is a number)
	
	return litEXPR;
}

expr_recStr process_idAct(){
	expr_recStr idEXPR;
	
	//set new expr_rec to enum ID EXPR
	//set string to token buffer (which is an ID)
	
	return idEXPR;
}

op_recStr process_opAct(){
	op_recStr op;
	//set new op_rec to operation type
	
	return op;
}
