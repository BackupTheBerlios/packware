/*
 * sltd - convert symbolic link to Slackware's doinst.sh script entry
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

#define SLTD "0.1"

#define BUFL 80

int main(int argc, char *argv[])
{
	char target[BUFL];
	char *lname, *dprep, *bprep, *dname, *bname;
	int len;

	if (argc < 2)
	{
		fprintf(stderr, "sltd %s: usage: %s symlink\n", SLTD, argv[0]);
		return 1;
	}

	if (strncmp(argv[1], "./", 2))
		lname = strdup(argv[1]);
	else
		lname = strdup(argv[1] + 2);
	len = readlink(lname, target, BUFL);
	if (len == -1)
	{
		perror("sltd");
		return 2;
	}
	target[len] = '\0';

	dprep = strdup(lname);
	bprep = strdup(lname);
	dname = dirname(dprep);
	bname = basename(bprep);
	printf("( cd %s ; rm -rf %s )\n", dname, bname);
	printf("( cd %s ; ln -sf %s %s )\n", dname, target, bname);

	free(dprep);
	free(bprep);
	free(lname);

	return 0;
}
