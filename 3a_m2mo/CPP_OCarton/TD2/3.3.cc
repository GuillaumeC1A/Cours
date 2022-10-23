#include <iostream>
#include "3.2.cc"

int main(int, char** argv) {
  Strip(argv[1]);  //Comme Strip est un void, on l'utilise d'abord pour modifier notre chaîne, et ENSUITE on voit son effet.
  cout << argv[1] << endl;
}
