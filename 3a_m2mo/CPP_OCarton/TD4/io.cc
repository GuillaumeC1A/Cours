#include "io.h"

void PrintStudent(const Student& student) {
  cout << "Student: " << student.getName() << " (Birthdate : " << student.getBirthday() << ")" << endl;
}

void PrintClass(const Class& classe) {
  cout << "Affichage de la classe: " << classe.course_name << " (Max eleves : " << classe.max_students << ")" << endl;
  for (int i = 0; i < classe.getNumStudents(); i++) {
    cout << "i : "  << i << " max : " << classe.max_students << endl;
    PrintStudent(*classe.getStudent(i));
  }
}

Student* EnterStudent() {
  char name[100];
  int birthdate;
  cout << "Nom de l'eleve : ";
  cin >> name;
  cout << "Date de naissance de l'eleve : ";
  cin >> birthdate;
  cout << endl;
  return new Student(name, birthdate); //Constructeur de notre classe Student : CNS (char* name, int birthdate)
  //On utilise bien new ici, car on veut un pointeur vers un élève, et non un élève, qui serait détruit à la fin de la fonction.
}

Class* EnterClass() {
  string course_name;
  int max_students;
  
  cout << "Nom du cours : ";
  cin >> course_name;
  cout << "Nombre max d'eleves : ";
  cin >> max_students;
  Class* classe = new Class(course_name, max_students); //Constructeur de notre classe Class : CNS (string course_name, int max_students)
  //On utilise bien new ici, car on veut un pointeur vers une classe, et non une classe, qui serait détruite à la fin de la fonction.
  //Mais avant de retourner ce pointeur on va d'abord ajouter des élèves à la classe.

  int num_students = 0;
  while (num_students < max_students) {
    cout << "Ajouter un eleve ? (1 pour oui, 0 pour non) : ";
    int add_student;
    cin >> add_student;
    if (add_student == 1) {
      classe->addStudent(EnterStudent()); //On ajoute un élève à la classe, en utilisant la méthode addStudent de la classe Class.
      cout << "Eleve numero " << num_students <<" ajoute." << endl;
      num_students++;
    } else {
      break; //Si on en a fini avec l'ajout d'élèves, on renvoie la classe telle quelle. 
    }
    }
    return classe;
}