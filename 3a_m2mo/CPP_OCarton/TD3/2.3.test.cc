#include "2.3.h"
#include "main_utils.h"

int main() {
  cout << "___________________________" << endl;
  {
    cout << "Testing 2.3: square matrix" << endl;
    // Easy case: square matrix
    double A[16] = {0.1, -0.2, 0.3, -0.4,
                    0.5, -0.6, 0.7, -0.8,
                    0.9, -1.0, 1.1, -1.2,
                    1.3, -1.4, 1.5, -1.6};
    double A_orig[4][4];
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        A_orig[i][j] = A[i * 4 + j];
      }
    }
    transpose(4, 4, A);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        CHECK_EQ(A[i * 4 + j], A_orig[j][i]);
      }
    }
    // Transpose again: goes back to the original matrix.
    transpose(4, 4, A);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        CHECK_EQ(A[i * 4 + j], A_orig[i][j]);
      }
    }
    cout << "PASSED" << endl;
  }

  {
    cout << "Testing 2.3: 1x1 matrix" << endl;
    // Easy corner case: size = 1x1.
    double a = 12.34;
    transpose(1, 1, &a);
    CHECK_EQ(a, 12.34);
    cout << "PASSED" << endl;
  }

  {
    cout << "Testing 2.3: Non-square matrix" << endl;
    // Rectangular matrix.
    double A[15] = {0.1, -0.2, 0.3, -0.4, 0.5,
                    -0.6, 0.7, -0.8, 0.9, -1.0,
                    1.1, -1.2, 1.3, -1.4, 1.5};
    double A_orig[3][5];
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 5; ++j) {
        A_orig[i][j] = A[i * 5 + j];
      }
    }
    transpose(3, 5, A);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++) {
        CHECK_EQ(A[i * 3 + j], A_orig[j][i]);
      }
    }
    transpose(5, 3, A);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 5; j++) {
        CHECK_EQ(A[i * 5 + j], A_orig[i][j]);
      }
    }
    cout << "PASSED" << endl;
  }

  {
    cout << "Testing 2.3: Speed test" << endl;
    // Complexity test.
    const clock_t c0 = clock();
    const int x = 5000;
    const int y = 5001;
    const int size = x*y;
    double* a = new double[size];
    for(int i = 0; i < size; ++i) a[i] = i + 23;
    const int times = 1;
    for (int i = 0; i < times; ++i) {
      transpose(x, y, a);
      transpose(y, x, a);
    }
    for(int i = 0; i < size; ++i) CHECK_EQ(a[i], i + 23);
    cout << "PASSED in " << (double(clock()) - c0) / CLOCKS_PER_SEC << " s." << endl;
  }
}
