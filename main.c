#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 100  // Maximum number of lines to read

// Function to read a line dynamically
char* readLine(FILE* file) {
 char *line = NULL;
 int ch;
 size_t length = 0;
 size_t bufferSize = 0;

 while ((ch = fgetc(file)) != '\n' && ch != EOF) {
  if (length + 1 >= bufferSize) {
   bufferSize = bufferSize == 0 ? 16 : bufferSize * 2;
   line = realloc(line, bufferSize);
  }
  line[length++] = ch;
 }

 if (length == 0 && ch == EOF) {
  free(line);
  return NULL;  // End of file
 }

 line[length] = '\0';  // Null-terminate the string
 return line;
}

int main() {
 FILE *file = fopen("input.txt", "r");
 if (file == NULL) {
  printf("Error opening file\n");
  return 1;
 }

 char *lines[MAX_LINES];
 int lineCount = 0;

 // Read lines into the array
 while (lineCount < MAX_LINES) {
  char *line = readLine(file);
  if (line == NULL) {
   break;  // End of file or error
  }
  lines[lineCount++] = line;
 }

 fclose(file);

 // Print the lines
 for (int i = 0; i < lineCount; i++) {
  printf("Line %d: %s\n", i + 1, lines[i]);
  free(lines[i]);  // Free the memory for each line
 }

 return 0;
}
