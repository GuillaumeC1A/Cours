#include <iostream>
        
struct Mat
{
  size_t n;
  size_t m;
        
  double *content;
        
  Mat(size_t _n, size_t _m, double *_content) : n(_n), m(_m) {
    content = _content;
  }
};
        
std::ostream& operator<<(std::ostream& os, const Mat& m)
{
  for (int i = 0; i < m.n; ++i)
  {
    os << "( ";
    for (int j = 0; j < m.m; ++j)
    {
      os << m.content[i * m.m + j] << " ";
    }
    os << ")" << std::endl;
  }
  return os;
}