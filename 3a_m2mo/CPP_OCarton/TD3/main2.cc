#include "2.3.cc"
#include <iostream>
    
int main()
{
  {
    // Easy case: square matrix
    double A[16] = {0.1, -0.2, 0.3, -0.4,
                    0.5, -0.6, 0.7, -0.8,
                    0.9, -1.0, 1.1, -1.2,
                    1.3, -1.4, 1.5, -1.6};
    Mat matA(4, 4, A);
    transpose(4, 4, A);
    std::cout << matA << std::endl;
    transpose(4, 4, A);
    std::cout << matA << std::endl;
  }
    
  {
    // Rectangular matrix.
    double A[15] = {0.1, -0.2, 0.3, -0.4, 0.5,
                    -0.6, 0.7, -0.8, 0.9, -1.0,
                    1.1, -1.2, 1.3, -1.4, 1.5};
    
    Mat matA(3, 5, A);
    std::cout << matA << std::endl;
    transpose(3, 5, A);
    Mat matAt(5, 3, A);
    std::cout << matAt << std::endl;
    
    transpose(5, 3, A);
    std::cout << matA << std::endl;
  }
}