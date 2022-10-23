// J'ai une erreur de compilateur 980711 que je n'arrive pas à résoudre, aucune documentation sur internet...
// SOLUCE : apt-get upgrade g++ (cela n'a pas upgrade g++ mais l'ensemble d'ubuntu et probablement vérifié l'intégrité de g++)
#include "1.4.cc"

int HIndex(int num_articles, const int* num_citations) { //num_citations contient les 'num_articles' citations de chaque article
  int h = 0;
  int* sorted = SortRev(num_articles, num_citations); //On trie simplement ce tableau dans l'ordre décroissant avec notre SortRev.

  while (h < num_articles && sorted[h] > h) { //Une fois trié, on parcourt le tableau jusqu'à un h tel que sorted[h] <= h.
    h++;
  }

  delete[] sorted; //Application du cours - on libère la mémoire. 
  return h; 
}