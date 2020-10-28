/*
Brian Steuber
CPSC 223-01
HW10
This hw10_tests.cpp file tests insert 
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

// Test 10 - root test
TEST(BasicCollectionTest, Bal0) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("b", 10.0);
  ASSERT_EQ(1, c.size());
  ASSERT_EQ(1, c.height());
}

// Test 11 - root with 2 children test 
TEST(BasicCollectionTest, Bal1) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("b", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("a", 20.0);
  ASSERT_EQ(2, c.size());
  c.insert("c", 30.0);
  ASSERT_EQ(3, c.size());
  ASSERT_EQ(2, c.height());
}

// Test 12 - Test case 3 left subtree
TEST(BasicCollectionTest, Bal2) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("h", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("d", 20.0);
  ASSERT_EQ(2, c.size());
  c.insert("l", 30.0);
  ASSERT_EQ(3, c.size());
  c.insert("a", 0);
  ASSERT_EQ(4, c.size());
  c.insert("c", 70.0);
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(3, c.height());
}

// Test 13 - Test case 3 right subtree
TEST(BasicCollectionTest, Bal3) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("h", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("d", 20.0);
  ASSERT_EQ(2, c.size());
  c.insert("l", 30.0);
  ASSERT_EQ(3, c.size());
  c.insert("p", 0);
  ASSERT_EQ(4, c.size());
  c.insert("m", 70.0);
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(3, c.height());
}

// Test 14 - Test case 2 single rotate right
TEST(BasicCollectionTest, Bal4) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("h", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("d", 20.0);
  ASSERT_EQ(2, c.size());
  c.insert("l", 30.0);
  ASSERT_EQ(3, c.size());
  c.insert("e", 0);
  ASSERT_EQ(4, c.size());
  c.insert("f", 70.0);
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(3, c.height());
}

// Test 15 - Test case 2 single rotate left
TEST(BasicCollectionTest, Bal5) {
  RBTCollection<string, double> c;
  ASSERT_EQ(0, c.size());
  c.insert("h", 10.0);
  ASSERT_EQ(1, c.size());
  c.insert("d", 20.0);
  ASSERT_EQ(2, c.size());
  c.insert("l", 30.0);
  ASSERT_EQ(3, c.size());
  c.insert("m", 0);
  ASSERT_EQ(4, c.size());
  c.insert("n", 70.0);
  ASSERT_EQ(5, c.size());
  ASSERT_EQ(3, c.height());
}

int main (int argc , char ** argv )
{
  testing :: InitGoogleTest (& argc , argv );
  return RUN_ALL_TESTS ();
}
