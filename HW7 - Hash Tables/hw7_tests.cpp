/*
Brian Steuber
CPSC 223-01
HW7
This hw7_tests.cpp file tests functions 
implemented in hash_table_collection.h
*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "hash_table_collection.h"

using namespace std;

// Test 1
TEST (BasicCollectionTest , CorrectSize) {
HashTableCollection<string, double> c;
ASSERT_EQ(c.size(), 0);
c.insert("a", 10.0);
ASSERT_EQ(c.size(), 1);
c.insert("b", 20.0);
ASSERT_EQ(c.size(), 2);
}

// Test 2
TEST (BasicCollectionTest, InsertAndFind) {
HashTableCollection<string, double> c;
double v;
ASSERT_EQ(c.find("a", v), false);
c.insert("a", 10.0);
ASSERT_EQ(c.find("a", v), true);
ASSERT_EQ(v,10.0);
ASSERT_EQ(c.find("b", v), false);
c.insert("b", 20.0);
ASSERT_EQ(c.find("b", v), true);
ASSERT_EQ(v, 20.0);
}

// Test 3
TEST(BasicCollectionTest, RemoveElems) {
HashTableCollection<string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert("c", 30.0);
double v;
c.remove("a");
ASSERT_EQ(c.find ("a", v ) , false );
c.remove("b");
ASSERT_EQ(c.find("b", v), false);
c.remove("c");
ASSERT_EQ(c.find("c", v), false);
ASSERT_EQ(c.size(), 0);
}


// Test 4
TEST(BasicCollectionTest, GetKeys) {
HashTableCollection<string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert("c", 30.0);
vector<string> ks;
c.keys(ks);
vector<string>::iterator iter;
iter = find(ks.begin(), ks.end(), "a");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "b");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "c");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "d");
ASSERT_EQ(iter, ks.end());
}


// Test 5
TEST(BasicCollectionTest, GetKeyRange) {
HashTableCollection<string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert ("c", 30.0);
c.insert ("d", 40.0);
c.insert ("e", 50.0);
vector<string> ks;
c.find("b", "d", ks);
vector<string>::iterator iter;
iter = find(ks.begin(), ks.end(), "b");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "c");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "d");
ASSERT_NE(iter, ks.end());
iter = find(ks.begin(), ks.end(), "a");
ASSERT_EQ(iter, ks.end());
iter = find(ks.begin(), ks.end(), "e");
ASSERT_EQ(iter, ks.end());
}


// Test 6
TEST(BasicCollectionTest, KeySort) {
HashTableCollection <string, double> c;
c.insert("a", 10.0);
c.insert("e", 50.0);
c.insert("c", 30.0);
c.insert("b", 20.0);
c.insert("d", 40.0);
vector<string> sorted_ks;
c.sort(sorted_ks);
// check if sort order
for(int i = 0; i < int(sorted_ks.size()) - 1; ++i)
ASSERT_LE(sorted_ks[ i ], sorted_ks[ i +1]);
}

/*Test 7 - checks that insert, remove, and size works 
with multiple cases.
*/
TEST(BasicCollectionTest, InsertRemoveCheckSize) {
HashTableCollection <string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert ("c", 30.0);
c.insert ("d", 40.0);
c.insert ("e", 50.0);
ASSERT_EQ(c.size(), 5);
c.remove("a");
ASSERT_EQ(c.size(), 4);
c.remove("b");
ASSERT_EQ(c.size(), 3);
c.remove("c");
ASSERT_EQ(c.size(), 2);
c.remove("d");
ASSERT_EQ(c.size(), 1);
c.remove("e");
ASSERT_EQ(c.size(), 0);
}

/* Test 8 - checks that insert works and 
tests the keys function.
*/
TEST(BasicCollectionTest, PrintKeys) {
HashTableCollection <string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert ("c", 30.0);
c.insert ("d", 40.0);
c.insert ("e", 50.0);
vector<string> ks;
c.keys(ks);
vector<string> empt;
c.keys(empt);
ASSERT_EQ(empt,ks);
}

/*
Test 9 - checks the copy/equal/destructor
*/
TEST(BasicCollectionTest, CopyAndEqual) {
HashTableCollection <string, double> c;
c.insert("a", 10.0);
c.insert("b", 20.0);
c.insert("b", 60.0);
c.insert("c", 30.0);
c.insert("d", 40.0);
c.insert("e", 50.0);
//c.print();
cout << endl;


HashTableCollection <string, double> a;
a = c;
a.remove("a");
a.remove("b");
a.remove("b");
//a.print();
c.~HashTableCollection();
}

int main(int argc, char ** argv)
{
  testing::InitGoogleTest(& argc, argv);
  return RUN_ALL_TESTS();
}
