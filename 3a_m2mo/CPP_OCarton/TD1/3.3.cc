#include <iostream>

using namespace std;
    
int main() {

    int x;

    long long n;
    
    cout << "Entrez un nombre et appuyez sur [Enter]: ";

    cin >> n;
    
    bool is_prime = true;

    for (long long i = 2; i < sqrt(n) + 1; i++) { 
      if (n % i == 0) {
      
        is_prime = false;
        break;
      }
       //On sort de la boucle dès qu'on a trouvé un diviseur.
    }
    
    if (is_prime) {
    
      cout << "premier" << endl;
    
    } else {
    
      cout << "composite" << endl;
    
    }

}