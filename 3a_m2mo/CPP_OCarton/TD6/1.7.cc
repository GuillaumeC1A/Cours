#include <iostream>
#include <cstring>
#include <math.h>
#include "1.7.h"

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


Uint2048 Uint2048::operator-(const Uint2048& other) const { //Fonction basée sur l'astuce, le complément à 2.
  Uint2048 result;
  Uint2048 otherComplement = other;
  for (int i = 0; i < 32; ++i) {
    otherComplement.u_[i] = ~other.u_[i]; //l'opérateur ~ est le complément à 2 : ~x = 1-x. (non bit à bit)
  }
  result = *this + otherComplement + Uint2048(1); //En utilisant le + précédent, nbr + (complément + 1) = nbr - other !
  return result; //Attention à bien utiliser Uint2048(1) pour utiliser l'arithmétique définie, 1 tout court n'est pas un Uint2048.
 }


Uint2048 Uint2048::operator*(const Uint2048& other) const { //Méthode tirée de wikipedia, la votre ne fonctionne pas... (cf mail) 
//https://fr.wikipedia.org/wiki/Technique_de_multiplication_dite_russe

  Uint2048 result = Uint2048(0);
  Uint2048 a = *this;
  Uint2048 b = other;
  while(Uint2048(0) < a) {     
    if (a.u_[0] % 2 == 1) { //si nombre à mult est impair. Le bit de poids faible du Uint2048 est le même que celui du premier uint64.
      result = result + b;
    }
    //Multiplication par 2 binaire (décalage de bits à gauche). On pourrait définir l'opérateur >> pour Uint2048.
    for(int i = 31; i > 0; i--) {
      b.u_[i] = (b.u_[i] << 1);
      if(b.u_[i-1] & 0x8000000000000000) { //si le bit de poids fort du uint64 précédent est à 1.
        b.u_[i] += 1;
      }
    }
    b.u_[0] = b.u_[0] << 1; 
    
    //A nouveau l'operateur >> de décalage bitwise. Division par 2 écrasant le bit de poids faible. 
    for(int i = 0; i < 31; i++) {
      a.u_[i] = a.u_[i] >> 1;
      if(a.u_[i+1] & 0x1) { //si le bit de poids faible du uint64 suivant est à 1.
        a.u_[i] += 0x8000000000000000;
      }
    }
    a.u_[31] = a.u_[31] >> 1;
  }
  return result;
}

bool Uint2048::operator==(const Uint2048& other) const { //Opérateur d'égalité Uint2048, pratique, j'aurais dû le rajouter avant.
  for(int i = 0; i < 32; i++) {
    if(u_[i] != other.u_[i]) {
      return false;
    }
  }
  return true;
}

Uint2048 Uint2048::operator/(const Uint2048& other) const { //Division 'papier' - chaque etape soustrait le plus possible le diviseur.
    if(other == Uint2048(0)) {
      //On pourrait lancer une exception : throw std::invalid_argument("Division par 0");
      cout << "Division par 0, exit" << endl;
      return Uint2048(0);
    }
    Uint2048 quot = Uint2048(0);
    Uint2048 rest = Uint2048(0);
    //La long division originale abaisse les bits un par un. Je vais coder une variante, qui abaisse les bits par blocs de 64.
    //Et donc avant d'abaisser un nouveau bloc, on doit deplacer notre quotient et reste de 64 bits vers la gauche.
    for(int j = 2047; j >= 0; j--) {
        for(int i = 31; i > 0; i--) { //Decalage de 1 a gauche
            rest.u_[i] = (rest.u_[i] << 1);
            if(rest.u_[i-1] & 0x8000000000000000) { //si le bit de poids fort du uint64 précédent est à 1.
                rest.u_[i] += 1;
            }
        }
        rest.u_[0] = (rest.u_[0] << 1); 

        //Subtilite : on doit ajouter le bit de poids faible du Uint2048 au reste. j = 64*i + j avec i = 'j'/64 le bloc, 'j'%64 la pos.
        if(u_[j/64] & ((uint64) 0x1 << (j%64))) {  //0x1 << (j%64) est un masque : le bit à 1 est à la position j%64. 
            rest.u_[0] += 1;
        }

        if(other < rest || other == rest) { //Soustraction du diviseur sur le reste.
            rest = rest - other;
            quot.u_[j/64] += ((uint64) 0x1 << (j%64)); //On ajoute le bit de poids faible du Uint2048 au quotient.
        }  
    }
    //Le reste est perdu.
    return quot;
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

/* ----------------- METHODE TROP LENTE PAR ABAISSEMENT DE BLOCS 64 BITS

Uint2048 Uint2048::operator/(const Uint2048& other) const { //Division 'papier' - chaque etape soustrait le plus possible le diviseur.
    if(other == Uint2048(0)) {
      //On pourrait lancer une exception : throw std::invalid_argument("Division par 0");
      cout << "Division par 0, exit" << endl;
      return Uint2048(0);
    }
    Uint2048 quot = Uint2048(0);
    Uint2048 rest = Uint2048(0);
    //La long division originale abaisse les bits un par un. Je vais coder une variante, qui abaisse les bits par blocs de 64.
    //Et donc avant d'abaisser un nouveau bloc, on doit deplacer notre quotient et reste de 64 bits vers la gauche.
    for(int j = 31; j >= 0; j--) {
        for(int i = 31; i > 0; i--) { //Abaissement d'un bloc de 64 bits.
            rest.u_[i] = rest.u_[i-1];
        }
        rest.u_[0] = u_[j];
        while(other < rest || other == rest) { //Soustraction du diviseur sur le reste.
            rest = rest - other;
            quot.u_[j] = quot.u_[j] + 1;
        }
    }

    //Le reste est perdu.
    return quot;
} 

*/