#include <iostream>
using namespace std;
  
// Ne touchez pas à cette fonction! Utilisez-là telle qu'elle est.
void GetDate(int* year, int* month, int* day) {
  *year = 7654;
  *month = 11;
  *day = 22;
}
  
int main() {
  int y;
  int m;
  int d;
  GetDate(&y,&m,&d);
  
  // Affichage de la date.
  cout << y << "-" << m << "-" << d << endl;
}