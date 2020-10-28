/*
Brian Steuber
CPSC 223-01
HW1
This stock.cpp file implements public functions with
private member variables defined in stock.h
*/

#include <iostream> 
#include <string>
#include "stock.h"

using namespace std;

//Constructor for Stock 
Stock :: Stock(string the_symbol) : Security(the_symbol)
{
   
}

// Function that assigns private member variable purchase_price to the_purchase_price 
void Stock :: set_purchase_price(double the_purchase_price)
{
	purchase_price = the_purchase_price;
}

// Function that returns purchase_price
double Stock :: get_purchase_price() const
{
	return purchase_price;
}

// Function that returns the sell value by calculating the net worth of stock holdings
double Stock :: sell_value() const
{
	return (get_share_value() - get_purchase_price()) * get_holdings();
}
