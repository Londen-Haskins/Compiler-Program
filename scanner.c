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

