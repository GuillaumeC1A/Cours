// -*- coding: utf-8 -*-
// Time-stamp: <staticmethod.cpp  28 sep 2016 18:49:47> 

// Static methods

#include <iostream>
using namespace std;

class A {
public:
  // Constructor
  A(int n = 0) : v(n) {}
  // Non static method: can access non static and static fields.
  void f() { ++v; ++w; }
  // Static method: can only access static fields.
  static void g() { ++w; }
private:
  int v;		// Non static field
  static int w;		// Static field
};

// Static field initialization
int A::w = 0;

int main() {
  A a;
  a.f(); 		// Call non static method with objet
  // A::f();            // Non static method must be called with an object
  a.g();		// Call static method with objet
  A::g();		// Call static method with class name
}
