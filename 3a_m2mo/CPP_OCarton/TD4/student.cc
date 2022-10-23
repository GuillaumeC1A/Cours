#include <cstring>
#include "student.h"

Student::Student(char* name, int birthdate) {
    strcpy(this->name, name); //NAME NE PEUT PAS CONTENIR D'ESPACE OU CELA FAIT PLANTER L'ENTREE (nullptr ?)
    //Version sans strcpy :
    //for(int i = 0; i < strlen(name) ; ++i) {
    //  this->name[i] = name[i];
    //name[strlen(nom)] = '\0';
    this->birthdate = birthdate;
}
int Student::getBirthday() const {       //Getter de la date d'anniversaire arrangé, (read-only donc on peut mettre const)
    return birthdate%10000;     //On retourne les 4 derniers chiffres pour ne garder que mois et jour. 
}
    
const char* Student::getName() const {   //Getter du nom (read-only donc on peut mettre const)
    return name;
    }