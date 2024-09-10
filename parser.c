#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct{
 void* left;
 void* right;
 Token data;
}Node;

