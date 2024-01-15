#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creation_tableau_verbe.h"
#include "read_with_mmap.h"
#include "dictionnaire.h"

// Nous avons repris le code de la correction de la séance précédente mais ATTENTION à la place de terminal dans la structure de dictionnaire se trouve un entier catégorie qui vaut 0 si aucun mot n'y est, 1 si un mot quelconque y est (pour etre retro compatible), 2 si c'est un verbe du premier groupe, 3 un verbe du second groupe, 4 troisieme groupe
//on a fait une fonction (qui est testé ci dessous mais qui a un petit probleme) qui met les verbe du dico dans un dicctionaire
//on à également fais une fonction qui load le fichier a conjuger
//il vous reste "que" à faire les fonctions qui conjuge les verbe en fonvtion du pronom

void    ajouter_fichier_dans_dictionnaire(char *fichier, dictionnaire d)
{
    FILE *fd = fopen ( fichier, "r" ); // on ouvre le .dic
    if ( fd == NULL )
    {
        // check si le fichier a bien été ouvert
        printf ( " Erreur lors de l ' ouverture du fichier %s  \n ", fichier);
    }
    else
    {
        char ligne[100];
        while (fscanf(fd, "%s", ligne) != EOF)
        {
            // on vérifie si on n'est pas à la fin du fichier
            ajouter_mot(d, ligne); //sinon on ajoute le mot au dictionaire
        }
    }
    fclose(fd); // on ferme le fichier
}

int    main(void)
{

    dictionnaire dicoVerbe; // on créé le dico qui possèderas tout les verbe avec leur groupe
    ajouter_fichier_dans_dictionnaire("fr-reforme1990_court_sans.dic", dicoVerbe); // on ajoute les verbes dans le dico
    return 0;
}

