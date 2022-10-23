#include <cstdlib>
#include <iostream>
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
  List list;
  using Element = List::Element;

  // The list is empty.
  cout << "Testing the empty list...\n";
  CHECK(list.NumElements() == 0);
  CHECK(list.Head() == nullptr);
  CHECK(list.Find(0) == nullptr);
  cout << "SUCCESS!\n";

  // Insert '4'.
  cout << "Testing the insertion of one element...\n";
  Element* p4 = list.InsertNewElementAfter(4, list.Head());
  CHECK(p4->value == 4);
  CHECK(p4->prev == nullptr);
  CHECK(p4->next == nullptr);
  CHECK(list.Head() == p4);
  CHECK(list.NumElements() == 1);
  cout << "SUCCESS!\n";

  // Insert '5' after 4, then '6' after 4, then '7' at head: 7, 4, 6, 5.
  cout << "Testing the insertion of more elements...\n";
  Element* p5 = list.InsertNewElementAfter(5, p4);
  Element* p6 = list.InsertNewElementAfter(6, p4);
  Element* p7 = list.InsertNewElementAfter(7, nullptr);
  CHECK(list.NumElements() == 4);
  CHECK(list.Head() == p7);
  CHECK(p4->value == 4);
  CHECK(p5->value == 5);
  CHECK(p6->value == 6);
  CHECK(p7->value == 7);
  CHECK(p7->prev == nullptr);
  CHECK(p7->next == p4);
  CHECK(p4->prev == p7);
  CHECK(p4->next == p6);
  CHECK(p6->prev == p4);
  CHECK(p6->next == p5);
  CHECK(p5->prev == p6);
  CHECK(p5->next == nullptr);
  cout << "SUCCESS!\n";

  cout << "Testing Find()...\n";
  CHECK(list.Find(4) == p4);
  CHECK(list.Find(5) == p5);
  CHECK(list.Find(6) == p6);
  CHECK(list.Find(7) == p7);
  CHECK(list.Find(8) == nullptr);
  cout << "SUCCESS!\n";

  cout << "Testing Find() on a repeated value (should return the first!)...\n";
  Element* p6_2 = list.InsertNewElementAfter(6, p6);
  Element* p6_3 = list.InsertNewElementAfter(6, p4);
  CHECK(list.Find(6) == p6_3);
  cout << "SUCCESS!\n";
}
