/*
Brian Steuber
CPSC 223-01
HW1
This security.h file contains public functions 
and private member variables that are implemented 
in security.cpp
*/

#ifndef SECURITY_H
#define SECURITY_H
#include <string>

using namespace std;

class Security
{
 public:
   // create a security with the given symbol
   Security(string the_symbol);

   // company symbol
   string get_symbol() const;

   // update the current share value
   void set_share_value(double current_share_value);

   // current share value
   double get_share_value() const;

   // update the number of holdings
   void set_holdings(int number_of_holdings);

   // current number of holdings
   int get_holdings() const;

   // total current value of all holdings
   double market_worth() const;

 private:
   string symbol; // security identifier
   double share_value = 0; // each share ’s current market value
   int holdings = 0; // number of total shares of security held
};

#endif