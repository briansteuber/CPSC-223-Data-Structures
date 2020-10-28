/*
Brian Steuber
CPSC 223-01
HW9
This hw9_perf.cpp allows me to test
Insert, Remove, Find, Range, and 
Sort averages from the 10k, 20k, 30k,
40k, 50k txt files
*/


#include <iostream>
#include "bst_collection.h"
#include "test_driver.h"

using namespace std;

int main(int argc, char** argv)
{
  //check command-line arguments 
  if (argc != 2)
  {
    cout << "usage: " << argv[0] << " filename" << endl;
	return 1;
  }
  
  //run basic performance test 
  BSTCollection<string, double> test_collection;
  TestDriver<string, double> driver(argv[1], &test_collection);
  driver.run_tests();
  driver.print_results();
}