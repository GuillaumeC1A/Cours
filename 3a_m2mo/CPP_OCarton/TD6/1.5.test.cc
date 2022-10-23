#include <ctime>
#include <iostream>
#include "1.5.h"
using namespace std;

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  // Simple test with ints.
  Uint2048 x(123681124);
  Uint2048 y(987123199);
  Uint2048 z = y - x;
  Uint2048 z_ref(987123199 - 123681124);
  if (z < z_ref || z_ref < z) {
    cout << "FAILED! When computing the following subtraction:\n";
    y.Print();
    cout << " -\n";
    x.Print();
    cout << "\nGot this: ";
    z.Print();
    cout << "\nExpected: ";
    z_ref.Print();
    return 1;
  }
  cout << "PASSED test #1\n";

  // Randomized test.
  x = Uint2048(0);
  y = Uint2048(0);
  Uint2048 p(1);
  for (int i = 0; i < 2047; ++i) {
    if (random()%2) x = x + p;
    if (random()%2) y = y + p;
    p = p + p;
  }
  z = x + y;
  Uint2048 d = z - y;  // Should be "x"
  if (d < x || x < d) {
    cout << "FAILED! When computing the following subtraction:\n";
    z.Print();
    cout << " -\n";
    y.Print();
    cout << "\nGot this: ";
    d.Print();
    cout << "\nExpected: ";
    x.Print();
    return 1;
  }
  cout << "PASSED test #2\n";
  cout << "Note: the performance tests weren't ran. If your code is slow, this test won't detect it.\n";
}
