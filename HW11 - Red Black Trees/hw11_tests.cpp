/*
Brian Steuber
CPSC 223-01
HW11
This hw11_tests.cpp file tests remove 
implemented in rbt_collection.h
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "rbt_collection.h"

using namespace std;

// Test 1
TEST(BasicCollectionTest, CorrectSize) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("a", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("b", 20.0);
  ASSERT_EQ(2, c.size());
  ASSERT_EQ(2, c.height());
}

// Test 2
TEST(BasicCollectionTest, InsertAndFind) {
  RBTCollection<string, double> c;
  double v;
  ASSERT_EQ(false, c.find("a", v));
  c.insert("a", 10.0);
  ASSERT_EQ(true, c.find("a", v));
  ASSERT_EQ(v, 10.0);
  ASSERT_EQ(false, c.find("b", v));
  c.insert("b", 20.0);
  ASSERT_EQ(true, c.find("b", v ));
  ASSERT_EQ(20.0, v );
}

// Test 3 -- THIS TEST SHOULD FAIL FOR HW8
TEST( BasicCollectionTest, RemoveElems) {
  RBTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  double v;
  c.remove("a");
  ASSERT_EQ(false, c.find("a", v));
  ASSERT_EQ(true, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  c.remove("b");
  ASSERT_EQ(false, c.find("b", v));
  ASSERT_EQ(true, c.find("c", v));
  c.remove("c");
  ASSERT_EQ(false, c.find("c", v));
  ASSERT_EQ(0, c.size());
} 

// Test 4
TEST(BasicCollectionTest, GetKeys) {
  RBTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  vector <string> ks;
  c.keys(ks);
  vector <string>::iterator iter;
  iter = find(ks.begin(), ks.end(), "a");
  ASSERT_NE(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "b");
  ASSERT_NE(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "c");
  ASSERT_NE (ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "d");
  ASSERT_EQ(ks.end(), iter);
}



// Test 5
TEST(BasicCollectionTest, GetKeyRange ) {
  RBTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("b", 20.0);
  c.insert("c", 30.0);
  c.insert("d", 40.0);
  c.insert("e", 50.0);
  vector <string> ks;
  c.find("b", "d", ks);
  vector <string>::iterator iter;
  iter = find(ks.begin(), ks.end(), "b");
  ASSERT_NE(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "c");
  ASSERT_NE(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "d");
  ASSERT_NE(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "a");
  ASSERT_EQ(ks.end(), iter);
  iter = find(ks.begin(), ks.end(), "e");
  ASSERT_EQ(ks.end(), iter);
}



// Test 6
TEST(BasicCollectionTest, KeySort) {
  RBTCollection<string, double> c;
  c.insert("a", 10.0);
  c.insert("e", 50.0);
  c.insert("c", 30.0);
  c.insert("b", 20.0);
  c.insert("d", 40.0);
  vector <string> sorted_ks;
  c.sort(sorted_ks);
  ASSERT_EQ(c.size(), sorted_ks.size());
  for (int i = 0; i < int (sorted_ks.size())- 1; ++i) 
  {
    ASSERT_LE(sorted_ks[i], sorted_ks[ i +1]);
  }
}

// Test 7
TEST(TreeCollectionTest, AssignOpTest) {
  RBTCollection <string, int> c1;
  c1.insert("c", 10);
  c1.insert("b", 15);
  c1.insert("d", 20);
  c1.insert("a", 20);
  RBTCollection <string, int> c2;
  c2 = c1;
  ASSERT_EQ(c1.size(), c2.size());
  ASSERT_EQ(c1.height(), c2.height());
}

// Test 8 - Key function
TEST(BasicCollectionTest, KeysTest) {
  RBTCollection <string, int> c1;
  c1.insert("c", 10);
  c1.insert("b", 15);
  c1.insert("d", 20);
  c1.insert("a", 20);
  vector <string> ks;
  c1.keys(ks);
  for (int i = 0; i < ks.size(); i++)
  {
	cout << ks.at(i) << endl;
  }
}
  
// Test 9 - Height/Destructor
TEST(TreeCollectionTest, HeightTest) {
  RBTCollection <string, int> c1;
  c1.insert("c", 10);
  c1.insert("b", 15);
  c1.insert("d", 20);
  c1.insert("a", 20);
  ASSERT_EQ(c1.height(), 3);
  c1.~RBTCollection();
}

// Test 10 - Leaf Node - left
TEST(TreeCollectionTest, Remove0) {
  RBTCollection <string, int> c1;
  c1.insert("f", 10);
  c1.insert("d", 15);
  c1.insert("b", 20);
  c1.insert("a", 20);
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 4);
  c1.remove("a");
  ASSERT_EQ(c1.height(), 2);
  ASSERT_EQ(c1.size(), 3);
  c1.~RBTCollection();
}

// Test 11 - Leaf Node - right
TEST(TreeCollectionTest, Remove1) {
  RBTCollection <string, int> c1;
  c1.insert("f", 10);
  c1.insert("d", 15);
  c1.insert("b", 20);
  c1.insert("g", 20);
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 4);
  c1.remove("g");
  ASSERT_EQ(c1.height(), 2);
  ASSERT_EQ(c1.size(), 3);
  c1.~RBTCollection();
}

// Test 12 - Root Removal
TEST(TreeCollectionTest, Remove2) {
  RBTCollection <string, int> c1;
  c1.insert("h", 10);
  c1.insert("e", 15);
  c1.insert("c", 20);
  c1.insert("a", 20);
  c1.insert("b", 25);
  //c1.print();
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 5);
  c1.remove("e");
  //c1.print();
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 4);
  c1.~RBTCollection();
}

// Test 13 - G removed 
TEST(TreeCollectionTest, Remove3) {
  RBTCollection <string, int> c1;
  c1.insert("j", 10);
  c1.insert("g", 15);
  c1.insert("s", 20);
  c1.insert("f", 20);
  c1.insert("p", 25);
  c1.insert("i", 30);
  c1.insert("v", 35);
  c1.insert("h", 40);
  //c1.print();
  ASSERT_EQ(c1.height(), 4);
  ASSERT_EQ(c1.size(), 8);
  c1.remove("g");
  //c1.print();
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 7);
  c1.~RBTCollection();
}


// Test 14 - S removed; inorder successor
TEST(TreeCollectionTest, Remove4) {
  RBTCollection <string, int> c1;
  c1.insert("j", 10);
  c1.insert("g", 15);
  c1.insert("s", 20);
  c1.insert("f", 20);
  c1.insert("p", 25);
  c1.insert("i", 30);
  c1.insert("v", 35);
  c1.insert("h", 40);
  c1.insert("q", 50);
  //c1.print();
  ASSERT_EQ(c1.height(), 4);
  ASSERT_EQ(c1.size(), 9);
  c1.remove("s");
  //c1.print();
  ASSERT_EQ(c1.height(), 4);
  ASSERT_EQ(c1.size(), 8);
  c1.~RBTCollection();
}

// Test 15 - removing blacks 
TEST(TreeCollectionTest, Remove5) {
  RBTCollection <string, int> c1;
  c1.insert("j", 10);
  c1.insert("g", 15);
  c1.insert("s", 20);
  c1.insert("f", 20);
  c1.insert("p", 25);
  c1.insert("i", 30);
  c1.insert("v", 35);
  c1.insert("h", 40);
  c1.insert("q", 50);
  c1.insert("z", 55);
  c1.insert("w", 60);
  //c1.print();
  ASSERT_EQ(c1.height(), 4);
  ASSERT_EQ(c1.size(), 11);
  c1.remove("w");
  c1.remove("v");
  //c1.print();
  ASSERT_EQ(c1.height(), 3);
  ASSERT_EQ(c1.size(), 9);
  c1.~RBTCollection();
}

int main (int argc , char ** argv )
{
  testing :: InitGoogleTest (& argc , argv );
  return RUN_ALL_TESTS ();
}
