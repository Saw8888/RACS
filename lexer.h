#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
 TOKEN_INT,        // 'int'
 TOKEN_ADDR,       // 'addr'
 TOKEN_ADDRARR,    // 'addrArr'
 TOKEN_ARR,        // 'arr'
 TOKEN_MEM,        // 'mem'
 TOKEN_STR,        // 'str'
 TOKEN_MAIN,       // 'main'
 TOKEN_ARROW_RIGHT,// '->'
 TOKEN_ARROW_LEFT, // '<-'
 TOKEN_EQUAL,      // '='
 TOKEN_SMALLER,    // '<'
 TOKEN_BIGGER,     // '>'
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


Token* scanTokens(const char* source);
Token* createToken(TokenType type, const char* start, int length);
void scanToken(const char** current, Token* tokens, int* tokenCount);
int isAlpha(char c);
int isDigit(char c);
int isAtEnd(const char* current);
int match(char expected, const char** current);