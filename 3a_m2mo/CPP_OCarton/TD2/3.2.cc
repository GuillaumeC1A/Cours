#include <iostream>
using namespace std;

void Strip(char* str) {
  int i = 0;     //i est notre indice de parcours de la chaîne de caractères
  int j = 0;     //j est notre indice d'ajout des caractères qui ne sont pas des espaces

  while(str[i] != 0) {
    if(str[i] != ' ') { //si on croise un espace
      str[j] = str[i] ; //on le rajoute à la suite des autres caractères qui ne sont pas des espaces (grâce à j)
      j++;              //on avance tout le monde
      i++;
    } 
    else i++;           //sinon on le passe sans avancer j pour continuer à entasser des caractères non espace.
  }
  str[j] = 0; //Quand on a vu tous les caractères, on coupe le bout de notre chaîne pour s'arrêter au bout de l'entassement de caractères.
}
//Le principe est qu'on écrit par-dessus le début de la chaîne et on rajoute une fin de chaîne de caractères prématurément.
//En mémoire à la fin, on aura la chaîne sans les espaces, le caractère \0, et la fin de la chaîne originale AVEC espaces et son \0.