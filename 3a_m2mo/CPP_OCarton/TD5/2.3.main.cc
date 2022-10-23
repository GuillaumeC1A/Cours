#include <cstdlib>
#include <iostream>
using namespace std;

#include "2.3.h"

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  const int num = 1000000;
  Pixel* const pixels_mutable = new Pixel[num];
  const Pixel* const pixels = pixels_mutable;
  ResetPixel(&pixels_mutable[0]);
  PrintPixel(&pixels_mutable[0]);
  const PixelArray p(num, pixels);
  int s = 0;
  for (int i = 0; i < num; ++i) {
    s += p.GetPixel(i)->GetX();
  }
  cout << "Hello world: " << s << endl;
}
