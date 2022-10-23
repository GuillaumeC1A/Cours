#include "io.h"
#include "class.h"
#include "student.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main() {
    Class* c = EnterClass();
    PrintClass(*c);
    delete c; //Désallocation de la mémoire
    return 0;
}