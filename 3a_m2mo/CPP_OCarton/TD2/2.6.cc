#include <iostream>

long Pgcd0(long a, long b) { //Version recursive lente

  long result;
  if(a==b) return a;
  if(a>b) return Pgcd0(a-b,b);
  return Pgcd0(a,b-a);
}

long Pgcd(long a, long b) { //Version recursive rapide
    if(a == b) return a;

    if(b == 0) return a;
    if(a == 0) return b;
    
    if(b>a) {
        long t = a;
        a = b;
        b = t;
    }

    return Pgcd(b, a%b);
}

//Ce programme NE FINIT PAS dans sa version récursive initiale, 
//Mais l'algorithme d'Euclide permet de traiter des nombres très grands rapidement.