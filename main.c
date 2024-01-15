#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "read_with_mmap.h"
#include "dictionnaire.h"

typedef struct
{
    char    verbe[256]; // Terminé par '\0'
    char    verbe_conjuge[256];
    int     groupe;
    char   *occ_txt; // Position dans le texte (pour le remplacer)
} verbe;

char   *next_word(char   *txt)
{
    bool was_not_word = false;
    while(*(txt++) != '\0')
    {
        if(
            txt[0] == '.' ||
            txt[0] == '\n' ||
            txt[0] == ' '
            )
        {
            was_not_word = true;
        }
        else if(was_not_word)
        {
            return txt;
        }
    }
    return NULL;
}

int    word_length(char   *txt)
{
    int length = 0;
    while(*txt != ' ' && *txt != '\n' && *txt != '.' && *txt != ',' && *txt != '\0')
    {
        txt++;
        length++;
    }
    return length;
}

void     ip_to_lower(char   *txt)
{
    while( txt[0] != '\0')
    {
        txt[0] = tolower(txt[0]);
        txt++;
    }
}

verbe    detection_verbe(dictionnaire dico, char *txt, size_t length)
{
    int wl = word_length(txt);

    char mot[256];
    memcpy(mot, txt, wl);
    ip_to_lower(mot);
    mot[wl] = '\0';

    if(chercher_mot(dico, mot) >= 2)
    {
        printf("\e[32m");
    }
    printf("VERBE (%5d): %s\n", wl, mot);
    printf("\e[0m");

    char *n_word = next_word(txt);

    if(!n_word)
    {
        return (verbe)
               {
                   0
               };
    }

    return detection_verbe(dico, n_word, length);
}


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
    size_t taille_texte = 0;
    char *texte_entree  = open_mmapfile("texte5.txt", &taille_texte);

    dictionnaire dicoVerbe = dictionnaire_vide(); // on créé le dico qui possèderas tout les verbe avec leur groupe
    ajouter_fichier_dans_dictionnaire("fr-reforme1990_court_sans.dic", dicoVerbe);

    if(chercher_mot(dicoVerbe, "établir") >= 2)
    {
        printf("WTF: Tu est un verbe ... \n");
    }
    detection_verbe(dicoVerbe, texte_entree, taille_texte);

    close_mmapfile(texte_entree, taille_texte);
    return 0;
}

