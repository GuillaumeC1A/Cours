#include <iostream>
using namespace std;
#include "2.4.cc"
int main() {
  switch (FiboRec(31)) {
    case 1346269:
    case 3524578:
      cout << "PASSED but with an off-by-one error\n";
      return 0;
    case 2178309:
      cout << "PASSED!\nPASSED!\n";
      return 0;
  }
  cerr << "FAILED!\n";
}
