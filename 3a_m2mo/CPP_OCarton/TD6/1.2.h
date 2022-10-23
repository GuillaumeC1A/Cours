using uint64 = unsigned long long;

class Uint2048 {
 public:
  Uint2048();
  Uint2048(int x);

  bool operator<(Uint2048 other);
  Uint2048 operator+(Uint2048 other);

  void Print();

 private:
  uint64 u_[32];
};
