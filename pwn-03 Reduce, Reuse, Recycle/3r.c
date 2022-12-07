#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>

#define BLUE "\033[1;34m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"

struct metals {
	char name[8];
	char identifier[35];
};

struct tracker{
	struct tracker *next;
	struct metals *ptr;
	char name[8];
	long int id;
};

char * bronzeBuffer;
char * brassBuffer;
char * pewterBuffer;
char * steelBuffer;

struct metals *alloy;
struct metals *gold;

struct tracker *alloy_t;
struct tracker *gold_t;

char *metalName[8];
char *metalBuffer;
int uid=1000;
int length;
char salt[8] = "APUBOH22";
char *hash;

void registration(){

	char identifier_L[33];

	printf(GREEN"\n[!] Please create a Metal Profile:\n");
	printf("\n[*] Enter metal name (8 characters max)\n> ");
	scanf("%8s", metalName);

	// if(strcmp(metalName, "Gold") == 0)

	printf("\n[+] Metal %s added successfully!\n", metalName);
	printf("\n[*] Enter unique identifier for %s\n> ", metalName);
	scanf("%32s", &identifier_L);
	hash = crypt(identifier_L, salt);

	printf("\n[*] How long is the description for the metal profile? (200 characters max)?\n> ");
	scanf("%d", &length);

	metalBuffer = malloc(length + 8);
	printf(" \n[*] Space allocated! Please enter the description\n> ");
	getchar();
	fgets((metalBuffer + 8), 201, stdin);
}

void recycle(){

	fflush(stdin);
	getchar();

	struct tracker *ptr;
	char metalName_l[9];
	char identifier_l[32];
	char *hash;

	printf(GREEN "\n[*] Metal Name (Case-sensitive): ");
	scanf("%8s", metalName_l);

	for (ptr = gold_t; ptr != NULL; ptr = gold_t->next) {

        if (strcmp(ptr->name, metalName_l) == 0) {

            printf("\n[*] Unique Identifier: ");
            scanf("%32s", identifier_l);
            hash = crypt(identifier_l, salt);

            if (strcmp(hash, ptr->ptr->identifier) == 0){

                strcpy(metalName, ptr->name);
                uid = ptr->id;
                puts(GREEN "\n[+] ♻️ Metal Recycled!");
                menu();
            }
            else{
                puts(RED "\n[-] ❌ Incorrect Details!");
                recycle();
            }
        }
        else
        {
            if (ptr->next==0)
            {
                puts(RED "\n[-] ❌ No such Metal Profile found!");
                recycle();
            }
        }
    }
}

void bash(){

	if (uid == 0){
		system("bash");
	}
	else 
	{
		printf(RED "\n-] ⛔ Access Denied!\n");
		exit(0);
	}

}

void banner(){

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

	printf(BLUE "\n[!] ♻️ Reduce, Reuse, Recycle - Metal Recycling Station\n");

}

void menu(){

	printf(YELLOW "\n[!] ♻️ Reduce, Reuse, Recycle - Metal Recycling Station\n");
	printf("\n[!] Flag is awarded as Token of Appreciation for each [Gold] contribution!\n");
	printf("[!] As the pre-alpha system is for internal use only, every recycle process requires the unique identifier of metal to proceed.\n");
	printf("[!] Objective: Recycle a Gold metal via [1] then claim your reward using [2].\n\n");

	puts("+-------------------------------+");
	puts("|           Commands            |");
	puts("+-------------------------------+");
	puts("| 1. Recycle/Donate/Contribute  |");
	puts("| 2. Token of Appreciation      |");
	puts("| 3. Exit                       |");
	puts("+-------------------------------+");

	int option;

	printf("\n[*] Choice > ");
	scanf("%i", &option);

	switch(option){
		case 1:
			recycle();
		case 2:
			bash();
		case 3:
			exit(0);
		default:
			printf(RED "\n[-] ❌ Invalid Choice!\n");
			break;
	}
}

void history(){

	bronzeBuffer = malloc(0x40);

	char Bronze[0x40] = "Bronze\nComposition of Copper and Tin.\0";
	char Brass[0x50] ="Brass\nComposition of Copper and Zinc.\0";
	char Pewter[0x50] = "Pewter\nComposition of Tin, Antimony and Copper.\0";
	char Steel[0x60] = "Steel\nComposition of Iron and Carbon.\0";

	strcpy(bronzeBuffer, Bronze);

	brassBuffer = malloc(0x50);
	strcpy(brassBuffer, Brass);

	pewterBuffer = malloc(0x60);
	strcpy(pewterBuffer, Pewter);

	steelBuffer = malloc(0x80);
	strcpy(steelBuffer, Steel);

	free(brassBuffer);
	free(steelBuffer);
}

int main(){

	setvbuf(stdout, 0, 2, 0);
	setvbuf(stdin, 0, 2, 0);

	alloy_t = malloc(sizeof(struct tracker));
	gold_t = malloc(sizeof(struct tracker));

	history();
	banner();

	alloy = malloc(sizeof(struct metals )* 4);
	gold = alloy + 1;

	strcpy(alloy->name,"Tin");
	strcpy(alloy->identifier,"placeholder");
	strcpy(gold->name,"Gold");
	strcpy(gold->identifier,"REDACTED");
	strcpy(gold_t->name,"Gold");

	gold_t->ptr = gold;
	gold_t->id = 0;
	gold_t->next = alloy_t;

	registration();

	strcpy(alloy->name, metalName);
	strcpy(alloy->identifier, hash);
	strcpy(alloy_t->name, metalName);

	alloy_t->id=1000;
	alloy_t->ptr = alloy;
	alloy_t->next = NULL;

	menu();

	return 0;
}