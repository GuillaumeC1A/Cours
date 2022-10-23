#include <cstdlib>
#include <iostream>
using namespace std;

#include "2.1.h"

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  Pixel q;
  Pixel p(3, 4, 0xffaa77);
  CHECK(p.GetX() == 3);  
  CHECK(p.GetY() == 4);
  CHECK(p.GetColor() == 0xffaa77);
  p.SetX(5);
  p.SetY(-8);
  CHECK(p.GetX() == 5);
  CHECK(p.GetY() == -8);
  CHECK(p.GetColor() == 0xffaa77);
  return 0;
}
