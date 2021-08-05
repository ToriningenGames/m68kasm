#ifndef SCANNER_H
#define SCANNER_H

void lex_init(char *infile);
char *lex_getLabel();
char *lex_getString();
char *lex_getDirective();
int lex_getNumber();

#endif

