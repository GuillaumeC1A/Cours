#include <iostream>
using namespace std;

void transpose(int n, int m, double* matrix) {
    
    //On peut voir une transposition comme une permutation (une bijection de n * m éléments vers eux-mêmes)
    //On va donc décomposer cette permutation en une suite de cycles :
    
    double tmp;                                 //Tampon de download (on télécharge la valeur suivante avant de l'écraser)
    double tmp2;                                //Tampon d'upload (qui écrase la valeur en k, téléchargée dans tmp1)

    //On a besoin de 2 tampons : sinon, lorsqu'on stocke matrix[k] dans tmp, on écrase matrix[k-1] avant d'avoir pu le copier (et inversement)
    
    int size = n*m;
    int* visited = new int[size];               //On crée un tableau de taille NxM de check de case.
    
    for (int i = 0; i < size; i++) {
        visited[i] = 0;                         //On initialise toutes les cases à 0 (non visitées)
    }

    for (int i = 0; i < size; i++) {

        if (visited[i] == 0) {                  //Si on n'a pas encore visité la case i (et les cases de son cycle)
            int j = i;
            tmp2 = matrix[j];
        
            while (visited[j] == 0) {           //Tant qu'on n'a pas visité la case (dans le cycle courant, i.e. pas encore fini)
                visited[j] = 1;                 //On la visite


                //L'idée est la suivante : A[i][j] = A[j][i] <=> A[i*m + j] = transpose(A)[j*n + i] avec j < m et i < n.
                //Le C permet d'écrire j/m pour avoir le quotient entier de la division par m.
                
                int k = (j%m)*n + j/m; 
                
                tmp = matrix[k];                //On stocke la valeur de la case suivante dans le tampon 1, (download dans tmp)
                matrix[k] = tmp2;               //On met la valeur de la case actuelle dans la case suivante (upload depuis tmp2)
                tmp2 = tmp;                     //Echange : tmp2 prend la nouvelle valeur à upload et on libère l'espace de download.

                j = k;                          //On passe à la case suivante
            } 
        }
    }
    delete[] visited; //On libère la mémoire
    //On ne retourne rien car la transposition était in place.
}