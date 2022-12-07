#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define FLAGSIZE 128
#define BUFSIZE 64
  
void login()
{  
	char flag[FLAGSIZE];

	FILE *f = fopen("flag.txt", "r");
	if (f == NULL) {
		puts("'flag.txt' not found.");
		exit(0);
	}

	fgets(flag, FLAGSIZE,f );

	char buffer[BUFSIZE];

	printf(BLUE "\n[*] Repeat after me!\n");
	printf("> ");
	fgets(buffer, BUFSIZE, stdin);
	printf(GREEN "[+] Echo: ");
	printf(buffer);
}

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	gid_t gid = getegid();
	setresgid(gid, gid, gid);

	char buf[BUFSIZE];

	printf(GREEN "\n");
	printf("██████╗  █████╗ ████████╗████████╗██╗     ███████╗   \n");
	printf("██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝ \n");
	printf("██████╔╝███████║   ██║      ██║   ██║     █████╗ \n");
	printf("██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝   \n");
	printf("██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗ \n");
	printf("╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝  \n");
	printf("\n");
	printf(" ██████╗ ███████╗ \n");
	printf("██╔═══██╗██╔════╝ \n");
	printf("██║   ██║█████╗ \n");
	printf("██║   ██║██╔══╝ \n");
	printf("╚██████╔╝██║ \n");
	printf(" ╚═════╝ ╚═╝  \n");
	printf("\n");
	printf("██╗  ██╗ █████╗  ██████╗██╗  ██╗███████╗██████╗ ███████╗\n");
	printf("██║  ██║██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝\n");
	printf("███████║███████║██║     █████╔╝ █████╗  ██████╔╝███████╗\n");
	printf("██╔══██║██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║\n");
	printf("██║  ██║██║  ██║╚██████╗██║  ██╗███████╗██║  ██║███████║\n");
	printf("╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n");
	printf("\n");
	printf("██████╗  ██████╗ ██████╗ ██████╗ \n");
	printf("╚════██╗██╔═████╗╚════██╗╚════██╗ \n");
	printf(" █████╔╝██║██╔██║ █████╔╝ █████╔╝\n");
	printf("██╔═══╝ ████╔╝██║██╔═══╝ ██╔═══╝ \n");
	printf("███████╗╚██████╔╝███████╗███████╗ \n");
	printf("╚══════╝ ╚═════╝ ╚══════╝╚══════╝  \n");

	printf(BLUE "\n[!] Welcome contestant, what is your secret PIN?\n");
	printf("> ");
	gets(buf);
	printf(RED "\n[!] Wrong PIN Number!\n");
	printf("[-] Access Denied!\n");
}