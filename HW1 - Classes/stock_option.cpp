/*
Brian Steuber
CPSC 223-01
HW1
This stock_option.cpp file implements public functions with
private member variables defined in stock_option.h
*/

#include <iostream> 
#include <string>
#include "stock_option.h"

using namespace std;

//Constructor for StockOption
StockOption :: StockOption(string the_symbol) : Stock(the_symbol)
{

}

// Function that assigns private member variable strike_price to the_strike_price
void StockOption :: set_strike_price(double the_strike_price)
{
  strike_price = the_strike_price;
}

//Function that returns strike_price
double StockOption :: get_strike_price() const
{
  return strike_price;
}

//Function that returns the sell value of the option given a strike price
double StockOption :: sell_value() const
{
  return ((strike_price - get_purchase_price()) * get_holdings()) - (get_holdings() * get_share_value());
}


