#include <cstring>
#include <string>
#include "class.h"

Class::Class(std::string course_name, int max_students) {
    this->course_name = course_name;
    this->max_students = max_students;
    this->students = new Student*[max_students]; //Mais aucun élève dedans.
    //this->students[0] = NULL; //ERREUR ----Cette initialisation suffit pour les calculs de getNumberStudents() ---- Pas du tout !
    for (int i = 0; i < max_students; ++i) {
        this->students[i] = NULL;
    } //Cette initialisation complète est nécessaire pour les calculs de getNumberStudents().
}

string Class::getName() {
    return course_name;
}

int Class::addStudent(Student* student) {
    int num_students = getNumStudents();
    if (num_students < max_students) { //C'est ici qu'on a notre sécurité pour le nombre max d'élèves, puisqu'on a déclaré students en tant que Student**. 
        students[num_students] = student;
        return num_students;
    }
    return -1; //Si le cours est plein. 
}

int Class::getMaxNumberOfStudents() const {
    return max_students;
}

int Class::getNumStudents() const {
    int i = 0;
    while (students[i] != NULL) { //students contient des pointeurs vers des Students. Tant qu'on atteint pas un nullptr, il en reste. 
        ++i;
    }
    return i;
}

Student* Class::getStudent(int student_index) const {
    if (student_index < getNumStudents()) {
        return students[student_index]; //Contient des pointeurs vers des Students. 
    }
    cout << "Erreur : l'eleve n'existe pas (id trop grand ou pas encore affecté)." << endl;
    return NULL; //Si on demande un élève qui n'existe pas : nullptr, avec un msg d'erreur. NULL est le nullptr qui marche ici, je n'arrive pas à utilliser nullptr.
    
    
    //On pourrait imaginer une sécurité pour un id trop grand ET une autre pour un id pas encore affecté
    }

//Modification pour voir si le Makefile le detecte