#include <iostream>

long long FactorielleMod2(long long n) {
    if (n < 0) {
        return 0;
    }
    
    long long resultat = 1;

    for (long long i = 1; i <= n; i++) {
        resultat = (resultat * i) % 1000000007;
    }    
    return resultat % 1000000007;
} //Celui-ci arrive à s'exécuter sans problème, en un temps correct. 
//On trouve en particulier que 10 000 000! mod 1000000007 = 682498929, en environ 2 secondes. 