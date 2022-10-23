#include <iostream>
#include <time.h>
using namespace std;

#include "2.4.cc"
#include "2.5.cc"

int main() {
  cout << "Entrez un entier n: ";
  int n;
  cin >> n;

  //Fibonacci : PARTIE ITERATIVE (2.5.cc)
    clock_t t1 = clock();
    cout << "Methode iterative : Fibonacci terme numero" << n << " = " << FiboIter(n) << endl;
    clock_t t2 = clock();
    cout << "Temps d'execution : " << (t2 - t1) / (double) CLOCKS_PER_SEC << " secondes" << endl;

  //Fibonacci : PARTIE RECURSIVE (2.4.cc)
    clock_t t3 = clock();
    cout << "Methode recursive : Fibonacci terme numero" << n << " = " << FiboRec(n) << endl;
    clock_t t4 = clock();
    cout << "Temps d'execution : " << (t4 - t3) / (double) CLOCKS_PER_SEC << " secondes" << endl;
} 