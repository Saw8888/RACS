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

ASTNode* parseProgram(Parser* parser);
ASTNode* parseMain(Parser* parser);
ASTNode* parseExpression(Parser* parser);
ASTNode* parseStatement(Parser* parser);

Token* peek(Parser* parser) {
 if (parser->current >= parser->tokenCount) return NULL;
 return &parser->tokens[parser->current];
}

Token* advance(Parser* parser) {
 if (parser->current < parser->tokenCount) {
  return &parser->tokens[parser->current++];
 }
 return NULL;
}

int matchToken(Parser* parser, TokenType type) {
 if (peek(parser)->type == type) {
  advance(parser);
  return 1;
 }
 return 0;
}

ASTNode* createASTNode(ASTNodeType type, Token* token) {
 ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
 node->type = type;
 node->left = NULL;
 node->right = NULL;
 node->token = token;
 node->children = NULL;
 node->childrenCount = 0;
 return node;
}

void addASTChild(ASTNode* parent, ASTNode* child) {
 parent->children = (ASTNode**)realloc(parent->children, sizeof(ASTNode*) * (parent->childrenCount + 1));
 parent->children[parent->childrenCount++] = child;
}


ASTNode* parseVariableDeclaration(Parser* parser) {
 Token* typeToken = advance(parser);      // Token for 'int', 'addr', etc.
 Token* identifierToken = advance(parser); // Token for variable name

 ASTNode* varDeclNode = createASTNode(AST_VAR_DECL, identifierToken);

 if (matchToken(parser, TOKEN_EQUAL)) {
  ASTNode* assignmentNode = createASTNode(AST_ASSIGNMENT, identifierToken);
  ASTNode* valueNode = parseExpression(parser);
  assignmentNode->left = varDeclNode;
  assignmentNode->right = valueNode;
  return assignmentNode;
 }

 return varDeclNode;
}

ASTNode* parseBlock(Parser* parser) {
 ASTNode* blockNode = createASTNode(AST_BLOCK, NULL); // Blocks don't need a token

 while (!matchToken(parser, TOKEN_RBRACE) && peek(parser)->type != TOKEN_EOF) {
  ASTNode* statement = parseStatement(parser);
  if (statement) {
   addASTChild(blockNode, statement);
  }
 }

 return blockNode;
}

ASTNode* parseMain(Parser* parser) {
 if (matchToken(parser, TOKEN_MAIN)) {
  matchToken(parser, TOKEN_LPAREN);
  Token* fileToken = advance(parser);
  matchToken(parser, TOKEN_RPAREN);

  ASTNode* mainNode = createASTNode(AST_FUNC_DEF, peek(parser)); // Pass the 'main' token
  mainNode->left = createASTNode(AST_LITERAL, fileToken); // The file name token
  if (matchToken(parser, TOKEN_LBRACE)) {
   mainNode->right = parseBlock(parser);
  }

  return mainNode;
 }
 return NULL;
}

ASTNode* parseExpression(Parser* parser) {
 Token* token = advance(parser);

 if (token->type == TOKEN_INT_DATA) {
  return createASTNode(AST_LITERAL, token);
 }

 if (token->type == TOKEN_IDENTIFIER) {
  return createASTNode(AST_VAR, token);
 }

 // Handle binary operations like `x + 5`
 if (token->type == TOKEN_SUM || token->type == TOKEN_SUB || token->type == TOKEN_MULT || token->type == TOKEN_DIV) {
  ASTNode* left = parseExpression(parser);
  ASTNode* right = parseExpression(parser);
  ASTNode* opNode = createASTNode(AST_BIN_OP, token);
  opNode->left = left;
  opNode->right = right;
  return opNode;
 }

 return NULL;
}


ASTNode* parseProgram(Parser* parser) {
 ASTNode* programNode = createASTNode(AST_PROGRAM, NULL);
 while (peek(parser)->type != TOKEN_EOF) {
  if (peek(parser)->type == TOKEN_INT || peek(parser)->type == TOKEN_ADDR || peek(parser)->type == TOKEN_ARR || peek(parser)->type == TOKEN_STR) {
   addASTChild(programNode, parseVariableDeclaration(parser));
  } else if (peek(parser)->type == TOKEN_MAIN) {
   addASTChild(programNode, parseMain(parser));
  } else if (peek(parser)->type == TOKEN_SETTINGS) {
   advance(parser);//For now we ignore the @static
  }else if (peek(parser)->type == TOKEN_IDENTIFIER) {
   addASTChild(programNode, parseMain(parser));
  }
 }

 return programNode;
}

ASTNode* parseStatement(Parser* parser) {
 Token* token = peek(parser);
 if (token->type == TOKEN_INT || token->type == TOKEN_ADDR || token->type == TOKEN_ARR || token->type == TOKEN_STR) {
  return parseVariableDeclaration(parser);
 } else if (token->type == TOKEN_IDENTIFIER) {
  Token* nextToken = peek(parser + 1);
  if (nextToken && nextToken->type == TOKEN_EQUAL) {
   return parseVariableDeclaration(parser); // Reuse parseVariableDeclaration for assignments
  } else {
   return parseExpression(parser); // This might need to be adjusted for actual function calls
  }
 } else if (token->type == TOKEN_PRINT) {
  advance(parser);
  ASTNode* exprNode = parseExpression(parser);
  ASTNode* printNode = createASTNode(AST_PRINT, token);
  printNode->left = exprNode;
  return printNode;
 } else if (token->type == TOKEN_IF) {
  
 } else if (token->type == TOKEN_FOR) {
 }

 // Handle other statement types or errors
 return NULL;
}


Parser initParser(Token* tokens) {
 Parser parser;
 parser.tokens = tokens;
 parser.current = 0;
 int size = 0;
 while (tokens[size].type != TOKEN_EOF) size++;
 parser.tokenCount = size + 1;
 return parser;
}
