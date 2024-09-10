#include "lexer.h"

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

ASTNode* createASTNode(ASTNodeType type, char* value) {
 ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
 node->type = type;
 node->left = NULL;
 node->right = NULL;
 node->value = value ? strdup(value) : NULL;
 node->children = NULL;
 node->childrenCount = 0;
 return node;
}

