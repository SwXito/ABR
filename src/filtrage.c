#include "ABR.h"

/**
 * @brief Fonction qui filtre les élément présent dans *A et filtre et supprime dans A les mots en commun
 * et les ajoutes dans utilises
 * 
 * @param A 
 * @param filtre 
 * @param utilises 
 * @return int 
 */
int filtres(Arbre * A, Arbre filtre, Arbre * utilises){
    Arbre tmp;

    if(*A == NULL) {return 0;}

    /* cas d'arrêt de la fonction récursive */
    if(filtre != NULL){
        tmp = suppression(A, filtre->mot);

        /* on vérifie l'adresse du noeud pour pouvoir l'ajouter */
        if(tmp != NULL){
            ajout(utilises, filtre->mot);
            free(tmp->mot);
            free(tmp);
            
        }
        filtres(A, filtre->fg, utilises);
        filtres(A, filtre->fd, utilises);
    }
    return 1;
}

int main(int argc, char* argv[]){
    Arbre texte = NULL, filtre = NULL, utilises = NULL;
    int pdf = 0; /* un booléen pour savoir si on réalise un pdf des arbre */
    char fichier1[100] = "ressources/", fichier2[100] = "ressources/"; /* pour pouvor accéder au fichier dans ressources*/

    if(argc < 3){
        fprintf(stderr, "veuillez renseigner les fichiers demandés\n");
        return -1;
    }

    if(argc == 3){
        if(!cree_arbre(strcat(fichier1, argv[1]), &texte)){
            fprintf(stderr, "le premier fichier donné n'est pas utilisable ou non trouvé\n");
            return -1;
            }
        if(!cree_arbre(strcat(fichier2, argv[2]), &filtre)) {
            fprintf(stderr, "le deuxième fichier donné n'est pas utilisable ou non trouvé\n");
            return -1;
            }
    }

    if(argc == 4){
        if(argv[1][0] == '-' && argv[1][1] == 'v') {pdf++;}
        if(!cree_arbre(strcat(fichier1, argv[2]), &texte)) {
            fprintf(stderr, "le premier fichier donné n'est pas utilisable ou non trouvé\n");
            return -1;
        }
        if(!cree_arbre(strcat(fichier2, argv[3]), &filtre)) {
            fprintf(stderr, "le deuxième fichier donné n'est pas utilisable ou non trouvé\n");
            return -1;
        }
        dessine("texte", texte);
        dessine("filtre", filtre);
    }
    
    if(!filtres(&texte, filtre, &utilises)){
        fprintf(stderr, "Erreur du filtrage du texte\n");
        return -1;
    }

    printf("Mots présents uniquement dans le texte de référence :\n");
    printf("-----------------------------------------------------\n");
    parcours_infixe(texte);

    printf("\nMots présents dans les deux textes :\n");
    printf("------------------------------------\n");
    parcours_infixe(utilises);

    if(pdf){
        dessine("filtrage", texte);
        dessine("en_commun", utilises);    
    }

    libere(&texte);
    libere(&filtre);
    libere(&utilises);
    return 0;
}
