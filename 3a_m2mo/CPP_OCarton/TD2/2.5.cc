#include <iostream>

double FiboIter(long long n) {

  //Initialisation nécessaire en itératif, ce sont les termes de départ qu'on va mettre à jour

    if (n < 0) {
        return 0;
    }

    if (n == 0 || n == 1) {
        return 1;
    }

    double Fn;
    double F0 = 1;
    double F1 = 1;

    for (long long i = 2; i <= n; i++) { //Actualisation des termes précédant celui qu'on calcule. 
        Fn = F0 + F1;
        F0 = F1;
        F1 = Fn;
    }
    return Fn;
}
//A la différence de sa contrepartie récursive, ce programme tourne instantanément pour des valeurs de n même grandes 
//C'est normal, les opérations sont très simples et on utilise très peu d'espace mémoire pour les calculs (3 long long)
// Une sortie en particulier :
//Methode iterative : Fibonacci terme numero1000 = 9079565065540428013
//Temps d'execution : 0 secondes