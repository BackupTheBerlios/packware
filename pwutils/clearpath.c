/*
 * clearpath - clear path from doubled slashes
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEARPATH "0.1"

int main(int argc, char *argv[])
{
	int i = 0, j = 0, c, slash = 0;
	char *path, *temp;

	if (argc != 2)
	{
		fprintf(stderr, "clearpath %s: usage: %s path\n", CLEARPATH, argv[0]);
		return 1;
	}

	path = (char *) malloc(strlen (argv[1]) + 1);
	strcpy(path, argv[1]);
	temp = (char *) malloc(strlen (path) + 1);
	strcpy(temp, path);

	while ((c = path[i++]) != '\0')
	{
		if (c == '/')
		{
			if (slash)
				continue;
			else
				slash = 1;
		}
		else
			slash = 0;
		temp[j++] = c;
	}
	if (temp[j - 1] == '/' && j - 1 > 0)
		temp[j - 1] = '\0';
	else
		temp[j] = '\0';
	printf("%s\n", temp);
	free(path);
	free(temp);

	return 0;

}
