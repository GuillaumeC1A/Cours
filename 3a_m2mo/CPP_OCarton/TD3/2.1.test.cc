#include "2.1.h"
#include "main_utils.h"

int main() {
  cout << "___________________________" << endl;
  cout << "Testing 2.1: simple example" << endl;
  double kMatrix[16] = {0.1, -0.2, 0.3, -0.4,
                        0.5, -0.6, 0.7, -0.8,
                        0.9, -1.0, 1.1, -1.2,
                        1.3, -1.4, 1.5, -1.6};

  CHECK_NEAR(trace(kMatrix, 4), 0.1 - 0.6 + 1.1 - 1.6, 1e-12);
  CHECK_NEAR(trace(kMatrix, 3), 0.1 + 0.5 + 0.9, 1e-12);
  cout << "PASSED" << endl;
  
  // Simple corner case: size = 1.
  cout << "Testing 2.1: 1x1 matrix" << endl;
  CHECK_NEAR(trace(kMatrix, 1), 0.1, 1e-12);
  double x = 123.456;
  CHECK_NEAR(trace(&x, 1), 123.456, 1e-12);
  cout << "PASSED" << endl;

  // Complexity test: it shouldn't be O(N), not O(N^2).
  cout << "Testing 2.1: speed test" << endl;
  clock_t c0 = clock();
  const int size = 1000;
  double* big_matrix = new double[size * size];
  for (int i = 0; i < size; ++i) {
    big_matrix[i] = 1.0 / (i + 10);
  }
  double t = 0;
  for (int i = 0; i < size; i += size + 1) {
    t += big_matrix[i];
  }
  double sum = 0;
  const int times = 100000;
  for (int i = 0; i < times; ++i) {
    sum += trace(big_matrix, size);
  }
  CHECK_NEAR(sum, t * times, 1e-12);
  cout << "PASSED in " << (double(clock()) - c0) / CLOCKS_PER_SEC << " s." << endl;

  // Super-corner case: size=0.
  cout << "Testing 2.1: empty matrix" << endl;
  CHECK_EQ(trace(kMatrix, 0), 0.0);
  cout << "PASSED" << endl;
}
