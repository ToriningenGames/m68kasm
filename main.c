#include <stdio.h>
#include "parse.h"


int main(int argc, char **argv)
{
	if (argc != 3) {
		printf(	"Incompatible Motorola 68000 Assembler\n"
			"Usage:\n"
			"\t m68kasm infile.asm outfile.o\n");
		return 1;
	};
	FILE *infile = fopen(argv[1], "r");
	FILE *outfile = fopen(argv[2], "wb");
	return 0;
}

