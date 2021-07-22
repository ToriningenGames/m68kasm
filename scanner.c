#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"


static FILE *input = NULL;
static int nextchar = -1;

int peek()
{
	if (!input) {
		return EOF;
	}
	if (nextchar == -1) {
		nextchar = getc(input);
	}
	return nextchar;
}

int take()
{
	int thischar = peek();	//buffer will always fill before taking or seeing any character by any function
	nextchar = -1;
	return thischar;
}

void init(char *infile)
{
	if (input) {
		fclose(input);
	}
	input = fopen(infile);
	peek();		//fill character buffer initially
}

//obtain alphanumeric string, which may be
	//a label
	//an opcode
	//a defined constant
char *getString()
{
	char *label = malloc(MAX_LABEL_LEN + 1);
	int i = 0;
	while (isalnum(peek()) && i < MAX_LABEL_LEN) {
		label[i++] = take();
	}
	label[i] = '\0';	//terminator
	//absorb extra characters
	while (isalnum(peek()))
		;
	return label;
}

