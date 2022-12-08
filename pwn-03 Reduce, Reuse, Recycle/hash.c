#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
//gcc hash.c -static -lcrypt -o hash

char salt[8] = "APUBOH22";
char *hash;

void setup(){
	char identifier_L[33];
	printf("Create a password.\n> ");
	scanf("%32s",&identifier_L);
	char *hash = crypt(identifier_L,salt);
    printf("%s\n", hash);
}

int main(){
    setup();
}

