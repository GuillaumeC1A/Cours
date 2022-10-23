#include <stdio.h>

void init(int * tab);
void swap(float f1, float f2);

int main(int argc, char *argv[]) {
  int * ptr = alloc(7);
  // use printf to look at the content accessible from ptr

  float f1=0.7;
  float f2=1.2;
  // use swap to put value of f1 in f2 and vice-versa
  // use printf to display values of f1 and f2
  
  return 0;
}

int * alloc (int val){
   int tab[20];
   // initialize elements of tab with value val

   return tab;
}

void swap(float f1, float f2)
{

}
