/*
 * spn - Slackware package name resolver
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

#define SPN "0.1"

#define C_NAM 0
#define C_VER 1
#define C_ARC 2
#define C_BLD 3

#define spn_exit(n) { free(raw); return n; }

int main(int argc, char *argv[])
{
	char *exec, *prog, *raw, *tab[4];
	int compon = -1, len;

	if (argc < 2)
	{
		fprintf(stderr, "spn %s: usage: %s name\n", SPN, argv[0]);
		return 1;
	}

	exec = strdup(argv[0]);
	prog = basename(exec);

	if (!strcmp(prog, "spn-name" )) compon = C_NAM; else
	if (!strcmp(prog, "spn-ver"  )) compon = C_VER; else
	if (!strcmp(prog, "spn-arch" )) compon = C_ARC; else
	if (!strcmp(prog, "spn-build")) compon = C_BLD;

	raw = strdup(argv[1]);
	tab[C_NAM] = basename(raw);
	len = strlen(tab[C_NAM]);

	if (len > 3 && !strcmp(tab[C_NAM] + len - 4, ".tgz"))
		(tab[C_NAM])[len -= 4] = 0;
	if (len == 0)
		spn_exit(2);

	if ((tab[C_BLD] = strrchr(tab[C_NAM], '-'))) *(tab[C_BLD]++) = 0;
	if ((tab[C_ARC] = strrchr(tab[C_NAM], '-'))) *(tab[C_ARC]++) = 0;
	if ((tab[C_VER] = strrchr(tab[C_NAM], '-'))) *(tab[C_VER]++) = 0;

	if (!(tab[C_VER] && tab[C_ARC] && tab[C_BLD]))
	{
		if (tab[C_VER]) *(tab[C_VER] - 1) = '-';
		if (tab[C_ARC]) *(tab[C_ARC] - 1) = '-';
		if (tab[C_BLD]) *(tab[C_BLD] - 1) = '-';

		if (compon == -1)
			printf("p_name=\"%s\"; p_ver=\"\"; p_arch=\"\"; p_build=\"\";\n", tab[C_NAM]);
		else
			if (compon == 0)
				printf("%s\n", tab[C_NAM]);
		spn_exit(0);
	}

	if (compon == -1)
		printf("p_name=\"%s\"; p_ver=\"%s\"; p_arch=\"%s\"; p_build=\"%s\";\n", tab[C_NAM], tab[C_VER], tab[C_ARC], tab[C_BLD]);
	else
		printf("%s\n", tab[compon]);

	spn_exit(0);
}
