#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

#include "1.5.cc"

string PrintVector(const vector<int>& v) {
  if (v.empty()) return "[]";
  stringstream ss;
  ss << "[" << v[0];
  const int maxN = 20;
  for (int i = 1; i < std::min(maxN, int(v.size())); ++i) ss << ", " << v[i];
  if (v.size() > maxN) ss << "... (" << v.size() - maxN << " more values) ";
  ss << "]";
  return ss.str();
}

int HIndexRef(const vector<int>& data) {
  const int n = data.size();
  int* count = new int[n + 1]();
  for (int i : data) count[std::max(0, std::min(n, i))]++;
  int s = 0;
  for (int i = n; i >= 0; --i) if ((s += count[i]) >= i) return i;
  return -1;
}

bool Test(const vector<int>& data) {
  const int n = data.size();
  const int href = HIndexRef(data);
  const vector<int> copy = data;
  const int h = HIndex(data.size(), data.data());
  if (data != copy) {
    cout << "ERROR: your code modifies the input vector!\n";
    return false;
  }
  if (h != href) {
    cout << "ERROR: Failed on: " << PrintVector(data) << endl
         << "Expected   : " << href << endl
         << "Got instead: " << h << endl;
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
    const int M = random() % (2*n) + 1;
    for (int j = 0; j < n; ++j) data[j] = random() % M;
    if (!Test(std::move(data))) return 1;
  }
  cout << "PASSED tests #1 (non-negative numbers, small arrays)" << endl;

  // Positive only, large array.
  {
    const int n = 1L << 21;
    const int M = n + 2;
    vector<int> data(n);
    for (int j = 0; j < n; ++j) data[j] = random() % M;
    if (!Test(std::move(data))) return 1;
    cout << "PASSED tests #2 (non-negative numbers, large array)" << endl;
  }

  // Zero length
  if (!Test({})) return 1;
  cout << "PASSED test #3 (empty array)\n";

  // Singleton, all signs.
  for (int i : {-1, -(1<<30), -12345321, 0, 1, 1<<30}) {
    if (!Test(vector<int>{i})) return 1;
  }
  cout << "PASSED tests #3 (positive/negative singletons)\n";

}
