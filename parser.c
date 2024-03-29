#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include <stdbool.h>	//for boolean
#include "file_util.h"	//include file_util header
#include "parser.h"	//include parser header
#include "scanner.h" //For token type

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
	listT = true;
	nxtTk = next_token();
	listT = false;
	fputs(listBuffer,list_file); //Add buffer to listing file
	clear_buffer(listBuffer);
	if(nxtTk == token){
		while(tokenBuffer[i] != '\0'){
			add_char(tokBuf,tokenBuffer[i],stateBufP);
			i++;
			stateBufP++;
		}
		fsetpos(in_file, &posA);
		printf("\nEXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",tkList[token],tkPtr);
		fprintf(out_file,"EXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",tkList[token],tkPtr);
		return true;
	}
	else{
		//Syntax error
		while(tokenBuffer[i] != '\0'){
			add_char(tokBuf,tokenBuffer[i],stateBufP);
			i++;
			stateBufP++;
		}
		errFound = true;
		snprintf(errorTemp, ERRTMP,"\nSyntax Error at line %d: Token %s is false, expected %s\n",listNum,tkPtr,tkList[token]);
		strcat(errorBuffer,errorTemp);
		clear_buffer(errorTemp);
		fsetpos(in_file, &posA);
		printf("\nEXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",tkList[token],tkPtr);
		fprintf(out_file,"EXPECTED TOKEN:   %s   ACTUAL TOKEN:   %s\n",tkList[token],tkPtr);
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
	finishAct();
	
	return 0;
}

//Production 1
int program_rule(){
	startAct();
	if(!match(BEGIN,statePtr)){
		lexErr++;
	}
	else{
		fprintf(out_file,"\nCurrent statement: %s \n", statePtr);
		stateBufP = 0;
		clear_buffer(statePtr);
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
	expr_recStr target = {};
	expr_recStr source = {};

	printf("\nRunning statement production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 3
		case 10:
			printf("\nRunning statement production rule 3\n");
			target = ident();
			if(!match(ASSIGNOP,statePtr)){
				lexErr++;
			}		
			expression(&source);	
			//expression();
			if(!match(SEMICOLON,statePtr)){
				lexErr++;
			}
			assignAct(target,source);
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
			//printf("\nRunning statement production rule 5\n");
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
			//printf("\nRunning statement production rule 6\n");
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
			//printf("\nRunning statement production rule 8\n");
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
	//printf("\nRunning if_tail production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 7
		case ELSE:
			//printf("\nRunning if_tail production rule 7\n");
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
			//printf("\nRunning if_tail production rule 8\n");
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
	expr_recStr id = {};
	printf("\nRunning id_list production\n");
	id = ident();
	read_idAct(id);
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
	expr_recStr id = {};
	printf("\nRunning expr_list production\n");
	expression(&id);
	write_exprAct(id);
	printf("\n EXPRLIST: %s \n",id.expression);
	//expression();
	repeat = next_token(tkPtr);
	while(repeat==COMMA){
		if(!match(COMMA,statePtr)){
			lexErr++;
		}
		expr_list();
		write_exprAct(id);
	
		repeat = next_token(tkPtr);
	}
	return 0;
}

//Production 12
void expression(expr_recStr *record){
//int expression(){
	enum token repeat;
	expr_recStr left = {};
	expr_recStr right = {};
	op_recStr op = {};
	
	printf("\nRunning expression production\n");
	term(&left);
	//term();
	repeat = next_token(tkPtr);
	while(repeat==PLUSOP || repeat==MINUSOP){
		//add_op();
		add_op(&op);
		term(&right);
		printf("\n EXPRESSION: %s %s %s\n",left.expression,op.operation,right.expression);
		fprintf(temp_file,"%s %s %s\n",left.expression,op.operation,right.expression);
		left = gen_infixAct(left,op,right);
		puts(left.expression);
		record = &left;
		//term();
		repeat = next_token(tkPtr);
	}
	return;
}

//Production 13
void term(expr_recStr*operand){
//int term(){
	enum token repeat;
	expr_recStr left;
	expr_recStr right;
	op_recStr op = {};
	printf("\nRunning term production\n");
	factor(&left);
	//factor();
	repeat = next_token(tkPtr);
	while(repeat==MULTOP || repeat==DIVOP){
		//mult_op();
		mult_op(&op);
		factor(&right);
		left = gen_infixAct(left,op,right);
		//factor();
		repeat = next_token(tkPtr);
	}
	printf("\n TERM: %s %s\n",left.expression,right.expression);
	*operand = left;
	return;
}

void factor(expr_recStr *operand){
//int factor(){
	enum token nxtTk;
	expr_recStr temp = {};
	printf("\nRunning factor production\n");
	nxtTk = next_token(tkPtr);
	switch(nxtTk){
		//Production 14
		case LPAREN:
			printf("\nRunning factor production rule 14\n");
			
			if(!match(LPAREN,statePtr)){
				lexErr++;
			}
			//expression();
			expression(&temp);
			*operand = temp;
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
			//factor();
			factor(&temp);
			//Add '-' to temp
			strcat(temp.expression,"-");
			*operand = temp;
			break;
		//Production 16
		case ID:
			printf("\nRunning factor production rule 16\n");
			//ident();
			*operand = ident();
			break;
		//Production 17
		case INTLITERAL:
			printf("\nRunning factor production rule 17\n");
			if(!match(INTLITERAL,statePtr)){
				lexErr++;
			}
			else{
				*operand = process_literalAct();
			}
			break;
	}
	return;	
}

void add_op(op_recStr *op){
//int add_op(){
	enum token nxtTk;
	//printf("\nRunning add_op production\n");
	nxtTk = next_token(tkPtr);
	switch(nxtTk){
		//Production 18
		case PLUSOP:
			printf("\nRunning add_op production rule 18\n");
			if(!match(PLUSOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
				printf("\n PLUS OP: %s \n",op);
			}
			break;
		//Production 19
		case MINUSOP:
			printf("\nRunning add_op production rule 19\n");
			if(!match(MINUSOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
	}
	return 0;
}

void mult_op(op_recStr *op){
//int mult_op(){
	enum token nxtTk;
	//printf("\nRunning mult_op production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 20
		case MULTOP:
			//printf("\nRunning mult_op production rule 20\n");
			if(!match(MULTOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
		//Production 21
		case DIVOP:
			//printf("\nRunning mult_op production rule 21\n");
			if(!match(DIVOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
	}
	return 0;
}

//Production 22
expr_recStr condition(){
//int condition(){
	enum token repeat;
	expr_recStr left = {};
	expr_recStr right = {};
	op_recStr op = {};
	printf("\nRunning condition production\n");
	addition(&left);
	//addition();
	repeat = next_token(tkPtr);
	while(repeat==LESSOP || repeat==LESSEQUALOP || repeat==GREATEROP || repeat==GREATEREQUALOP || repeat==NOTEQUALOP || repeat==EQUALOP){
		rel_op(&op);
		addition(&right);
		left = gen_infixAct(left,op,right);
		//rel_op();
		//addition();
		repeat = next_token(tkPtr);
	}
	return left;
	//return 0;
}

//Production 23
void addition(expr_recStr *operand){
//int addition(){
	enum token repeat;
	expr_recStr left = {};
	expr_recStr right = {};
	op_recStr op = {};
	//printf("\nRunning addition production\n");
	multiplication(right);
	//multiplication();
	repeat = next_token(tkPtr);
	while(repeat==PLUSOP || repeat==MINUSOP){
		add_op(&op);
		multiplication(left);
		left = gen_infixAct(left,op,right);
		//add_op();
		//multiplication();
		repeat = next_token(tkPtr);
	}
	*operand = left;
	return;
}

//Production 24
void multiplication(expr_recStr operand){
//int multiplication(){
	enum token repeat;
	expr_recStr left = {};
	expr_recStr right = {};
	op_recStr op = {};
	//printf("\nRunning multiplication production\n");
	unary(&left);
	repeat = next_token(tkPtr);
	while(repeat==MULTOP || repeat==DIVOP){
		mult_op(&op);
		unary(&right);
		left = gen_infixAct(left,op,right);
		repeat = next_token(tkPtr);
	}
	operand = left;
	return;
}

void unary(expr_recStr *operand){
//int unary(){
	enum token nxtTk;
	expr_recStr temp = {};
	//printf("\nRunning unary production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 25
		case NOTOP:
			if(!match(NOTOP,statePtr)){
				lexErr++;
			}
			strcat(temp.expression,"!");
			unary(&temp);
			//Add '!' to record
			*operand = temp;
			//unary();
			break;
		//Production 26
		case MINUSOP:
			if(!match(MINUSOP,statePtr)){
				lexErr++;
			}
			strcat(temp.expression,"-");
			unary(&temp);
			//Add '-' to record
			*operand = temp;
			//unary();
			break;
		//Production 27
		case INTLITERAL:
			lprimary(&operand);
			break;
		case ID:
			lprimary(&operand);
			break;
		case LPAREN:
			lprimary(&operand);
			break;
		case FALSEOP:
			lprimary(&operand);
			break;
		case TRUEOP:
			lprimary(&operand);
			break;
		case NULLOP:
			lprimary(&operand);
			break;
	}
	return 0;
}

void lprimary(expr_recStr *operand){
//int lprimary(){
	enum token nxtTk;
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 28
		case INTLITERAL:
			if(!match(INTLITERAL,statePtr)){
				lexErr++;
			}
			*operand = process_literalAct();
			break;
		//Production 29
		case ID:
			*operand = ident();
			break;
		//Production 30
		case LPAREN:
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
			if(!match(FALSEOP,statePtr)){
				lexErr++;
			}
			*operand = process_literalAct();
			break;
		//Production 32
		case TRUEOP:
			if(!match(TRUEOP,statePtr)){
				lexErr++;
			}
			*operand = process_literalAct();
			break;
		//Production 33
		case NULLOP:
			if(!match(NULLOP,statePtr)){
				lexErr++;
			}
			*operand = process_literalAct();
			break;
	}
	return operand;
}

void rel_op(op_recStr *op){
//int rel_op(){
	enum token nxtTk;
	//printf("\nRunning rel_op production\n");
	nxtTk = next_token(tkPtr);
	
	switch(nxtTk){
		//Production 34
		case LESSOP:
			//printf("\nRunning rel_op production rule 34\n");
			if(!match(LESSOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
		//Production 35
		case LESSEQUALOP:
			//printf("\nRunning rel_op production rule 35\n");
			if(!match(LESSEQUALOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
		//Production 36
		case GREATEROP:
			//printf("\nRunning rel_op production rule 36\n");
			if(!match(GREATEROP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
		//Production 37
		case GREATEREQUALOP:
			//printf("\nRunning rel_op production rule 37\n");
			if(!match(GREATEREQUALOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
		//Production 38
		case EQUALOP:
			//printf("\nRunning rel_op production rule 38\n");
			if(!match(EQUALOP,statePtr)){
				lexErr++;
			}
			*op = process_opAct();
			break;
		//Production 39
		case NOTEQUALOP:
			//printf("\nRunning rel_op production rule 39\n");
			if(!match(LESSOP,statePtr)){
				lexErr++;
			}
			else{
				*op = process_opAct();
			}
			break;
	}
	return 0;
}

expr_recStr ident(){
	expr_recStr temp;
	if(!match(ID,statePtr))
	{
		lexErr++;
	}
	else{
		temp = process_idAct();
	}
	
	return temp;
}
