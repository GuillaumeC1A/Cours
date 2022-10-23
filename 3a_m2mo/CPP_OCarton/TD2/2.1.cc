#include <iostream>

long long FactorielleMod(long long n) { //On doit prendre des long long au vu de la taille des nombres demandés
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return (n * FactorielleMod(n - 1)) % 1000000007;
}

//Pour n = 10000000 en récursif, le programme ne finit pas de s'exécuter, on va donc utiliser une boucle for. (stackoverflow)