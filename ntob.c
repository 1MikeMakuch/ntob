/* N to Base. Convert a number from one base to another
 * Makuch 1995
 * 2010/06/29 added arbitrary input bases
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <math.h>
#include <getopt.h>

extern char * optarg;
extern int optind, opterr, optopt;

char basevals[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char ibasevals[] = {
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  
	 2,  3,  4,  5,  6,  7,  8,  9,  0,  0, 
	 0,  0,  0,  0,  0, 10, 11, 12, 13, 14, 
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 
	35,  0,  0,  0,  0,  0,  0, 10, 11, 12, 
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 
	33, 34, 35,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0
};

void reverse(char * s) {
	int i,j;
	char c;
	for(i = 0, j=strlen(s)-1 ; i < j ; i++,j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}   
}
long long myatoi(long long ibase, char s[]) {
	long long i,n,sign;
	i=0;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for(n=0 ; s[i] ; i++)
		n = ibase * n + ibasevals[s[i]];
	return sign * n;
}

void my2bin(long long n, char s[]) {
	int i;
	for(i=0 ; i < sizeof(n) * 8 ; i++) {
		if (n & 1)
			s[i]='1';
		else
			s[i]='0';
		n = n >> 1;
	}
	s[i]=0;
	reverse(s);
}
void myitoa(long long base, long long n, char s[]) {
	long long i, sign;

	long long max;
	max = exp2((sizeof(long long) * 8) - 1);
	max = - max;
	if (n == max) {
		printf("xxx\n");
		return;
	}
	if (base > 2) {

		if ((sign = n) < 0) {
			n = -n;
		}

		i=0;
		long long mod,offset;
		do {
			mod = n % base;
			s[i++] = basevals[mod];
		} while ((n /= base) > 0);
		if (sign < 0)
			s[i++] = '-';
		s[i] = '\0';
		reverse(s);
	} else {
		my2bin(n,s);
	}
}

void usage(char * p) {
	printf("usage: %s -o <output base> -n <input value> [-i <input base>] [-1|-2] [-h]\n",p);
}
void help(char *p) {
	printf("ntob, version 1.01\n\n");
	usage(p);
	
static char * helpmsg =
"\nN to Base: Convert a number from one base to another. Bases can be anything from 2 to 36.\n"
"Input base defaults to 10. Bases beyond 16 use the alphabet as you'd expect.\n\n"
"-1 or -2 calculate 1s or 2s complement\n"
"\n"
"Examples:\n"
"\n"
"$ ntob -o 2 -n 10             # convert 10 to binary\n"
"1010\n"
"\n"
"$ ntob -o 10 -n 1010 -i 2     # and back\n"
"10\n"
"\n"
"$ ntob -o 8 -n 10             # convert 10 to octal\n"
"12\n"
"\n"
"$ ntob -o 16 -n 10            # base 16 A is equal to decimal 10\n"
"A\n"
"\n"
"$ ntob -o 36 -n 35            # base 36 Z is equal to decimal 35\n"
"Z\n"
"\n"
"$ ntob -o 36 -n  1767707668033969\n"
"HELLOWORLD\n";


	printf("%s",helpmsg);
}
int
main(int argc, char* argv[]) {

	long long base,ibase,n;
	base = ibase = n = 0;
	char c;
	char ival[100];
	ibase = 10;
	int do1s,do2s;
	do1s=do2s=0;
	while ((c = getopt(argc,argv,"ho:n:i:12")) != -1) {
		switch(c) {
			case 'o':
				base = atoi(optarg);
				break;
			case 'n':
				strcpy(ival,optarg);
				break;
			case 'i':
				ibase = atoi(optarg);
				break;
			case '1':
				do1s=1;
				break;
			case '2':
				do2s=1;
				break;
			case 'h':
				help(argv[0]);
				exit(0);
				break;
			default:
				usage(argv[0]);
				exit(0);
				break;
		}
	}
	if (argc < 5) {
		usage(argv[0]);
		exit(0);
	}
	if (base < 2 || base > 36) {
		usage(argv[0]);
		printf("base [%lld] out of range\n",base);
		exit(0);
	}
	if (ibase < 1 || ibase > 36) {
		usage(argv[0]);
		printf("inputbase [%lld] out of range\n", ibase);
		exit(0);
	}
	n = myatoi(ibase, ival);
	if (do1s)
		n = ~n;
	if (do2s)
		n = (~n) + 1;

	char buf[100];
	memset(buf,0,100);
	myitoa(base, n,buf);
	char * p = buf;
	while(*p == '0') ++p;
	printf("%s\n", p);


	return 0;

}
