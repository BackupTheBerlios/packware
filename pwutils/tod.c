/*
 * tod - convert Unix text file do DOS format
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>

#define TOD "0.2"

int main(int argc, char *argv[])
{
	FILE *f;
	int c;

	if (argc < 2)
	{
		fprintf(stderr, "tod %s: usage: %s unix-file\n", TOD, argv[0]);
		return 1;
	}

	if ((f = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "tod %s: cannot open file\n", TOD);
		return 2;
	}

	while ((c = fgetc(f)) != EOF)
	{
		if (c == 10)
			putchar(13);
		putchar(c);
	}

	fclose(f);

	return 0;
}
