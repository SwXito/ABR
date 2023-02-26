/**
 * @file ABR.c
 * @author TWARDAWA Yanis, TOUATI Damien
 * @brief fichier contenant les fonctions pour utiliser un abr
 * ansi que l'utilitaire dot
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ABR.h"


Noeud* alloue_noeud(char* mot){
    Noeud* nvx;

    nvx = (Noeud*)malloc(sizeof(Noeud));

    if(nvx != NULL){
        /* on rajoute +1 pour le \0*/
        nvx->mot = (char*)malloc(sizeof(char) * (strlen(mot) + 1));
        /* on arrête la fonction est on free nvx*/
        if(mot == NULL){
            free(nvx);
            return NULL;
        }
        /* on fait un copie du mot à l'emplacement méoire réservé */
        strcpy(nvx->mot, mot);
        nvx->fd = NULL;
        nvx->fg = NULL;
    }
    return nvx;
}


void parcours_infixe(Arbre A){
    if(A != NULL){
        parcours_infixe(A->fg);
        printf("%s\n", A->mot);
        parcours_infixe(A->fd);        
    }
}


Noeud* ajout(Arbre* A, char* mot){
    int compare; /* variable pour éviter d'appeler la 
                    fonction strcmp trop souvent */


    /* arbre vide on ajoute */
    if(*A == NULL){
        *A = alloue_noeud(mot);
        return *A;
    }
    compare = strcmp((*A)->mot, mot);

    /* mot déjà présent on revoie le noeud ou le mot ce trouve*/
    if(compare == 0){
        return *A;
    }

    /* mot de l'arbre *A est plus grand */
    if(compare > 0){
        return ajout(&(*A)->fg, mot);
    }

    /* mot de l'arbre *A est plus petit */
    else{
        return ajout(&(*A)->fd, mot);
    }
    return *A;
}


Noeud* extrait_max(Arbre* A){
    Arbre tmp;
    if (*A ==  NULL){
        return *A;
    }
    if ((*A)-> fd == NULL){
        tmp = *A;
        *A = (*A)-> fg;
        return tmp;  
    }
    return extrait_max(&((*A)->fd));
}


Noeud* suppression(Arbre *A, char * mot){
    Noeud *max, *temp;
    if(*A == NULL)
        return *A;
    int comp = strcmp((*A)->mot, mot);
    if(comp > 0)
        return suppression(&((*A)->fg), mot);
    if(comp < 0)
        return suppression(&((*A)->fd), mot);

    temp = *A; 
    if(((*A)->fg == NULL) && ((*A)->fd == NULL)){ //aucun fils
        *A = NULL;
    }
    else if((*A)->fd == NULL){ //on a seulement le fils gauche
        *A = (*A)->fg;
    }
    else if((*A)->fg == NULL){ //on a seulement le fils droit
        *A = (*A)->fd; 
    }
    else{ //on a deux fils
        max = extrait_max(&((*A)->fg));
        max->fg = (*A)->fg;
        max->fd = (*A)->fd;
        *A = max;
    }
    return temp;
}


void libere(Arbre* A){
    if(*A != NULL){
        libere(&(*A)->fg);
        libere(&(*A)->fd);
        free((*A)->mot);
        free(*A);
    }
}


void dessine(char * nom, Arbre A){
    int len = 100;
    char cmd[len];
    char evince[len];
    char pdf[len];
    FILE *out;
    sprintf(pdf, "%s.pdf", nom);
    out = fopen("visualise.dot", "w");
    if(out == NULL){
        fprintf(stderr, "Erreur d'ouverture du fichier\n");
        return;
    }

    cree_dot(out, A);
    fclose(out);
    sprintf(evince, "evince %s &", pdf);
    sprintf(cmd, "dot -Tpdf visualise.dot -o %s", pdf);
    if(system(cmd)){
        fprintf(stderr, "Erreur avec la commande sytem arret\n");
        return;
    }
    system(evince);
}


int cree_arbre(char * nom, Arbre *A){
    FILE * fichier;
    char buffer[TAILLE_MAX];

    fichier = fopen(nom, "r");
    
    if(fichier == NULL) {return 0;} /* fichier non trouvé on arrête la fonction*/
    
    while(fgets(buffer, TAILLE_MAX, fichier) != NULL){
        char *token = strtok(buffer, " \n,;:.?!\"()-'");
        while(token){
            ajout(A, token);            
            token = strtok(NULL, " \n,;:.?!\"()-'");
        }
        free(token);
    }
    fclose(fichier);
    return 1;
}


/* les fonctions rajoutés pour utiliser dot*/

void ecrireDebut(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "\tnode [shape=record , height=.1 ]\n");
    fprintf(f,"\tedge [tailclip=false , arrowtail = dot , dir=both];\n");

}


void ecrireArbre(FILE *f, Arbre a){
    if(a != NULL){
        fprintf(f, "n%p [label=\"<gauche> | <valeur> %s | <droit>\"];\n", (void *)a, a->mot);
        if (a ->fg != NULL){
            fprintf(f, "n%p:gauche:c -> n%p:valeur;\n", (void *)a, (void *)a->fg);
            ecrireArbre(f, a ->fg);
        }
        if (a ->fd != NULL){
            fprintf(f, "n%p:droit:c -> n%p:valeur;", (void *)a, (void *)a ->fd);
                ecrireArbre(f, a->fd);
        }
    }
}


void ecrireFin(FILE *f){
    fprintf(f,"}");

}


void cree_dot(FILE * out, Arbre A){
    ecrireDebut(out);
    ecrireArbre(out, A);
    ecrireFin(out);
}
