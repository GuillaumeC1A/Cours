#include <iostream>

using namespace std;
    
int main() {

    int x;

    cout << "Entrez un nombre et appuyez sur [Enter]: ";

    cin >> x;

    cout << "Ce nombre est ";

    if (x % 2 == 0) {

      cout << "pair";

    } else {

      cout << "impair";

    }

    cout << endl;

}