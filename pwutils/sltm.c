/*
 * sltm - convert symbolic link to manual page reference
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

#define SLTM "0.1"

#define BUFL 80

#define free_all() free(tmp1); free(tmp2); free(tmp4);

int main(int argc, char *argv[])
{
	char target[BUFL];
	char *tmp1, *tmp2, *tmp3, *tmp4, *tmp5, *page, *sect;
	int len;

	if (argc < 2)
	{
		fprintf(stderr, "sltm %s: usage: %s symlink\n", SLTM, argv[0]);
		return 1;
	}

	len = readlink(argv[1], target, BUFL);
	if (len == -1)
	{
		perror("sltm");
		return 2;
	}
	target[len] = '\0';

	tmp1 = strdup(target);
	page = basename(tmp1);
	tmp2 = strdup(target);
	tmp3 = dirname(tmp2);
	if (strcmp(tmp3, "."))
	{
		tmp4 = strdup(tmp3);
		sect = basename(tmp4);
	}
	else
	{
		tmp5 = strdup(argv[1]);
		tmp3 = dirname(tmp5);
		tmp4 = strdup(tmp3);
		sect = basename(tmp4);
		free(tmp5);
	}

	if (!unlink(argv[1]))
	{
		FILE *f;

		f = fopen(argv[1], "w");
		if (!f)
		{
			perror("sltm");
			free_all();
			return 3;
		}
		fprintf(f, ".so %s/%s\n", sect, page);
		fclose(f);
	}
	else
	{
		perror("sltm");
		free_all();
		return 4;
	}
	free_all();

	return 0;

}
