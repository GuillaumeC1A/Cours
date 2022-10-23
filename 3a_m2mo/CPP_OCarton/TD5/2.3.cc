#include <iostream>

#include "2.3.h"
        
using namespace std;
        
void PrintPixel(const Pixel* pixel) {
  cout << "X=" << pixel->GetX() << "; Y=" << pixel->GetY() << endl;
}
        
void ResetPixel(Pixel* pixel) {
  pixel->SetX(0);
  pixel->SetY(0);
}
        
PixelArray::PixelArray(int num, Pixel* pixels) {
  num_ = num;
  pixels_ = pixels;
}

const Pixel* PixelArray::GetPixel(const int i) const {
  return &pixels_[i];
}