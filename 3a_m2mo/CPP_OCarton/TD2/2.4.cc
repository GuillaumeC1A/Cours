#include <iostream>

long long FiboRec(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    return FiboRec(n - 1) + FiboRec(n - 2);
}

//Lorsqu'on lance pour des petites valeurs, ça va. Pour n = 60, le programme tourne dans le vide, il y a overflow. 
//Fibonacci est exponentielle, alors en récursif, l'explosion de temps de calcul est visible. 