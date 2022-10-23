#include <ctime>
#include <iostream>
#include "1.4.h"
using namespace std;

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  Uint2048 x(1);
  Uint2048 y(1);
  for (int i = 0; i < 123; ++i) {
    x = x + y;
    y = x + y;
  }
  cout << Uint2048::NumAdditions() << endl;
  CHECK(Uint2048::NumAdditions() == 246);
}
