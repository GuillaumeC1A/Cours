#include <iostream>

#include <cmath>

using namespace std;

int main() {

  cout << "Hello" << endl;

  double sum;

  int n = 10000000;

  for (int i = 1; i < n; i++) {

    sum = sum + 1 / (float)i;
  
  }
  cout << "Harmonic sum: " << sum << endl;

  cout << "Log(N):       " << log(n-1) << endl;

  cout << "Euler approx: " << sum - log(n-1) << endl;

  cout << "Next coeff:   " << (n)*(sum - log(n) - 0.577215664901532860606512090082) << endl; //On multiplie par n car on veut bien le _coefficient_ du 1/n qui suit.
}