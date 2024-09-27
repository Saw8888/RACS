#include "parser.h"

#define MAX_CHARACTERS 10000
#define MAX_TOKENS 1000

#define MAX_HEIGHT 1000
#define MAX_WIDTH 255


Token *tokenArr;

const char* getASTNodeTypeName(ASTNodeType type) {
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


// Function to format and print the AST nodes in an ASCII tree
int _print_ast(ASTNode *node, int is_left, int offset, int depth, char s[20][255]) {
    char b[50];  // Larger buffer to fit node type or token value
    int width = 9; // Increased width for larger node labels

    if (!node) return 0;

    // If the node has a token, print its value; otherwise, print the node type
    if (node->token && node->token->value) {
        snprintf(b, sizeof(b), "(%s)", node->token->value);
    } else {
        snprintf(b, sizeof(b), "[%s]", getASTNodeTypeName(node->type));
    }

    int left  = _print_ast(node->left,  1, offset,                depth + 1, s);
    int right = _print_ast(node->right, 0, offset + left + width, depth + 1, s);

    // Print the current node in the string array 's'
    for (int i = 0; i < width && b[i] != '\0'; i++)
        s[2 * depth][offset + left + i] = b[i];

    // Connect left and right children with lines in the ASCII tree
    if (depth && is_left) {
        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';
        s[2 * depth - 1][offset + left + width / 2] = '+';
    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';
        s[2 * depth - 1][offset + left + width / 2] = '+';
    }

    // Recursively print the children (if any)
    int child_offset = offset + left + width;
    for (int i = 0; i < node->childrenCount; i++) {
        child_offset += _print_ast(node->children[i], 0, child_offset, depth + 1, s);
    }

    return left + width + right;
}

// Public function to print the AST
void print_ast(ASTNode *root) {
    char s[20][255];
    for (int i = 0; i < 20; i++) {
        sprintf(s[i], "%80s", " ");
    }

    _print_ast(root, 0, 0, 0, s);

    for (int i = 0; i < 20; i++) {
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

 print_ast(AST);

 fclose(fp);
 return 0;
}
