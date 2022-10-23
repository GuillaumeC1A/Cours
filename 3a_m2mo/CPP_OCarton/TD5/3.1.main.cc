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
  cout << "Testing the empty list...";
  CHECK(list.NumElements() == 0);
  CHECK(list.Head() == nullptr);
  cout << "SUCCESS!\n";

  // Insert '4'.
  cout << "Testing the insertion of one element...";
  Element* p4 = list.InsertNewElementAfter(4, list.Head());
  CHECK(p4->value == 4);
  CHECK(p4->prev == nullptr);
  CHECK(p4->next == nullptr);
  CHECK(list.Head() == p4);
  CHECK(list.NumElements() == 1);
  cout << "SUCCESS!\n";

  // Insert '5' after 4, then '6' after 4, then '7' at head: 7, 4, 6, 5.
  cout << "Testing the insertion of more elements...";
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

  // Remove 6; then 7; then 5; then 4.
  cout << "Testing the removal...";
  list.Remove(p6);
  CHECK(list.NumElements() == 3);
  CHECK(list.Head() == p7);
  CHECK(p4->value == 4);
  CHECK(p5->value == 5);
  CHECK(p7->value == 7);
  CHECK(p7->prev == nullptr);
  CHECK(p7->next == p4);
  CHECK(p4->prev == p7);
  CHECK(p4->next == p5);
  CHECK(p5->prev == p4);
  CHECK(p5->next == nullptr);

  list.Remove(p7);
  CHECK(list.NumElements() == 2);
  CHECK(list.Head() == p4);
  CHECK(p4->value == 4);
  CHECK(p5->value == 5);
  CHECK(p4->prev == nullptr);
  CHECK(p4->next == p5);
  CHECK(p5->prev == p4);
  CHECK(p5->next == nullptr);

  list.Remove(p5);
  CHECK(list.NumElements() == 1);
  CHECK(list.Head() == p4);
  CHECK(p4->value == 4);
  CHECK(p4->prev == nullptr);
  CHECK(p4->next == nullptr);

  list.Remove(p4);
  CHECK(list.NumElements() == 0);
  CHECK(list.Head() == nullptr);
  cout << "SUCCESS!\n";
}
