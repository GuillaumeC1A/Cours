#include <ctime>
#include <iostream>
#include "1.3.h"
using namespace std;

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  // Test des const.
  cout << "Testing 'const'..." << endl;
  const Uint2048 aa(12);
  const Uint2048 bb(12);
  cout << "A="; aa.Print(); cout << "\n";
  cout << "B="; bb.Print(); cout << "\n";
  Uint2048 cc = aa + bb;
  cout << "A+B="; cc.Print(); cout << "\n";
  const bool b = aa < bb;
  cout << "A " << (b ? "<" : ">=") << " B\n";

  // Test de perf et de correctness.
  cout << endl;
  cout << "Testing the performance of operator< ..." << endl;
  Uint2048 p1[2048];
  Uint2048 p2[2048];
  Uint2048 p3[2048];
  Uint2048 one(1);
  Uint2048 x1(12376781);
  Uint2048 x2 = x1 + one;
  for (int i = 0; i < 2048; ++i) {
    p1[i] = x1;
    p2[i] = x2;
    p3[i] = x2 + one;
    x2 = x2 + x2;
    x1 = x1 + x1 + one;
  }
  const clock_t c0 = clock();
  for (int i = 0; i < 2010; ++i) {
    for (int ki = 1; ki <= 3; ++ki) {
      const Uint2048& ii = ki == 1 ? p1[i] : ki == 2 ? p2[i] : p3[i];
      for (int j = 0; j < 2010; ++j) {
        for (int kj = 1; kj <= 3; ++kj) {
          const Uint2048& jj = kj == 1 ? p1[j] : kj == 2 ? p2[j] : p3[j];
          const bool is_inf = ii < jj;
          if (is_inf != (i*3+ki < j*3+kj)) {
            cout << "Unexpected comparison result (got " << (is_inf ? "<" : ">")
                 << ", expected the other) with:\n";
            ii.Print();
            cout << " VS\n";
            jj.Print();
            cout << "\n";
            CHECK(false);
          }
        }
      }
    }
  }
  const clock_t c1 = clock();
  cout << "Time: " << double(c1 - c0) / CLOCKS_PER_SEC << " s" << endl;
}
