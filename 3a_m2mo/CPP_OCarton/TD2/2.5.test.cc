#include <iostream>
#include <cmath>
using namespace std;
#include "2.5.cc"
int main() {
  const double x = FiboIter(1000);
  if (std::min(std::abs(x - 4.3466557686937427e+208),
               std::abs(x - 1.1379692539836020e+209)) < 1e197) {
    cout << "PASSED but with an off-by-one error\n";
    return 0;
  }
  if (std::abs(x - 7.0330367711422765e+208) < 1e196) {
    cout << "PASSED!\nPASSED!\n";
    return 0;
  }
  if (std::abs(x - 7.0330367711422765e+208) < 1e202) {
    cout << "PASSED but with inferior precision. Did you use doubles?\n";
    return 0;
  }
  cerr << "FAILED!\n";
}
