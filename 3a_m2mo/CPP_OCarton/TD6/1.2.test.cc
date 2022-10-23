#include <iostream>
#include "1.2.h"
using namespace std;

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  // Very simple tests.
  Uint2048 one(1);
  Uint2048 two(2);
  Uint2048 three(3);
  CHECK(one < two);
  CHECK(one < three);
  CHECK(two < three);
  CHECK(!(two < one));
  CHECK(!(three < one));
  CHECK(!(three < two));
  CHECK(!(one < one));
  CHECK(!(two < two));
  CHECK(!(three < three));

  // A bit more complex: compare 2^64 with 2^64-1.
  Uint2048 x(1);
  Uint2048 y(1);
  for (int i = 0; i < 63; ++i) {
    x = x + x;
    y = y + y + one;
  }
  x = x + x;
  CHECK(one < x);  // x = 2^64
  CHECK(y < x);    // x = 2^64, y = 2^64 - 1
  CHECK(!(x < y));
  CHECK(!(x < x));
  CHECK(!(y < y));

  // More complex test.
  x = one;
  y = Uint2048(0);
  Uint2048 a(124876214);
  Uint2048 b = a;
  for (int i = 0; i < 2000; ++i) {
    a = a + a;
    b = b + b;
    if (i == 1000) { b = b + one; }
    x = x + x;
    y = y + y + one;
  }
  Uint2048 z = x + one;
  // x = 2^2000; z = x+1; y = x-1;
  CHECK(x < z);
  CHECK(y < x);
  CHECK(x < z);
  CHECK(!(z < x));
  CHECK(!(z < y));
  CHECK(!(x < y));
  CHECK(!(x < x));
  CHECK(!(y < y));
  CHECK(!(z < z));

  // b has one bit set to '1' that a has to 0. So b > a.
  CHECK(a < b);
  CHECK(!(b < a));
  CHECK(a + one < b);
}
