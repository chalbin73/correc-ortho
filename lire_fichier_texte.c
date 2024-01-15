#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "read_with_mmap.h"
#include "tableau_dyn.h"

// Ce code lit le fichier texte "texte5.txt" et affiche son contenu dans un tableau. Mais marche pas.

int* main(int argc, char *argv[]) { 
  size_t size;
  char *fichier = open_mmapfile("texte5.txt", &size); // on ouvre le fichier
  tableau* t_mot = creer_tableau(1); // on crée un tableau de taille 1
  tableau* t_temp = creer_tableau(1); // on crée un 2e tableau de taille 1
  for(int i=0; i<size;i++){ // on parcourt le fichier
    if (fichier[i] == ' ' || fichier[i] == '.'){ // si on tombe sur un espace ou un point
      if (taille(t_temp)!=0){ // si le tableau temporaire n'est pas vide
        push_back(t_mot, 1); // on ajoute le tableau dans le tableau de mots
        char* mot_temp = (char*)malloc(taille(t_temp)*sizeof(char)); // on alloue de la mémoire pour le mot temporaire
        for(int k; k<taille(t_temp);k++){ // on parcourt le tableau temporaire
          mot_temp[k] = get(t_temp,k); // on copie le contenu du tableau temporaire dans le mot temporaire
        }
        set(t_mot, taille(t_mot)-1, mot_temp); // on ajoute le tableau temporaire dans le tableau de mots
      }
    }
    else{
      push_back(t_temp,1); // on ajoute le caractère dans le tableau temporaire
      set(t_temp,taille(t_temp)-1,fichier[i]); 
    }
  }
  for(int i =0;taille(t_mot)>i;i++){
    printf("%s ",get(t_mot,i));
  }
  return t_mot;
}

