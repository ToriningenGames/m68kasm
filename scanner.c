#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "defines.h"


static FILE *input = NULL;
static int nextchar = -1;

static int peek()
{
	if (!input) {
		return EOF;
	}
	if (nextchar == -1) {
		nextchar = getc(input);
	}
	return nextchar;
}

static int take()
{
	int thischar = peek();	//buffer will always fill before taking or seeing any character by any function
	nextchar = -1;
	return thischar;
}

//Take out whitespace and comments
void stripWhitespace()
{
	while (true) {
		if (isblank(peek())) {
			while (isblank(peek())) {
				take();
			}
		} else if (peek() == ';') {
			while (peek() != '\n') {
				take();
			}
		} else {
			return;
		}
	}
}

//Parses a number in a given base
//Relies on [0-9A-Z] being contiguous
static int parsenum(int base)
{
	int result = 0;
	while (toupper(peek()) - '0' < base && toupper(peek()) - '0' > 0) {
		result *= base;
		result += toupper(take()) - '0';
	}
	return result;
{

//Ready the lexer
void lex_init(char *infile)
{
	if (input) {
		fclose(input);
	}
	input = fopen(infile);
	peek();		//fill character buffer initially
	stripWhitespace();	//Remove leading blanks
}

//obtain alphanumeric string, which may be
	//a label
	//an opcode
	//a predefined constant
char *lex_getLabel()
{
	if (!isalnum(peek()) {
		return null;
	}
	char *label = malloc(MAX_LABEL_LEN + 1);
	int i = 0;
	while (isalnum(peek()) && i < MAX_LABEL_LEN) {
		label[i++] = toupper(take());		//all of these are case insensitive
	}
	label[i] = '\0';	//terminator
	//absorb extra characters
	while (isalnum(peek()))
		;
	stripWhitespace();
	return label;
}

//obtain string constant
char *lex_getString()
{
	if (peek() != '"' && peek() != '\'') {
		return null;
	}
	char endquote = take();
	char *string = malloc(MAX_STRING_LEN + 1);
	int i = 0;
	for (; i < MAX_STRING_LEN && peek() != endquote; i++) {
		if (peek() == '\\') {	//escape character
			i++;
			switch (peek()) {
			case '"' :
			case '\'' :
			case '\\' :
				break;	//copy the character literally
			case 'n' :
				take();
				string[i] = '\n';
				continue;	//next iteration
			case '0' :
				take();
				string[i] = '\0';
				continue;	//next iteration
			case 'o' :
			case 'O' :
				take();
				string[i] = parsenum(8);	//parse octal number
				if (peek() == '\\') {	//trailing demarcation?
					take();
				}
				continue;	//next iteration
			case 'x' :
			case 'X' :
				take();
				string[i] = parsenum(16);	//parse hexadecimal number
				if (peek() == '\\') {	//trailing demarcation?
					take();
				}
				continue;	//next iteration
			case 'b' :
			case 'B' :
				take();
				string[i] = parsenum(2);	//parse binary number
				if (peek() == '\\') {	//trailing demarcation?
					take();
				}
				continue;	//next iteration
			case 'd' :
			case 'D' :
				take();
				string[i] = parsenum(10);	//parse decimal number
				if (peek() == '\\') {	//trailing demarcation?
					take();
				}
				continue;	//next iteration
		}
		string[i] = take();
	}
	stripWhitespace();
	return "";
}

//obtain directives (assembler commands, prepended with a '.')
char *lex_getDirective()
{
	if (peek() != '.') {
		return NULL;
	}
	take();	//a dot
	return getLabel();
}

static int parseNumber()
{
	switch (peek()) {
	case '$' :	//hexadecimal
		take();
		return parsenum(16);
	case '%' :	//binary
		take();
		return parsenum(2);
	case '0' :	//options
		take();
		if (peek() == ' ') {	//octal
			take();
			return parsenum(8);
		}
		if (isnum(peek())) {	//octal
			return parsenum(8);
		}
	default :	//decimal
		return parsenum(10);
	case '\\' :
		take();
		switch (peek()) {
		case 'o' :
		case 'O' :	//octal
			take();
			return parsenum(8); 
		case 'x' :
		case 'X' :	//hexadecimal
			take();
			return parsenum(16); 
		case 'b' :
		case 'B' :	//binary
			take();
			return parsenum(2); 
		case 'd' :
		case 'D' :	//decimal
		default :	//decimal? 
			take();
			return parsenum(10);
		}
	}
}

//obtain numbers
int lex_getNumber()
{
	int retval = parseNumber();
	stripWhitespace();
	return retval;
}

