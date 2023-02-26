/**
 * @file ABR.h
 * @author TWARDAWA Yanis, TOUATI Damien
 * @brief fichier des déclarations des fonctions sur les ABR
 * (arbre binaire de recherche) avec une chaîne de caractères
 * @version 0.1
 * @date 2023-02-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __ABR__
#define __ABR__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 512

typedef struct noeud{
    char * mot;
    struct noeud *fg, *fd;
}Noeud, *Arbre;


/**
 * @brief fonction qui alloue dynamiquement la structure noeud
 * 
 * @param mot 
 * @return Noeud* 
 */
Noeud* alloue_noeud(char* mot);


/**
 * @brief fonction récursive qui parcours un arbre A et affiche ses valeurs
 * sur la sortie standard dans un parcours de l'arbre dit infixe
 * 
 * @param A 
 */
void parcours_infixe(Arbre A);


/**
 * @brief fonction qui ajoute un noeud à la structure *A en conservant
 * la caractère d'être un ABR
 * 
 * @param A 
 * @param mot 
 * @return Noeud* 
 */
Noeud* ajout(Arbre* A, char* mot);


/**
 * @brief fonction qui extrait le maximun d'un arbre *A et le supprime
 * de l'arbre et renvoie l'adresse du noeud
 * 
 * @param A 
 * @return Noeud* 
 */
Noeud* extrait_max(Arbre* A);


/**
 * @brief fonction qui supprime un noeud de l'arbre *A qui contient le
 * mot et renvoie l'adresse du noeud en maintenant 
 * le caractère d'être un ABR
 * 
 * @param A 
 * @param mot 
 * @return Noeud* 
 */
Noeud* suppression(Arbre* A, char* mot);


/**
 * @brief fonction qui libère tout les noeud de l'arbre *A 
 * alloué dynamiquement de manière récursive
 * 
 * @param A 
 */
void libere(Arbre* A);


/**
 * @brief crée un fichier .pdf dont le nom est passé en paramètre 
 * qui contient une représentation graphique de
 * l’arbre A réalisée à l’aide de l’utilitaire dot
 * 
 * @param nom 
 * @param A 
 */
void dessine(char* nom, Arbre A);


/**
 * @brief fonctio qui va creer un arbre à partir du fichier nommer nom
 * 
 * 
 * @param nom 
 * @param A 
 * @return int 
 */
int cree_arbre(char * nom, Arbre * A);


/* 
    fonction non demandé mais rajouté pour utiliser 
    l'outil dot pour la visualisation d'un arbre 
*/


/**
 * @brief fonction qui écrit le début d'un fichier .dot
 * 
 * @param f fichier pris en parametre
 */
void ecrireDebut(FILE *f);


/**
 * @brief fonction pour générer les visualistions d'un arbre et rempli
 * un fichier .dot
 * 
 * @param f fichier pris en parametre 
 */
void ecrireArbre(FILE *f, Arbre a);


/**
 * @brief fonction pour ecrire la fin d'un fichier dot
 * 
 * @param f fichier pris en parametre  
 */
void ecrireFin(FILE* f);


/**
 * @brief fonction qui realise le fichier .dot d'un arbre a
 * 
 * @param f 
 * @param a 
 */
void cree_dot(FILE *f, Arbre a);

#endif
