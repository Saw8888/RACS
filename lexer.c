#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHARACTERS 10000
#define MAX_TOKENS 1000

typedef enum {
 TOKEN_INT,        // 'int'
 TOKEN_ADDR,       // 'addr'
 TOKEN_ADDRARR,    // 'addrArr'
 TOKEN_ARR,        // 'arr'
 TOKEN_MEM,        // 'mem'
 TOKEN_STR,        // 'str'
 TOKEN_MAIN,       // 'main'
 TOKEN_ARROW,      // '->'
 TOKEN_EQUAL,      // '='
 TOKEN_LPAREN,     // '('
 TOKEN_RPAREN,     // ')'
 TOKEN_LBRACE,     // '{'
 TOKEN_RBRACE,     // '}'
 TOKEN_SETTINGS,   // '@'
 TOKEN_STATIC,     // no change 
 TOKEN_SUM,        // add
 TOKEN_SUB,        // substracr
 TOKEN_DIV,        // divide
 TOKEN_MULT,       // multiply
 TOKEN_INT_DATA,   // int data
 TOKEN_ADDR_DATA,  // addresses
 TOKEN_IDENTIFIER, // variable names
 TOKEN_STRING,     // strings
 TOKEN_NULL,       // 'NULL', 'null', 'Null'
 TOKEN_COMMA,      // ','
 TOKEN_FOR,        // 'for'
 TOKEN_IF,         // 'if'
 TOKEN_PRINT,      // 'print'
 TOKEN_EOF         // End of file/input
} TokenType;
typedef struct {
 TokenType type;
 char* value;
} Token;

int tokenCount = 0;

int isAlpha(char c) {return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';}
int isDigit(char c) {return c >= '0' && c <= '9';}
int isAtEnd(const char* current){return *current == '\0';}
int match(char expected, const char** current) { //Finds the next character and returns 1 if it is the expected character
 if (isAtEnd(*current)) return 0;
 if (**current != expected) return 0;
 (*current)++;
 return 1;
}

Token* createToken(TokenType type, const char* start, int length) {
 Token* token = (Token*)malloc(sizeof(Token));
 token->type = type;
 token->value = (char*)malloc(length + 1);
 strncpy(token->value, start, length);
 token->value[length] = '\0';
 return token;
}

void scanToken(const char** current, Token* tokens, int* tokenCount) {
 char c = **current;
 (*current)++;

 switch (c) {
  case '(': tokens[(*tokenCount)++] = *createToken(TOKEN_LPAREN, "(", 1); break;
  case ')': tokens[(*tokenCount)++] = *createToken(TOKEN_RPAREN, ")", 1); break;
  case '{': tokens[(*tokenCount)++] = *createToken(TOKEN_LBRACE, "{", 1); break;
  case '}': tokens[(*tokenCount)++] = *createToken(TOKEN_RBRACE, "}", 1); break;
  case '=': tokens[(*tokenCount)++] = *createToken(TOKEN_EQUAL, "=", 1); break;
  case ',': tokens[(*tokenCount)++] = *createToken(TOKEN_COMMA, ",", 1); break;
  case '+': tokens[(*tokenCount)++] = *createToken(TOKEN_SUM, "+", 1); break;
  case '*': tokens[(*tokenCount)++] = *createToken(TOKEN_MULT, "*", 1); break;
  case '/': tokens[(*tokenCount)++] = *createToken(TOKEN_SUB, "/", 1); break;
  case '@': tokens[(*tokenCount)++] = *createToken(TOKEN_SETTINGS, "@", 1); break;
  case '-':
   if (match('>', current)) {
    tokens[(*tokenCount)++] = *createToken(TOKEN_ARROW, "->", 2);
   }
   else{
    tokens[(*tokenCount)++] = *createToken(TOKEN_SUB, "-", 1);
   }
   break;
  default:
   if (isAlpha(c)) {
    const char* start = *current - 1;
    while (isAlpha(**current) || isDigit(**current)) (*current)++;
    int length = *current - start;
    char* value = (char*)malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';

    // Recognize keywords and identifiers
    if (strcmp(value, "addr") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_ADDR, value, length);
    } else if (strcmp(value, "addrArr") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_ADDRARR, value, length);
    } else if (strcmp(value, "arr") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_ARR, value, length);
    } else if (strcmp(value, "mem") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_MEM, value, length);
    } else if (strcmp(value, "str") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_STR, value, length);
    } else if (strcmp(value, "main") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_MAIN, value, length);
    } else if (strcmp(value, "NULL") == 0 || strcmp(value, "null") == 0 || strcmp(value, "Null") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_NULL, value, length);
    } else if (strcmp(value, "for") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_FOR, value, length);
    } else if (strcmp(value, "if") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_IF, value, length);
    } else if (strcmp(value, "print") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_PRINT, value, length);
    } else if (strcmp(value, "int") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_INT, value, length);
    } else if (strcmp(value, "static") == 0) {
     tokens[(*tokenCount)++] = *createToken(TOKEN_STATIC, value, length);
    } else {
     tokens[(*tokenCount)++] = *createToken(TOKEN_IDENTIFIER, value, length); // variable name
    }
    free(value);
   }
   else if(isDigit(c)){
    if(c = '0'){ // Potential address literal
     if (match('x', current)) {
      const char* start = *current - 2; // including '0x'
      while (isAlpha(**current) || isDigit(**current)) (*current)++;
      int length = *current - start;
      char* value = (char*)malloc(length + 1);
      strncpy(value, start, length);
      value[length] = '\0';
      tokens[(*tokenCount)++] = *createToken(TOKEN_ADDR_DATA, value, length);
      free(value);
      break;
     }
    }
    const char* start = *current - 1;
    while (isDigit(**current)) (*current)++;
    int length = *current - start;
    char* value = (char*)malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';
    tokens[(*tokenCount)++] = *createToken(TOKEN_INT_DATA, value, length);
    free(value);
   }
 }
}

Token* scanTokens(const char* source) {
 const char* current = source;
 Token* tokens = (Token*)malloc(MAX_TOKENS * sizeof(Token));

 while (!isAtEnd(current)) {
  scanToken(&current, tokens, &tokenCount);
 }

 tokens[tokenCount++] = *createToken(TOKEN_EOF, "", 0);
 return tokens;
}