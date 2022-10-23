#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
#include "2.6.cc"
#define CHECK_EQ(x, y) do{ if((x)==(y))cout<<"Test of '" #x "' PASSED!\n";else{cout<<"Test of '" #x "' FAILED. Stopping.\n";exit(1);} }while(false)
int main() {
  // The first 'mandatory' test.
  CHECK_EQ(Pgcd(2250, 1000), 250);
  // More basic tests.
  CHECK_EQ(Pgcd(16, 12), 4);
  CHECK_EQ(Pgcd(12, 1), 1);
  CHECK_EQ(Pgcd(122, 105), 1);
  CHECK_EQ(Pgcd(122, 56), 2);
  // When a < b, should still work fine.
  CHECK_EQ(Pgcd(1000, 2250), 250);
  CHECK_EQ(Pgcd(12, 20), 4);
  CHECK_EQ(Pgcd(1, 12), 1);
  CHECK_EQ(Pgcd(3, 5), 1);
  // Stress test with large numbers. Should work, and be still quick.
  CHECK_EQ(Pgcd(129387194869817412L, 19827398170419240L), 12);
  CHECK_EQ(Pgcd(1000000007, 1), 1);
  // More large numbers, not mentioned in the exercise text.
  CHECK_EQ(Pgcd(1, 1000000007), 1);
  CHECK_EQ(Pgcd(4000000044000000121, 1), 1);
  CHECK_EQ(Pgcd(1, 4000000044000000121), 1);
  CHECK_EQ(Pgcd(4000000044000000121, 1000000014000000049), 1);
  CHECK_EQ(Pgcd(1000000014000000049, 4000000044000000121), 1);
  // Corner case: with 0
  CHECK_EQ(Pgcd(17, 0), 17);
  CHECK_EQ(Pgcd(0, 17), 17);
  CHECK_EQ(Pgcd(987654321, 0), 987654321);
  CHECK_EQ(Pgcd(0, 987654321), 987654321);
  CHECK_EQ(Pgcd(1, 0), 1);
  cerr << "Success! All tests passed.\n";
}
