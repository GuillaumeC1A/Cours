#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

int* SortRev(int num, const int* values) {
    int* sorted = new int[num]; //On crée un nouveau tableau de la même taille que le tableau original
    for (int i = 0; i < num; i++) { //On copie d'abord notre tableau original dans un nouveau
        sorted[i] = values[i];
    }
    std::sort(sorted, sorted + num, std::greater<int>()); //On utilise la fonction sort de la librairie algorithm
    return sorted; 
}
