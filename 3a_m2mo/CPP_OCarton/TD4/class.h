#ifndef _CLASS_H_
#define _CLASS_H_

#include <cstring>
#include <string> 
#include "student.h"

struct Class {

    std::string course_name;
    int max_students; //Ne dépassera pas 1000.
    Student** students; //Tableau de pointeurs vers des Students, notre liste d'élèves. (1ère version)
    //Student* students[1000]; //Tableau de pointeurs vers des Students, notre liste d'élèves. (2ème version)

    Class();
    Class(std::string course_name, int max_students);
    
    std::string getName();
    int addStudent(Student* student);
    int getMaxNumberOfStudents() const;
    int getNumStudents() const;
    Student* getStudent(int student_index) const;
    //J'ai préféré prendre Student* pour pouvoir retourner NULL si l'élève n'existe pas, et ça ne change en définitive rien:
    //On accède quand même à un élève, on peut modifier ses attributs etc...
};
#endif