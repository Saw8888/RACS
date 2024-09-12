#include "lexer.h"

typedef enum {
 AST_PROGRAM,    // Root node
 AST_FUNC_DEF,   // Function definition
 AST_BLOCK,      // '{ }'
 AST_VAR_DECL,   // int x
 AST_ASSIGNMENT, // x = 5
 AST_BIN_OP,     // +,-,/,*
 AST_UNARY_OP,   // like negation
 AST_IF,         // 'if'
 AST_FOR,        // 'for'
 AST_PRINT,      // 'print'
 AST_LITERAL,    // 22,"hello"
 AST_VAR,        // Variable reference
 AST_FUNC_CALL   // Function calls
} ASTNodeType;

typedef struct ASTNode {
 ASTNodeType type;
 struct ASTNode* left;       // Left child (for binary ops, etc.)
 struct ASTNode* right;      // Right child
 Token* token;               // Pointer to the token representing this node
 struct ASTNode** children;  // For blocks or function arguments
 int childrenCount;          // Number of children (for blocks, function args)
} ASTNode;

typedef struct {
 Token* tokens; // Array of tokens
 int current;   // Current token index
 int tokenCount;
} Parser;

Parser initParser(Token* tokens);
ASTNode* parseProgram(Parser* parser);