/**
 * Projet Correcteur Orthographique. 2024.
 * Phase 1. Détection d'erreurs.
 *
 * @author  : M. Durand
 * @date    : version
 * @version : 1.0
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionnaire.h"

/**
 * Renvoie un dictionnaire vide initialisé à 0.
 *
 * En pratique, il faut allouer un premier élément, qui correspond au cercle le
 * plus à gauche sur le dessin de la structure.
 * Puis affecter la valeur NULL à tous les éléments du tableau suivantes.
 * Enfin, préciser que le noeud est terminal.
 */
dictionnaire    dictionnaire_vide()
{
    dictionnaire d = (lettre *)malloc( sizeof(lettre) );
    if (d == NULL)
    {
        printf("Problème d'allocation\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < NB_LETTRES; i++)
    {
        d->suivantes[i] = NULL;
    }
    d->categorie = 0;

    d->nb_mots = 0; // non demandé

    return d;
}


/**
 * Ajoute un mot à un dictionnaire précédemment créé.
 *
 * Après l'appel à la fonction le chemin représentant le mot mot est créé et le
 * noeud atteint à la fin du mot est marqué comme terminal.
 *
 * Il est assez naturel d'utiliser une fonction récursive ici.
 * Le plus simple pour gérer l'éventuel signe '/' après le mot est de
 * l'utiliser, au même titre que '\0' comme fin de chaîne de caractères.
 */
void    ajouter_mot(dictionnaire d, char *mot)
{
    assert(d != NULL);
    if (mot[0] != '\0' && mot[0] != '/')
    {
        int indice = indice_lettre( (unsigned char *)mot );
        if (indice == -1)
        {
            printf("caractere %s non connu !\n", mot);
        }
        else
        {
            if (d->suivantes[indice] == NULL)
            {
                d->suivantes[indice] = dictionnaire_vide();
            }
            char *s = &mot[1];
            if (indice >= 28)
            {
                s = &s[1];
            }
            ajouter_mot(d->suivantes[indice], s);
            d->nb_mots++; // non demandé
        }
    }
    else if(mot[1] == 'a' && mot[0] == '/')  //le mot est un verbe du premier groupe
    {
        d->categorie = 2;
    }
    else if (mot[1] == 'f'  && mot[0] == '/')   // le mot est un verbe du deuxième groupe
    {
        d->categorie = 3;
    }
    else if (mot[1] == 'u'  && mot[0] == '/')   // le mot est un verbe du troisième groupe
    {
        d->categorie = 4;
    }
    else
    {
        d->categorie = 1; // le mot existe mais n'est pas un verbe
    }
}


/**
 * Cherche un mot dans un dictionnaire précédemment créé et enrichi.
 *
 * Il faut parcourir les caractères du mot et s'assurer que les arcs entre
 * chaque lettre et la suivante existent.
 * Il faut vérifier à la fin que l'élément est 'terminal'.
 */
int    chercher_mot(dictionnaire d, char *mot)
{
    assert(d != NULL);
    if (mot[0] != '\0' && mot[0] != '/')
    {
        int indice = indice_lettre( (unsigned char *)mot );
        if (indice == -1)
        {
            printf("caractere %s non connu !\n", mot);
            return false;
        }
        else
        {
            if (d->suivantes[indice] == NULL)
            {
                return 0;
            }
            else
            {
                char *s = &mot[1];
                if (indice >= 28)
                {
                    s = &s[1];
                }
                return chercher_mot(d->suivantes[indice], s);
            }
        }
    }
    else
    {
        return d->categorie;
    }
}
// retourne 0 si le mot n'y est pas 1 si c'est un mot terminal 2 si c'est un verbe du premier groupe 3 si c'est un verbe du second groupe

/**
 * Libère l'espace mémoire alloué au dictionnaire complet.
 *
 * Une écriture récursive est naturelle ici aussi.
 * Il faut appeler la suppression sur chacune des lettres suivantes et quand ce
 * travail est terminé, supprimer l'élément courant.
 */
void    supprimer_dictionnaire(dictionnaire    d)
{
    if (d != NULL)
    {
        for(int i = 0; i < NB_LETTRES; i++)
        {
            supprimer_dictionnaire(d->suivantes[i]);
        }
        free(d);
    }
}



/* Fonctions ci-dessous non demandées. */
// Étant donné ce qui se passe au moment de l'ajout, la fonction suivante
// renverra le nombre de mots qui ont commencé à être ajouté. En cas de souci,
// cela ne sera peut-être pas le nombre de mots effectivement contenu par le
// dictionnaire.
int    nombre_de_mots(dictionnaire    d)
{
    assert(d != NULL);

    return d->nb_mots;
}

// Pour avoir une idée du taux de remplissage.
int    nombre_de_structures(dictionnaire    d)
{
    assert(d != NULL);
    int cpt = 1;
    for(int i = 0; i < NB_LETTRES; i++)
    {
        if (d->suivantes[i] != NULL)
        {
            cpt = cpt + nombre_de_structures(d->suivantes[i]);
        }
    }
    return cpt;
}

