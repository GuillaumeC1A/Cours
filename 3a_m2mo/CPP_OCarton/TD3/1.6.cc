int HIndex(int num_articles, const int* num_citations) {
    long long min = 0;              //Ce sont ces indices qui peuvent être très grands (cf énoncé) donc je prends des long long. 
    long long max = 0;              //La raison derrière cela : MAX_INT - MIN_INT = dépassement mémoire du int.
    for (int i = 0; i < num_articles; i++) {
        if (num_citations[i] > max) {
            max = num_citations[i];
        }
        if (num_citations[i] < min) {
            min = num_citations[i];
        }
    }
    //On calcule d'abord les min et max des citations pour avoir la bonne taille de notre tableau des occurences. 
    //J'avais remarqué dans mes codes précédents que j'avais des segfaults, avec cette init et les long long ça marche.

    int* occurences = new int[max - min + 1];    //Les valeurs contenues ne sont pas si grandes, c'est la taille du tableau qui l'est.
    for (long long i = 0; i < max - min + 1; i++) { 
        occurences[i] = 0;
    }

    for (int i = 0; i < num_articles; i++) {     //Première étape du tri inversé : occ[i] contient le nombre de i-citations. 
        occurences[max - (long long)num_citations[i]]++;  
    }

    //Pour l'instant notre tableau occurences contient des 'négatifs' et est de taille bien trop grande (pour les performances)
    //Notre h-index étant toujours plus bas que num_articles, les valeurs trop hautes peuvent être en fin de tableau (num_articles).
    
    int* occurences2 = new int[num_articles];    //On crée un nouveau tableau de taille num_ar
    int total = 0;                               //Nombre d'articles traités / numéro d'article en cours.
    
    for(long long i = 0; i < max - min + 1; i++) { 
        if(occurences[i] != 0) {                          //S'il y a des articles à ce nombre de citations
            for (int j = 0; j < occurences[i]; j++) {     //Tant qu'il en reste, on les ajoute dans l'ordre
                occurences2[total] = int(max) - i;        //En i la citation courant est à max-i occurences. Et le h-index est un int.
                total++;                                  //On se déplace de numéro d'articles (article courant).
            }                          
        }
    }
    
    //occurences2 contient maintenant le nombre de citations par article dans l'ordre décroissant, ce qu'on voulait. 
    //On cherche maintenant juste le h-index (qui, encore une fois, est borné par num_citations, un int).

    int hindex = 0;
    for(int i = 0; i < num_articles; i++) {
        if(occurences2[i] >= i+1) { //On cherche le premier h tel que occurences2[h] < h. (L'égalité est autorisée pour le hindex)
            hindex++;               //Pour rappel, occurences[i] contenait le nombre d'articles de citation i,
        }                           //Alors occurences2[i] contient le nombre de citations de l'article i (rangés en décroissant).
    }

    delete[] occurences;
    delete[] occurences2;
    return hindex; //Si on a pas trouvé de h-index, on renvoie num_articles.
}