#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

#include "3.1.h"

#define CHECK(x) do {\
  if (!(x)) {\
    cerr << "ERROR in " __FILE__ ":" << __LINE__\
         << ": CHECK condition violated: " #x << std::endl;\
    exit (1);\
  }\
} while(0)

int main() {
  using Element = List::Element;
  List l0;
  List l1;
  List l2;
  List l3;

  // l2 = 3,4,5
  Element* p6 = l2.InsertNewElementAfter(6, nullptr);
  l2.InsertNewElementAfter(5, nullptr);
  l2.InsertNewElementAfter(4, nullptr);
  Element* p3 = l2.InsertNewElementAfter(3, nullptr);
  l2.InsertNewElementAfter(3, nullptr);
  l2.InsertNewElementAfter(2, nullptr);
  l2.Remove(p3);
  l2.Remove(l2.Head());
  l2.Remove(p6);

  // l3 = 1,2,3
  p3 = l3.InsertNewElementAfter(3, nullptr);
  Element* p2 = l3.InsertNewElementAfter(2, nullptr);
  Element* p4 = l3.InsertNewElementAfter(4, p3);
  Element* p1 = l3.InsertNewElementAfter(1, nullptr);
  l3.Remove(p4);
  Element* p22 = l3.InsertNewElementAfter(2, nullptr);
  l3.Remove(p22);

  l2.InsertListAfter(&l0, l2.Head());
  l2.InsertListAfter(&l3, l2.Head()->next);
  l1.InsertListAfter(&l2, l1.Head());
  CHECK(l1.NumElements() == 6);
  vector<int> vals;
  Element* prev = nullptr;
  for (Element* ptr = l1.Head(); ptr != nullptr; ptr = ptr->next) {
    vals.push_back(ptr->value);
    CHECK(ptr->prev == prev);
    prev = ptr;
  } 
  const vector<int> expected = {3,4,1,2,3,5};
  CHECK(expected == vals);
  cout << "SUCCESS!\n";
}
