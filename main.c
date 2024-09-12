#include "parser.h"

#define MAX_CHARACTERS 10000
#define MAX_TOKENS 1000

Token *tokenArr;

void printNode(ASTNode* node) {
  if (node->token != NULL) {
    printf("Node Type: %d, Token: %s\n", node->type, node->token->value);
  } else {
    printf("Node Type: %d, No Token\n", node->type);
  }
}

void postOrderTraversal(ASTNode* node) {
  if (node == NULL) {
    return;
  }

  // Traverse left subtree
  if (node->left != NULL) {
    postOrderTraversal(node->left);
  }

  // Traverse right subtree
  if (node->right != NULL) {
    postOrderTraversal(node->right);
  }

  // Traverse children nodes (if any)
  for (int i = 0; i < node->childrenCount; i++) {
    postOrderTraversal(node->children[i]);
  }

  // Process current node
  printNode(node);
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

 postOrderTraversal(AST);

 fclose(fp);
 return 0;
}
