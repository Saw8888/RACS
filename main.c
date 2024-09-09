#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
 FILE *file = fopen("input.txt", "r");
 if (!file) return 1;

 char **lines = NULL;
 char *buffer = NULL;
 size_t len = 0;
 ssize_t nread;
 int count = 0;

 while ((nread = getline(&buffer, &len, file)) != -1) {
  lines = realloc(lines, (count + 1) * sizeof(char *));
  lines[count] = strdup(buffer);
  count++;
 }

 fclose(file);
 free(buffer);

 for (int i = 0; i < count; i++) {
  printf("%s", lines[i]);
 }
 
 for (int i = 0; i < count; i++) {free(lines[i]);}
 free(lines);

 return 0;
}
