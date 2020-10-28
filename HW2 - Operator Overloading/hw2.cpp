/*
Brian Steuber
CPSC 223-01
HW2
This hw2.cpp file implements assert functions to 
test the operator overloading functions and 
other functions in integer.cpp
*/

#include <iostream>
#include <cassert>
#include "integer.h"

using namespace std;

int main ()
{
  //test same values
  Integer x1("42");
  Integer x2("42");
  assert(x1 == x2);
  assert(!(x1 != x2));
  assert(!(x1 < x2));
  assert(!(x1 > x2));
  assert(x1 <= x2);
  assert(x1 >= x2);
  
  //test two different values
  Integer x3("50");
  Integer x4("57");
  assert(x3 != x4);
  assert(x3 < x4);
  assert(x3 <= x4);
  assert(!(x3 > x4));
  assert(!(x3 >= x4));
  assert(!(x3 == x4));
  assert(x4 > x3);
  assert(x4 >= x3);
  assert(!(x4 < x3));
  assert(!(x4 <= x3));
  
  //test adding two different values
  Integer x5("99999999999999999999");
  Integer x6("1");
  Integer r1("100000000000000000000");
  assert (x5 + x6 == r1);
  
  //no carry add test
  Integer x7("21");
  Integer x8("175");
  Integer r2("196");
  assert(x7 + x8 == r2);
  
  //print tests
  cout << "should be 1: " << x6 << endl;
  cout << "should be 42: " << x1 << endl;
  cout << "should be 175: " << x8 << endl;
  
  //basic subtraction without carry over
  Integer x9("97");
  Integer x10("45");
  Integer r5("52");
  assert(x9 - x10 == r5);
  
  //subtraction with carry over
  Integer x11("107");
  Integer x12("39");
  Integer r4("68");
  assert(x11 - x12 == r4);
  
  //cases cases of adding negative numbers with unary operator 
  Integer x13("20");
  Integer x15 = -x13;
  Integer x14("40");
  Integer x16 = -x14;
  assert(x15+x14 == x13);
  assert(x14 + x15 == x13);
  assert(x15+x15 == x16);
  
  //cases of subtracting negative numbers with unary operator
  Integer x17("60");
  Integer x18 = -x17;
  Integer x19("60");
  assert(x15 - x14 == x18);
  assert(x14 - x15 == x19);
}