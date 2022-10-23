#include <iostream>

#include "1.4.h"

using namespace std;

//Constructeurs (1.1) :
Uint2048::Uint2048() { //Constructeur par défaut - initialisation à 0.
  for (int i = 0; i < 32; i++) {
    u_[i] = 0;
  }
}

int Uint2048::numAdd=0;

Uint2048::Uint2048(const int& x):Uint2048() { //Nouvelle syntaxe proche des constructeurs par délégation, on réutilise le constructeur par défaut.
  u_[0] = x; 
}

int Uint2048::NumAdditions() { 
  //Pas besoin de spécifier à nouveau static ici. Le compilateur sait déjà qu'elle est static avec le header.
  //En C++, static dans une fonction membre / variable fait bien ce qu'on veut,
  //mais ici static signifierait autre chose : une fonction propre uniquement au fichier, et c++ ne l'autorise pas. 
  return numAdd;
}

bool Uint2048::operator<(const Uint2048& other) const { 
  for(int i = 31; i >=0; i--) { 
    if(u_[i] < other.u_[i]) { 
      return true;
    }
    else if(u_[i] > other.u_[i]) { //idem dans l'autre sens. On considère que le cas d'égalité est le plus rare. 
      return false;
    }
  }
  return false; //Si toutes les unités de la base sont égales, il y a égalité totale. DONC l'inégalité stricte est violée. 
}

Uint2048 Uint2048::operator+(const Uint2048& other) const { //idem, read-only, la valeur est retournée mais les appelés ne sont pas modifiés.
  //Comme on vient de faire appel à operator +, on incrémente notre compteur d'additions static de 1.
  numAdd++;
  Uint2048 result;
  uint64 carry = 0;
  for (int i = 0; i < 32; ++i) {
    result.u_[i] = u_[i] + other.u_[i] + carry;
    // Detect overflows, which indicate that there should be a carry.
    // It's not that simple!
    if ((carry == 0 && result.u_[i] < u_[i]) ||
        (carry == 1 && result.u_[i] <= other.u_[i])) {
      carry = 1;
    } else {
      carry = 0;
    }
  }
  // The last carry is lost.
  return result;
}

void Uint2048::Print() const {  //idem, read-only
  // The difficulty is to print the number in base 10.
  // First, precompute *all* the powers of 10 that are smaller or equal to x.
  // Since 2^2048 ~= 10^616.5, we need up to 617 powers: 10^0...10^616.
  int p = 0;
  Uint2048 cur(1);  // 10^p
  Uint2048 p10[617];  // p10[i] will be equal to 10^i.
  p10[0] = cur;
  while (p < 616 && !(*this < cur)) {
    // Simple way of computing p10 * 10 with few additions.
    Uint2048 tmp2 = cur + cur;
    Uint2048 tmp4 = tmp2 + tmp2;
    Uint2048 tmp8 = tmp4 + tmp4;
    cur = tmp8 + tmp2;
    p++;
    p10[p] = cur;
  }

  // Now, compute the digits in base 10, one by ones.
  Uint2048 s(0);
  if (p > 0) --p;
  while (p >= 0) {
    int d;  // Declared outside the "for" loop to keep its value after it's done
    for (d = 0; d < 10; ++d) {
      Uint2048 t = s + p10[p];
      if (*this < t) break;
      s = t;
    }
    cout << d;
    p--;
  }
}
