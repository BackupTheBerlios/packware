/*
 * getsfmirror 0.2 - Get best dl.sourceforge.net mirror
 * Copyright (c) 2003 Jaroslaw Swierczynski <swiergot@intersec.pl>
 * Distributed under the terms of GNU GPL version 2 or any later version.
 */

#include <netdb.h> 
#include <stdio.h>

#define DLSFNET		"dl.sourceforge.net"

#define ALERON		0xe5039dcc /* 204.157.3.22	*/
#define BELNET		0x61c6bec1 /* 193.190.198.97	*/
#define CESNET		0x58a171c3 /* 195.113.161.88	*/
#define EASYNEWS	0x1e66638c /* 140.99.102.30	*/
#define FLOW		0xae5f81ca /* 202.129.95.174	*/
#define HEANET		0x57db01c1 /* 193.1.219.87	*/
#define KEIHANNA	0x044092d2 /* 210.146.64.4	*/
#define OPTUSNET	0x11018ec6 /* 198.142.1.17	*/
#define OVH		0x5b21bad5 /* 213.186.33.91	*/
#define PUZZLE		0xdd658dc3 /* 195.141.101.221	*/
#define TWTELECOM	0x0c04facf /* 207.250.4.12	*/
#define UMN		0x82506580 /* 128.101.80.130	*/
#define UNC		0x79d20298 /* 152.2.210.121	*/
#define VOXEL		0x02a40945 /* 69.9.164.2	*/

inline const char *a2s(const unsigned long int a)
{
	switch (a)
	{
		case ALERON:
			return "aleron";
		case BELNET:
			return "belnet";
		case CESNET:
			return "cesnet";
		case EASYNEWS:
			return "easynews";
		case FLOW:
			return "flow";
		case HEANET:
			return "heanet";
		case KEIHANNA:
			return "keihanna";
		case OPTUSNET:
			return "optusnet";
		case OVH:
			return "ovh";
		case PUZZLE:
			return "puzzle";
		case TWTELECOM:
			return "twtelecom";
		case UMN:
			return "umn";
		case VOXEL:
			return "voxel";
		case UNC:
		default:
			return "unc";
	}
}

int main()
{
	extern int h_errno;
	struct hostent *hostptr;
	struct in_addr *ptr;

	hostptr = gethostbyname(DLSFNET);
	if (!hostptr)
	{
		switch (h_errno)
		{
			case HOST_NOT_FOUND:
				fprintf(stderr, "Host not found\n");
				break;
			case TRY_AGAIN:
				fprintf(stderr, "Try again\n");
				break;
			case NO_RECOVERY:
				fprintf(stderr, "No recovery\n");
				break;
			case NO_ADDRESS:
				fprintf(stderr, "No address\n");
				break;
			default:
				fprintf(stderr, "Unknown error %d\n", h_errno);
				break;
		}
		return 1;
	}

	switch (hostptr->h_addrtype)
	{
		case AF_INET:
			ptr = (struct in_addr *) *hostptr->h_addr_list;
			printf ("%s\n", a2s(ptr->s_addr));
			break;
		default:
			fprintf(stderr, "Unknown address type %d\n", hostptr->h_addrtype);
			return 2;
	}

	return 0;
}
