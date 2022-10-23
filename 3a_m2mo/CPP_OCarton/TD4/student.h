#ifndef _STUDENT_H_
#define _STUDENT_H_

struct Student {

    char name[128];         //127 caractères max, on n'utilise pas de string
    int birthdate;      //date de naissance format YYYYMMDD
    
    Student();
    Student(char* name, int birthdate);
    int getBirthday() const;     //Getter de la date de naissance (getter donc const)
    const char* getName() const; //Getter du nom
};
#endif