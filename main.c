#include "lexer.h"

#define MAX_CHARACTERS 10000
#define MAX_TOKENS 1000

Token *tokenArr;

int main(){
 char *filename = "test1.racs";
 FILE *fp = fopen(filename, "r");

 if (fp == NULL){printf("Error: could not open file %s", filename);return 1;}

 char *buffer = (char*)malloc(MAX_CHARACTERS * sizeof(char));
 if (buffer == NULL){fclose(fp);return 1;}

 fgets(buffer, MAX_CHARACTERS, fp);

 tokenArr = scanTokens(buffer);

 printf("%d\n", tokenArr[0].type);
 printf("%d\n", tokenArr[1].type);
 printf("%d\n", tokenArr[2].type);
 printf("%d\n", tokenArr[3].type);

 fclose(fp);
 return 0;
}
