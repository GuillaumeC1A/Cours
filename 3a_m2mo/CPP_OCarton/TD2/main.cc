#include <iostream>
#include <time.h>
using namespace std;

#include "2.1.cc"
#include "2.2.cc"

int main() {
  cout << "Entrez un entier n: ";
  int n;
  cin >> n;

  //Partie test de sommes de factorielles : PARTIE ITERATIVE (2.2.cc)
    clock_t t1 = clock();
    long long resultat = 0;
    for (int i = 1; i <= n; i++) {
        resultat = (resultat + FactorielleMod2(i)) % 1000000007;
    }
    cout << "Methode iterative : Somme des factorielles de 1 a " << n << " = " << resultat << endl;
    clock_t t2 = clock();
    cout << "Temps d'execution : " << (t2 - t1) / (double) CLOCKS_PER_SEC << " secondes" << endl;

  //Partie test de sommes de factorielles : PARTIE RECURSIVE (2.1.cc)
    clock_t t3 = clock();
    long long resultat2 = 0;
    for (int i = 1; i <= n; i++) {
        resultat2 = (resultat2 + FactorielleMod(i)) % 1000000007;
    }
    cout << "Methode recursive : Somme des factorielles de 1 a " << n << " = " << resultat2 << endl;
    clock_t t4 = clock();
    cout << "Temps d'execution : " << (t4 - t3) / (double) CLOCKS_PER_SEC << " secondes" << endl;
} 
//Exemple de sortie -
//Entrez un entier n: 10000
//Methode iterative : Somme des factorielles de 1 a 10000 = 396626132
//Temps d'execution : 2.109 secondes
//Methode recursive : Somme des factorielles de 1 a 10000 = 396626132
//Temps d'execution : 2.422 secondes