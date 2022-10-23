#include <iostream>
using namespace std;

//Problème à la compilation - implicit declaration of LaSolution(). On va donc rajouter une déclaration pour le compilateur.
int LaSolution(int x);

//Maintenant, le compilateur s'attend à trouver dans les fichiers inclus la définition de la fonction LaSolution avec sa signature. 
int main() {
  cout << LaSolution(3) << endl;
  cout << LaSolution(-1) << endl;
}

// Cette fois pas de problème à la compilation entrant deux fichiers en ligne de commande pour la compilation : g++ 1.2.main et 1.1