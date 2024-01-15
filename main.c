#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creation_tableau_verbe.h"
#include "dictionnaire.h"

// Nous avons repris le code de la correction de la séance précédente mais ATTENTION à la place de terminal dans la structure de dictionnaire se trouve un entier catégorie qui vaut 0 si aucun mot n'y est, 1 si un mot quelconque y est (pour etre retro compatible), 2 si c'est un verbe du premier groupe, 3 un verbe du second groupe, 4 troisieme groupe
//on a fait une fonction (qui est testé ci dessous mais qui a un petit probleme) qui met les verbe du dico dans un dicctionaire
//on à également fais une fonction qui load le fichier a conjuger 
//il vous reste "que" à faire les fonctions qui conjuge les verbe en fonvtion du pronom 

int main(void) {

  dictionnaire dicoVerbe; // on créé le dico qui possèderas tout les verbe avec leur groupe
  ajouter_fichier_dans_dictionnaire("fr-reforme1990_court_sans.dic",dicoVerbe); // on ajoute les verbes dans le dico
  return 0;
}
