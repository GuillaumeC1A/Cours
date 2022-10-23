#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Random {
 public:
  explicit Random(int seed) : seed_(seed) {}

  inline int RandInt() {
    unsigned long long p = seed_ * 16807;  // bits 14, 8, 7, 5, 2, 1, 0
    const unsigned int M = (1U<<31) - 1;
    // Compute (p % M) using the fact that ((x << 31) % M) == x.
    seed_ = (p >> 31) + (p & M);
    if (seed_ > M) seed_ -= M;
    return seed_;
  }

  inline double RandDouble() { return RandInt() / double((1U<<31) - 1); }

  inline int Uniform(int max) { return RandInt() % max; }

 private:
  int seed_;
};

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

#define CHECK_BINARY(test, x, y) do {\
  if (!((x) test (y))) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK violated: \"" #x " " #test " " #y "\" (values: "\
         << (x) << " " #test " " << (y) <<  ")" << std::endl;\
    exit (1);\
  }\
} while(0)

#define CHECK_EQ(x, y) CHECK_BINARY(==, x, y)
#define CHECK_NE(x, y) CHECK_BINARY(!=, x, y)
#define CHECK_LT(x, y) CHECK_BINARY(<, x, y)
#define CHECK_GT(x, y) CHECK_BINARY(>, x, y)
#define CHECK_LE(x, y) CHECK_BINARY(<=, x, y)
#define CHECK_GE(x, y) CHECK_BINARY(>=, x, y)

#define CHECK_NEAR(x, y, eps) do {\
  double xx = (x);\
  double yy = (y);\
  if (xx!=yy && fabs(xx -yy) / (fabs(xx) + fabs(yy)) > double(eps)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK_NEAR violated: \"" #x " ~= " #y \
         << " with relative precision " << #eps << "\" (values: "\
         << xx << " ~= " << yy << ")" << std::endl;\
    exit (1);\
  }\
} while(0)
