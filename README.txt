TWARDAWA Yanis, TOUATI Damien Groupe 8 TP Algo des arbres

Présentation:
    Le programme suivant permet de réaliser des arbres binaires de recherches contenant des mots pour permettre le filtrage d'un texte et de déterminer les mot présents dans les deux textes.


Avertissement: 
    Si vous souhaitez utiliser toutes les fonctionnalités du programme télécherger l'outil dot  à l'adresse suivante : https://graphviz.org/about/


Compilation:
    Voici les options de compilations disponible pour le programme:
        - make pour compiler le programme
        - make clean pour supprimer tout les fichiers .o présent
        - make mrproper pour effacer tout les fichiers créés .pdf .dot .o et l'éxécutable

Utilisation du programme:
    Lorsque que la compilation est réalisé vous avez la possibilités d'utilser les commandes suivantes:
        - ./filtrage texte.txt filtre.txt qui affiche sur le terminal les mots présents dans le fichier texte mais qui ne sont pas dans filtre, puis
            les mots présents simultanément dans les deux fichiers.
        
        - ./filtrage -v texte.txt filtre.txt qui comme pour la prémière commande avec comme ajout la création de fichier pdf contenant les choses suivantes:
            — l’arbre contenant les mots présents dans le fichier texte.
            — l’arbre contenant les mots présents dans le fichier filtre.
            — l’arbre contenant les mots présents dans texte, mais pas dans filtre.
            — l’arbre contenant les mots présents simultanément dans texte et filtre.
