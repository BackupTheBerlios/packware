/*
 * desc - format text in style of slack-desc files
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <stdio.h>
#include <string.h>

#define DESC "0.1"

#define LINEL 70
#define BUFL 80
#define LINES 9

int main(int argc, char *argv[])
{
	char buf[BUFL];
	char word[LINEL];
	int s, n, i, l, w, f, e;
	size_t r;

	if (argc < 2)
	{
		fprintf(stderr, "desc %s: usage: %s package\n", DESC, argv[0]);
		return 1;
	}

	s = sizeof(*buf);
	n = sizeof(buf);
	l = w = e = 0;
	f = 1;

	while ((r = fread(buf, s, n, stdin)))
		for (i = 0; i < r; ++i)
		{
			if (buf[i] == '\n')
			{
				word[w] = '\0';
				if (l + 1 + w > LINEL)
					printf("\n%s: %s\n", argv[1], word);
				else
					if (f)
						printf("%s: ", argv[1]);
					else
						fputc(' ', stdout);
					printf("%s\n", word);
				l = w = 0;
				f = 1;
				e += 1;
				continue;
			}
			if (buf[i] == ' ')
			{
				word[w] = '\0';
				if (l + 1 + w > LINEL)
				{
					printf("\n%s: %s", argv[1], word);
					l = w;
					e += 1;
				}
				else
				{
					if (f)
						printf("%s: ", argv[1]);
					else
						fputc(' ', stdout);
					printf ("%s", word);
					l += 1 + w;
				}
				w = f = 0;
				continue;
			}
			word[w++] = buf[i];
		}
	for (i = e; i < LINES; ++i)
		printf("%s:\n", argv[1]);

	return 0;
}
