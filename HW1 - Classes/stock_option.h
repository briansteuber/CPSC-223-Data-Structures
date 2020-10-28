/*
Brian Steuber
CPSC 223-01
HW1
This stock_option.h file contains public functions 
and private member variables that are implemented 
in stock_option.cpp
*/

#ifndef STOCK_OPTION_H
#define STOCK_OPTION_H
#include <string>
#include "stock.h"

using namespace std;

class StockOption : public Stock
{
 public:
   // crate a stock option with the given symbol
   StockOption(string the_symbol);

   // set the strike price per share  
   void set_strike_price(double the_strike_price);

   // strike price per share
   double get_strike_price() const ;

   // the net worth of the option
   virtual double sell_value() const ;

 private:
   double strike_price = 0; // price to sell per holding
};

#endif 