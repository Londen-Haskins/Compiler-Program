/*
	Group Member:
		Londen Haskins --- has4082@calu.edu
	Group Number: 5
	Language Translation
	CSC 460
	Program 3: Parser Program
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//to lookup files
#include <sys/stat.h>	//for the check file
#include "file_util.h"	//include header file
#include "scanner.h"	//include scannner header

char tokenBuffer[TKLEN];
char stateBuf[TKLEN];

int main(int argc, char *argv[]) 
{
	init(argc, argv);
	wrapUp();
}

