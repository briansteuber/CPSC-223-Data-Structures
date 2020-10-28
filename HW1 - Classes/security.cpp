/*
Brian Steuber
CPSC 223-01
HW1
This security.cpp file implements public functions with
private member variables defined in security.h
*/

#include <iostream>
#include <string>
#include "security.h"

using namespace std;

// Security constructor that initializes private member variable: symbol
Security :: Security(string the_symbol) : symbol(the_symbol)
{

}

// Function that returns symbol
string Security :: get_symbol() const
{
	 return symbol;
}

// Function that assigns private member variable share_value to current_share_value
void Security :: set_share_value(double current_share_value)
{
	 share_value = current_share_value;
}

// Function that returns share_value
double Security :: get_share_value() const
{
	return share_value;
}

// Function that assigns private member variable holdings to number_of_holdings
void Security :: set_holdings(int number_of_holdings)
{
	 holdings = number_of_holdings;
} 

// Function that returns holdings
int Security :: get_holdings() const 
{
	return holdings;
}
 
// Function that returns the market worth by evaluating the product of holdings and share_value
double Security :: market_worth() const
{
	 return holdings * share_value;
}
