#include "parser.h"

#define MAX_CHARACTERS 10000
#define MAX_TOKENS 1000

#define MAX_HEIGHT 1000
#define MAX_WIDTH 255


Token *tokenArr;

const char* getASTNodeTypeString(ASTNodeType type) {
  switch (type) {
    case AST_PROGRAM: return "PROGRAM";
    case AST_FUNC_DEF: return "FUNC_DEF";
    case AST_BLOCK: return "BLOCK";
    case AST_VAR_DECL: return "VAR_DECL";
    case AST_ASSIGNMENT: return "ASSIGNMENT";
    case AST_BIN_OP: return "BIN_OP";
    case AST_UNARY_OP: return "UNARY_OP";
    case AST_IF: return "IF";
    case AST_FOR: return "FOR";
    case AST_PRINT: return "PRINT";
    case AST_LITERAL: return "LITERAL";
    case AST_VAR: return "VAR";
    case AST_FUNC_CALL: return "FUNC_CALL";
    default: return "UNKNOWN";
  }
}

// Function to convert TokenType to string for printing
const char* getTokenTypeString(TokenType type) {
  switch (type) {
    case TOKEN_INT: return "INT";
    case TOKEN_ADDR: return "ADDR";
    case TOKEN_ADDRARR: return "ADDRARR";
    case TOKEN_ARR: return "ARR";
    case TOKEN_MEM: return "MEM";
    case TOKEN_STR: return "STR";
    case TOKEN_MAIN: return "MAIN";
    case TOKEN_ARROW_RIGHT: return "->";
    case TOKEN_ARROW_LEFT: return "<-";
    case TOKEN_EQUAL: return "=";
    case TOKEN_SMALLER: return "<";
    case TOKEN_BIGGER: return ">";
    case TOKEN_LPAREN: return "(";
    case TOKEN_RPAREN: return ")";
    case TOKEN_LBRACE: return "{";
    case TOKEN_RBRACE: return "}";
    case TOKEN_SETTINGS: return "@";
    case TOKEN_STATIC: return "STATIC";
    case TOKEN_SUM: return "+";
    case TOKEN_SUB: return "-";
    case TOKEN_DIV: return "/";
    case TOKEN_MULT: return "*";
    case TOKEN_INT_DATA: return "INT_DATA";
    case TOKEN_ADDR_DATA: return "ADDR_DATA";
    case TOKEN_IDENTIFIER: return "IDENTIFIER";
    case TOKEN_STRING: return "STRING";
    case TOKEN_NULL: return "NULL";
    case TOKEN_COMMA: return ",";
    case TOKEN_FOR: return "FOR";
    case TOKEN_IF: return "IF";
    case TOKEN_PRINT: return "PRINT";
    case TOKEN_EOF: return "EOF";
    default: return "UNKNOWN";
  }
}

// Helper function to print AST node content
void printNode(char* buffer, ASTNode* node) {
  if (node->token) {
    sprintf(buffer, "(%s, %s)", getASTNodeTypeString(node->type), node->token->value);
  } else {
    sprintf(buffer, "(%s)", getASTNodeTypeString(node->type));
  }
}

// Recursive function to print the AST in tree format
int _printAST(ASTNode* node, int is_left, int offset, int depth, char s[MAX_HEIGHT][MAX_WIDTH]) {
  char b[20];
  int width = 7;
  if (!node) return 0;

  printNode(b, node);
  //Random comment

  int left  = _printAST(node->left,  1, offset,                depth + 1, s);
  int right = _printAST(node->right, 0, offset + left + width, depth + 1, s);

  for (int i = 0; i < width; i++)
    s[2 * depth][offset + left + i] = b[i];

  if (depth && is_left) {
    for (int i = 0; i < width + right; i++)
      s[2 * depth - 1][offset + left + width/2 + i] = '-';
    s[2 * depth - 1][offset + left + width/2] = '+';
  } else if (depth && !is_left) {
    for (int i = 0; i < left + width; i++)
      s[2 * depth - 1][offset - width/2 + i] = '-';
    s[2 * depth - 1][offset + left + width/2] = '+';
  }

  return left + width + right;
}

// Print the full AST tree
void printAST(ASTNode* root) {
  char s[MAX_HEIGHT][MAX_WIDTH];
  for (int i = 0; i < MAX_HEIGHT; i++)
    sprintf(s[i], "%80s", " ");

  _printAST(root, 0, 0, 0, s);

  for (int i = 0; i < MAX_HEIGHT; i++) {
    if (strlen(s[i]) > 0)
      printf("%s\n", s[i]);
  }
}


int main(){
 char *filename = "test1.racs";
 FILE *fp = fopen("test1.racs", "r");

 if (fp == NULL){printf("Error: could not open file %s", filename);return 1;}

 char *buffer = (char*)malloc(MAX_CHARACTERS * sizeof(char));
 if (buffer == NULL){fclose(fp);return 1;}

 fgets(buffer, MAX_CHARACTERS, fp);

 tokenArr = scanTokens(buffer);

 printf("%d\n", tokenArr[0].type);
 printf("%d\n", tokenArr[1].type);
 printf("%d\n", tokenArr[2].type);
 printf("%d\n", tokenArr[3].type);

 Parser parseStruct = initParser(tokenArr);
 ASTNode *AST = parseProgram(&parseStruct);

 if (AST == NULL) {
  printf("AST generation failed.\n");
  return 1;
 }

 printAST(AST);

 fclose(fp);
 return 0;
}
