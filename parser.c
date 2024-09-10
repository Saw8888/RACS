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
 TOKEN_SETTINGS,   // '@'
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

typedef enum {
 AST_PROGRAM,    // The root node of the program
 AST_FUNC_DEF,   // Function definition, e.g., main or other user-defined functions
 AST_BLOCK,      // Block of statements, enclosed in '{ }'
 AST_VAR_DECL,   // Variable declaration, e.g., int x
 AST_ASSIGNMENT, // Variable assignment, e.g., x = 5
 AST_BIN_OP,     // Binary operations (add, subtract, etc.)
 AST_UNARY_OP,   // Unary operations (like negation)
 AST_IF,         // 'if' statement
 AST_FOR,        // 'for' loop
 AST_PRINT,      // 'print' statement
 AST_LITERAL,    // Literal values (integers, strings, etc.)
 AST_VAR,        // Variable reference
 AST_FUNC_CALL   // Function calls
} ASTNodeType;


typedef struct ASTNode {
 ASTNodeType type;
 struct ASTNode* left;  // Left child (for binary ops, etc.)
 struct ASTNode* right; // Right child
 char* value;           // Stores variable names, literals, etc.
 struct ASTNode** children; // For blocks or function arguments
 int childrenCount;     // Number of children (for blocks, function args)
} ASTNode;
