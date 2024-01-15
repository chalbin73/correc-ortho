#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "read_with_mmap.h"
#include "dictionnaire.h"



void ajouter_fichier_dans_dictionnaire(char* fichier, dictionnaire d) {
  FILE * fd = fopen ( fichier , "r" ); // on ouvre le .dic
  if ( fd == NULL ) { // check si le fichier a bien été ouvert
    printf ( " Erreur lors de l ' ouverture du fichier %s  \n " ,
    fichier) ;
  } else {
    char ligne[100];
    while (fscanf(fd, "%s", ligne) != EOF) { // on vérifie si on n'est pas à la fin du fichier 
       ajouter_mot(d, ligne); //sinon on ajoute le mot au dictionaire 
  }
  fclose(fd); // on ferme le fichier
}





