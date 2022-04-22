#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include <stdbool.h>	//for boolean
#include "code_gen.h"	//include code_gen header
#include "scanner.h" //For token buffer ptr
#include "file_util.h" //For file pointer


//Checks if symbol table contains symbol string
bool lookup(char*symbol){
	bool flag = false;
	int i;
	for(i=0;i<TABLEC;i++){
		if(!strcmp(symbolTable[i],symbol)){
			flag = true;
		}
	}
	
	return flag;
}

//Adds symbol string to table
void enter(char*symbol){
	strcpy(symbolTable[tableIndex],symbol);
	tableIndex++;
	return;
}

void check_id(char*sym){
	//Uses lookup to see if ID exists
	//Uses enter and generate if it doesn't exist
	
	if(lookup(sym)){
		enter(sym);
		//generate();
	}
	
	return;
}

char*getTemp(){
	char t[25];
	char tempID[25];
	char i[2];
	strcat(t,"Temp");
	snprintf(i, 2, "%d", tempNum);
	strcat(t,i);
	if(lookup(t)){
		tempNum++;
		snprintf(i, 2, "%d", tempNum);
		strcat(t,i);
	}
	else{
		snprintf(i, 2, "%d", tempNum);
		strcat(t,i);
	}
	
	return tempID;
}

//Generates intermediate code string
//Recieves up to 5 strings and writes to temp with ';'
void generate(char*strA){
	
	return;
}

void startAct(){
	//write descriptive heading to list and output files
	//init code_gen variables
	tempNum = 0;
	tableIndex = 0;
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	fprintf(out_file,"//Current Date:\n//%d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fprintf(out_file,"#include <stdio.h>\nint main()\n{\n");
	return;
}

void finishAct(){
	//write descriptive closing to list and output files
	//concatenate the two parts of C code
	
	return;
}

void assignAct(expr_recStr left,expr_recStr right){
	char phrase[50];
	//Use 'left' = operator and 'right' to create C
	//ie. assign(target,source) Makes "X = Temp1;"
	strcat(phrase,left.expression);
	strcat(phrase,"=");
	strcat(phrase,right.expression);
	strcat(phrase,";\n");
	
	fputs(phrase,temp_file);
	
	return;	
}

void read_idAct(expr_recStr temp){
	char phrase[50];
	//Generate scanf statement
	//i.e. "scanf("%d",&x);"
	
	strcat(phrase,"scanf(""%d"",&");
	strcat(phrase,temp.expression);
	strcat(phrase,");\n");
	fputs(phrase,temp_file);
	
	return;
}

void write_exprAct(expr_recStr temp){
	char phrase[50];
	//Generate scanf statement
	//Depends on exprType
	//i.e. "printf("%d\n",x);"
	
	strcat(phrase,"printf(""%d\n"",");
	strcat(phrase,temp.expression);
	strcat(phrase,");\n");
	fputs(phrase,temp_file);
	
	
	return;
}

expr_recStr gen_infixAct(expr_recStr left,op_recStr op,expr_recStr right){
	expr_recStr temp;
	char buffer[50];
	
	//set expr_rec temp to enum TEMPEXPR
	temp.type = 2;
	//set temp string to new temp ID by using getTemp()
	strcat(temp.expression,getTemp());
	snprintf(buffer, 50,"= %s %s %s",left.expression,op.operation,right.expression);
	strcat(temp.expression,buffer);
	//Assign to temp: 'left' operation 'right'
	
	return temp;
}

expr_recStr process_literalAct(){
	expr_recStr litEXPR;
	
	//set new expr_rec to enum LITERAL EXPR
	litEXPR.type = 1;
	//set string to token buffer (which is a number)
	strcat(litEXPR.expression,tkPtr);
	
	return litEXPR;
}

expr_recStr process_idAct(){
	expr_recStr idEXPR;
	
	//set new expr_rec to enum ID EXPR
	idEXPR.type = 0;
	//set string to token buffer (which is an ID)
	strcat(idEXPR.expression,tkPtr);
	
	return idEXPR;
}

op_recStr process_opAct(){
	op_recStr op;
	//set new op_rec to operation type
	strcat(op.operation,tkPtr);
	
	return op;
}
