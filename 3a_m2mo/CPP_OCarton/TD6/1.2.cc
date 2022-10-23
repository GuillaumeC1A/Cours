#include <iostream>

#include "1.2.h"

using namespace std;

//Constructeurs (1.1) :
Uint2048::Uint2048() { //Constructeur par défaut - initialisation à 0.
  for (int i = 0; i < 32; i++) {
    u_[i] = 0;
  }
}

Uint2048::Uint2048(int x) { //Constructeur à partir d'un entier.
  for (int i = 0; i < 32; i++) {
    u_[i] = 0;
  }
  u_[0] = x; //Uint2048 est 64 entiers de 32 bits, int x est un entier de 32 bits ->'dans les unités', i.e. au début du tableau.
}

bool Uint2048::operator<(Uint2048 other) { //Ce test ne fonctionne que si les nombres traités sont bien positifs (pas de bit de signe)
  for(int i = 31; i >=0; i--) { //on commence par les couches supérieures (dernières) car ce sont les nombres les plus grands
    if(u_[i] < other.u_[i]) { //Dès qu'un des nombres de la base int64 est plus petit, on peut conclure que le nombre est plus petit.
      return true;
    }
    else if(u_[i] > other.u_[i]) { //idem dans l'autre sens. On considère que le cas d'égalité est le plus rare. 
      return false;
    }
  }
  return false; //Si toutes les unités de la base sont égales, il y a égalité totale. DONC l'inégalité stricte est violée. 
}

Uint2048 Uint2048::operator+(Uint2048 other) {
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

void Uint2048::Print() {
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
