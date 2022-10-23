#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "1.6.cc"

int HIndexRef(const vector<int>& data) {
  const int n = data.size();
  int* count = new int[n + 1]();
  for (int i : data) count[std::max(0, std::min(n, i))]++;
  int s = 0;
  for (int i = n; i >= 0; --i) if ((s += count[i]) >= i) return i;
  return -1;
}

int main() {
  const int n = 1<<25;
  vector<int> data(n);
  int seed = 12345;
  srandom(0);
  for (int i = 0; i < n; ++i) {
    data[i] = seed;
    seed += 7893 + seed;
    if (seed > n) seed %= n;
    if ((i & 0xFFF) == 0) seed = random();
  }
  const int href = HIndexRef(data);
  const int h = HIndex(n, data.data());
  cout << "href : " << href << endl;
  cout << "h obtenu : " << h << endl;
  if (h == href) {
    cout << "PASSED performance test!\n";
  } else {
    cout << "ERROR: failed correctness test..\n";
  }
}
