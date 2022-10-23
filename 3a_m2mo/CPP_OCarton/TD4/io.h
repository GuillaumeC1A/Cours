#ifndef _IO_H_
#define _IO_H_

#include <cstring>
#include <string>
#include "class.h"
#include "student.h"


void PrintStudent(const Student&);

void PrintClass(const Class&);

Student* EnterStudent();

Class* EnterClass();
#endif