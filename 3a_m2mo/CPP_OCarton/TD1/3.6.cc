#include <iostream>

using namespace std;

long long n;

int main() {
    cout << "Entrez un nombre et appuyez sur [Enter]: ";

    cin >> n;

    bool isPrime(long long N) { //Je suppose que le nombre entré sera grand et positifde toute façon.

        long long i;
        for(i = 2; i < sqrt(N); i++) {

            if (N % i == 0) {
                return false;
            }
        }

        return true;
    }

    long long i = 3;

    while(n != 1) { //Tant qu'il reste des facteurs premiers à afficher et qu'on a pas atteint n (c'est aussi la garantie théorique de finition du programme)
        if (isPrime(i) && n % i == 0) { //Si i est premier et est un facteur premier de n
            cout << i << " "; //On l'affiche
            n /= i; //On enlève le facteur premier en question
        } else {
            i++; //Sinon on passe au nombre suivant (on pourrait faire le crible d'Eratosthène pour éviter certains nombres)
        }
    }
}