#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define BUFSIZE 256

const char flag_array[] = {0xd6, 0xf4, 0xfe, 0xd0, 0xca, 0xc4, 0x30, 0x30, 0xa2, 0xb8, 0x9e, 0xb0, 0xa6, 0x90, 0x96, 0x90, 0xa6, 0xb0, 0x9e, 0xb8, 0xea, 0x90, 0x3c, 0xdb, 0xc3, 0xe7, 0x22, 0xe8, 0xd2, 0x21, 0x9f, 0xc5, 0x21, 0x9f, 0xe4, 0xd1, 0xe8, 0xf5, 0xd8, 0xdd, 0xd8, 0xf5, 0xe8, 0xd1, 0xe4, 0xf9};
const int SIZE = 46;

int attempt = 1;

void verification()
{
	char selection[BUFSIZE];

	printf(BLUE "\n[!] 🤖 You must pass this Human Verification Test to use the flag-checker!\n");
	printf("\n[!] ⏲️ Current number of available attempts: %d\n", attempt);
	printf("\n1. Earn an attempt");
	printf("\n2. Check flag\n");
	printf("> ");

	fgets(selection, BUFSIZE, stdin);

	if (atoi(selection) == 1)
	{
		guess();
	}
	else if (atoi(selection) == 2)
	{
		check();
	}
	else
	{
		printf(RED "\n[-] Error Encountered! Terminating...\n");
		exit(0);
	}
}

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

void guess()
{
	char input[BUFSIZE];
	char guess[BUFSIZE];
	int num = random_int(10000000, 99999999);

	printf(GREEN "\n[!] Guess a 8-digit secret number to pass the test!");
	printf("\n[!] However, one attempt will be deducted if you lose!");
	printf("\n[!] What will you do?\n");
	printf("\n1. Continue with the test");
	printf("\n2. Abort");
	printf("\n> ");

	fgets(input, BUFSIZE, stdin);

	if (atoi(input) == 1)
	{
		printf(GREEN "\n[!] Guess:\n");
		printf("> ");

		fgets(guess, BUFSIZE, stdin);

		if (atoi(guess) == num)
		{
			printf(GREEN "\n[+] ✔️ Correct Guess! You have earned yourself an attempt!\n");
			attempt++;
			verification();
		}
		else
		{
			printf(RED "\n[-] ❌ Terrible Guess! The correct answer was %d\n", num);
			attempt--;
			verification();
		}
	}
	else if (atoi(input) == 2)
	{
		printf(RED "\n[-] 🔙 Mission Abort! Returning...\n");
		verification();
	}
	else
	{
		printf(RED "\n[-] Error Encountered! Returning...\n");
		verification();
	}
}

bool encrypt(char flag[])
{
	bool match = true;
    char inputChar[BUFSIZE];
    char flagChar[BUFSIZE];
    
    char *inputPtr;
    inputPtr = flag;
    
    char input_array[] = {};
    
    for (int i = 0; i < SIZE; i++) {
        
        int charval = *(inputPtr+i);
        charval ^= 42;
        
        if (i < 23){
            input_array[i] = (charval << 3) >> 2;
        }
        else{
            input_array[i] = charval ^ (charval << 1);
        }

        sprintf(inputChar, "%d", input_array[i]);
    	sprintf(flagChar, "%d", flag_array[i]);

        if(atoi(inputChar) != atoi(flagChar)){
            match = false;
            break;
        }
    }

    return match;
}

void check()
{
	if (attempt > 0)
	{
		char input[BUFSIZE];

		printf(GREEN "\n[!] 🏳️ Enter Flag:\n");
		printf("> ");

		scanf("%[^\n]%*c", input);

		if (encrypt(input) == true)
		{
			printf(GREEN "\n[+] ✔️ Correct Flag!\n");
		}
		else
		{
			printf(RED "\n[-] ❌ Wrong Flag! Try again!\n");
			attempt--;
			verification();
		}
	}
	else
	{
		printf(RED "\n[-] ⛔ No attempts available! Verify yourself first!\n");
		exit(0);
	}
}

int main(int argc, char **argv)
{
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

	verification();
}