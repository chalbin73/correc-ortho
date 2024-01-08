#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure Node représentant un élément de la liste chaînée
typedef struct Node {
  struct Node *next;
} Node;

// Définition de la structure Liste_Node représentant le dictionnaire
typedef struct Liste_Node {
  int terminal; // Indicateur pour savoir si un mot est dans le dictionnaire
  Node *liste[26]; // Tableau de pointeurs vers des éléments de la structure Node, chaque indice correspond à une lettre dans l'ordre alphabétique
} Liste_Node;

// Fonction pour ajouter un mot dans le dictionnaire
void ajouter_mot(Liste_Node *dico, char *mot) {
  for (int i = 0; i < strlen(mot); i++) {
    Node *p = dico->liste[mot[i] - 97]; // Récupération de l'élément correspondant à la lettre du mot, -97 pour avoir l'indice de la lettre dans l'alphabet par rapport à l'ascii
    if (p == NULL) { // Si l'élément n'existe pas encore
      p = (Node *)malloc(sizeof(Node)); // Allouer de la mémoire pour créer un nouvel élément
      if (p == NULL) {
        exit(EXIT_FAILURE);
      }
      dico->liste[mot[i] - 97] = p; // Mettre à jour le tableau avec le nouvel élément
    }
    if (i == strlen(mot) - 1) { // Si c'est la dernière lettre du mot
      dico->terminal = 1; // Marquer le mot comme terminé
    }
  }
}

// Fonction pour rechercher un mot dans le dictionnaire
int rechercher_mot(Liste_Node *dico, char *mot) {
  for (int i = 0; i < strlen(mot); i++) {
    Node *p = dico->liste[mot[i] - 97]; // Récupération de l'élément correspondant à la lettre du mot
    if (p == NULL) { // S'il n'existe pas de lien vers la prochaine lettre
      printf("On ne connaît pas le mot %s\n", mot);
      return 0;
    }
    if (i == strlen(mot) - 1) { // Si c'est la dernière lettre du mot
      if (dico->terminal == 1) { // Si le mot est marqué comme terminé
        printf("Le mot %s est dans le dictionnaire\n", mot);
        return 1;
      }
    }
    dico->liste[mot[i] - 97] = p; // Mettre à jour le tableau avec l'élément suivant
  }
  return 0;
}

int main(void) {
  Liste_Node Dico; // Initialisation du dictionnaire

  // Check le si les fonction marche
  ajouter_mot(&Dico, "bonjour");
  rechercher_mot(&Dico, "pkjjour");
  rechercher_mot(&Dico, "bonjour");
  rechercher_mot(&Dico, "bongour");
  return 0;
}
