#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  struct Node *next;
} Node;

typedef struct Liste_Node {
  int terminal;
  Node *liste[26];
} Liste_Node;

void ajouter_mot(Liste_Node *dico, char *mot) {
  for (int i = 0; i < strlen(mot); i++) {
    Node *p = dico->liste[mot[i] - 97];
    if (p == NULL) {
      p = (Node *)malloc(sizeof(Node));
      if (p == NULL) {
        exit(EXIT_FAILURE);
      }
      dico->liste[mot[i] - 97] = p;
    }
    if (i == strlen(mot) - 1) {
      dico->terminal = 1;
    }
  }
}

int main(void) {
  Liste_Node Dico;

  ajouter_mot(&Dico, "bonjour");
  return 0;
}