#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "3.2.cc"

int main() {
  vector<pair<string, string>> tests = {
    {"pa    pe t    i     peton",
     "papetipeton"},
    {" Bonjour  madame     la marquise H E L L O    W    ORL D  ",
     "BonjourmadamelamarquiseHELLOWORLD"},
    {"  x  ", "x"},
    {" x ", "x"},
    {"  ", ""},
    {" ", ""},
    {"", ""}};
  for (int i = 0; i < tests.size(); ++i) {
    const auto& p = tests[i];
    char test[80];
    strcpy(test, p.first.c_str());
    Strip(test);
    if (test == p.second) {
      cout << "Test #" << i << " PASSED\n";
    } else {
      cerr << "Test #" << i << "FAILED!"
           << "\nWith input: '" << p.first << "'"
           << "\nExpected  : '" << p.second << "'"
           << "\nGot       : '" << test << "'" << endl;
      return 1;
    }
  }
  cout << "--------\n"
       << "Running performance test. Any O(N^2) solution (or worse) will hang"
       << " forever:\nif it happens, press Ctrl+C to interrupt the program,"
       << " and optimize your code to make it run in O(N).\n";
  const int size = 1<<20;  // 1MB.
  char* test = new char[size + 1];  // 1MB.
  for (int i = 0; i < size; ++i) {
    int r = random();
    test[i] = (r & 1) ? ' ' : (r / 2) % 26 + 'a';
  }
  test[size] = 0;
  clock_t c0 = clock();
  Strip(test);
  const double time = double(clock() - c0) / CLOCKS_PER_SEC;
  cout << "\nDone! Strip() worked in " << time << " seconds for a 1MB string.\n"
       << "--------\n";
  const int s = strlen(test);
  if (s < size / 3 || s > 2 * size / 3) {
    cerr << "ERROR: your Strip() function has a bug on super-long strings!\n";
    return 1;
  }
  cout << "All tests PASSED!\n";
}
