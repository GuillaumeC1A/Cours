#include "2.2.h"
#include "main_utils.h"

int main() {
  cout << "___________________________" << endl;
  {
    cout << "Testing 2.2: simple example" << endl;
    // 3 x 5
    double A[15] = {0.1, -0.2, 0.3, -0.4, 0.5,
                    -0.6, 0.7, -0.8, 0.9, -1.0,
                    1.1, -1.2, 1.3, -1.4, 1.5};
    // 5 x 2
    double B[10] = {2.0, -2.1,
                    -2.2, 2.3,
                    2.4, -2.5,
                    -2.6, 2.7,
                    2.8, -2.9};

    double* prod = matrix_prod(3, 5, 2, A, B);
    const double kExpected[3][2] = {
      {0.1*2.0 + 0.2*2.2 + 0.3*2.4 + 0.4*2.6 + 0.5*2.8,
       -0.1*2.1 - 0.2*2.3 - 0.3*2.5 - 0.4*2.7 - 0.5*2.9},
      {-0.6*2.0 - 0.7*2.2 - 0.8*2.4 - 0.9*2.6 - 1.0*2.8,
       0.6*2.1 + 0.7*2.3 + 0.8*2.5 + 0.9*2.7 + 1.0*2.9},
      {1.1*2.0 + 1.2*2.2 + 1.3*2.4 + 1.4*2.6 + 1.5*2.8,
       -1.1*2.1 - 1.2*2.3 - 1.3*2.5 - 1.4*2.7 - 1.5*2.9}};
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        CHECK_NEAR(prod[i*2 + j], kExpected[i][j], 1e-12);
      }
    }
    cout << "PASSED" << endl;
  }
  
  // Simple corner case: size = 1.
  {
    cout << "Testing 2.2: 1x1 matrices" << endl;
    double a = 12.34;
    double b = 45.67;
    CHECK_NEAR(*matrix_prod(1, 1, 1, &a, &b), 12.34 * 45.67, 1e-12);
    cout << "PASSED" << endl;
  }

  // Complexity test: it should be O(N*M*P).
  {
    cout << "Testing 2.2: Speed test" << endl;
    const clock_t c0 = clock();
    const int n = 101;
    const int m = 2003;
    const int p = 304;
    double *a = new double[n * m];
    double *b = new double[m * p];
    for (int i = 0; i < n * m; ++i) a[i] = 1.0 / (i + 43);
    for (int i = 0; i < m * p; ++i) b[i] = 1.0 / (i + 67);
    double* prod = matrix_prod(n, m, p, a, b);
    double ck = 0;
    for (int i = 0; i < n * p; ++i) {
      ck += (i + 1) * prod[i];
    }
    // printf("%.16lf\n", ck);
    CHECK_NEAR(ck, 157.6742683042820374, 1e-8);
    cout << "PASSED in " << (double(clock()) - c0) / CLOCKS_PER_SEC << " s." << endl;
  }
}
