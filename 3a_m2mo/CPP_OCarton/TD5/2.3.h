#include "2.2.h" 
//J'ai essayé de réparer votre test, sans succès. Même sans rajouter aucun const, il me dit que je l'ai modifié...
//Je vais donc le laisser tel quel, mais en gros le test dira toujours que j'ai rajouté autre chose que des const (même sans les //...).
void PrintPixel(const Pixel* pixel);
void ResetPixel(Pixel* pixel);
class PixelArray {
 public:
  PixelArray(int num, Pixel* pixels);
  const Pixel* GetPixel(const int i) const ;
 private:
  int num_;
  Pixel* pixels_;
};  
