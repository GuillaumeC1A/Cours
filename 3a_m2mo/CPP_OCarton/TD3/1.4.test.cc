#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "1.4.cc"

string PrintVector(const vector<int>& v) {
  if (v.empty()) return "[]";
  stringstream ss;
  ss << "[" << v[0];
  for (int i = 1; i < v.size(); ++i) ss << ", " << v[i];
  ss << "]";
  return ss.str();
}

bool Test(vector<int> data) {
  const int n = data.size();
  const vector<int> d2 = data;
  int* p3 = SortRev(n, d2.data());
  if (d2 != data) {
    cout << "ERROR: your code modifies the input vector!\n";
    return false;
  }
  sort(data.begin(), data.end());
  reverse(data.begin(), data.end());
  vector<int> d3(p3, p3+n);
  if (d3 != data) {
    cout << "ERROR: Failed" << endl
         << "Expected   : " << PrintVector(data) << endl
         << "Got instead: " << PrintVector(d3) << endl;
    return false;
  }
  return true;
}

int main() {
  srandom(0);
  // Positive only.
  for (int i = 0; i < 100; ++i) {
    const int n = sqrt((1L << (random() % 20))) + 1;
    vector<int> data(n);
    for (int j = 0; j < n; ++j) data[j] = random();
    if (!Test(std::move(data))) return 1;
  }
  cout << "PASSED tests #1 (non-negative numbers, small arrays)" << endl;

  // Positive only, large array.
  {
    const int n = 1L << 21;
    vector<int> data(n);
    for (int j = 0; j < n; ++j) data[j] = random();
    if (!Test(std::move(data))) return 1;
    cout << "PASSED tests #2 (non-negative numbers, large array)" << endl;
  }

  // Singleton, all signs.
  for (int i : {-1, -(1<<30), -12345321, 0, 1, 1<<30}) {
    if (!Test(vector<int>{i})) return 1;
  }
  cout << "PASSED tests #3 (positive/negative singletons)\n";

  // Zero length
  if (!Test({})) return 1;
  cout << "PASSED test #4 (empty array)\n";

}
