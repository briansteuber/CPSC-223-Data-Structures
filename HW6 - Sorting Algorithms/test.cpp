/*
Brian Steuber
CPSC 223-01
HW6
This test.cpp file implements the functions 
in linked_list_collection.h and tests the 
sorting algorithms 

to compile: g++ -std=c++11 test.cpp
to execute: ./a.out
*/

#include <iostream>
#include <string>
#include "linked_list_collection.h"

using namespace std;

int main()
{
  LinkedListCollection<string, int> i;
  i.insert("a",1);
  i.insert("b",2);
  i.insert("c",2);
  i.insert("f",3);
  i.insert("b",4);
  i.print();
  cout << endl;  
  i.insertion_sort();
  i.print();
  cout << endl;
  cout << "Insertion Sort\n" << endl;
 
  LinkedListCollection<string, int> m;
  m.insert("a",1);
  m.insert("c",2);
  m.insert("f",3);
  m.insert("b",4);
  m.print();
  cout << endl;  
  m.merge_sort();
  m.print();
  cout << endl;
  cout << "Merge Sort\n" << endl;
  
  LinkedListCollection<string, int> q;
  q.insert("b",4);
  q.insert("a",1);
  q.insert("c",2);
  q.insert("f",3);
  q.print();
  cout << endl;  
  q.quick_sort();
  q.print();
  cout << endl;
  cout << "Quick Sort\n" << endl;
}

