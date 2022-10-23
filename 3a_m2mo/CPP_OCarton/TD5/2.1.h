class Pixel {
 public:
  Pixel();
  Pixel(int x, int y, int color);

  int GetX();
  int GetY();
  int GetColor();

  void SetX(int x);
  void SetY(int y);

 private:
  int x_;
  int y_;
  int color_;
};
