/*
Brian Steuber
CPSC 223-01
HW2
This integer.cpp file implements public functions with
private member variables/functions defined in integer.h
*/

#include <iostream>
#include <string>
#include <vector>
#include "integer.h"

using namespace std;

//default constructor
Integer::Integer()
{
  digits.push_back(0);
  negative = false;  
}

//Dr. Bowers' constructor
Integer::Integer(string val)
{
  negative = false;
  int num = int(val.size());
  if (num == 0)
  {
    digits.push_back(0);
	return;
  }
  if (val[0] == '0' && num > 1)
  {
    digits.push_back(0);
	return;
  }
  for (int i = num - 1; i >= 0; --i)
  {
	char c = val[i];
	if (isdigit(c))
	{
	  digits.push_back(c - '0');
    }
	else
	{
	  digits.clear();
	  digits.push_back(0);
	  return;
	}
  }
}

//less than private member function
bool Integer::less_than(const digit_list &lhs, const digit_list &rhs) const
{
  int l = lhs.size();
  int r = rhs.size();
  if (l != r)
    return l < r; // checks to see if l < r
  for (int i = l - 1; i >= 0; i--)
  {
	if(lhs.at(i)<rhs.at(i)) // checks to see if lhs < rhs 
      return true;
  }
  return false;
}

//negation operator
Integer Integer::operator -() const
{
  Integer new_list = *this;
  if (new_list.negative)
	new_list.negative = false;
  else 
	new_list.negative = true;
  return new_list;
}

//binary addition operator 
Integer Integer::operator +(const Integer &rhs) const
{
  Integer new_list;
  if (this->negative && rhs.negative)
  {
    digit_list cpy = add(this->digits, rhs.digits);
    new_list.digits = cpy;
	new_list.negative = true;
	return new_list;
  }
  
  if (!this->negative && rhs.negative)
  {
	digit_list cpy = sub(this->digits, rhs.digits);
    new_list.digits = cpy;
	if (!less_than(rhs.digits, this->digits))
      new_list.negative = true;
    return new_list;
  }
  if (this->negative && !rhs.negative)
  {
	digit_list cpy = sub(rhs.digits, this->digits);
    new_list.digits = cpy;
	if (!less_than(this->digits, rhs.digits))
      new_list.negative = true;
    return new_list;
  }
  new_list.digits = new_list.add(this->digits, rhs.digits);
  return new_list;
}

//binary subtraction operator 
Integer Integer::operator -(const Integer &rhs) const
{ 
  Integer new_list;
  if (this->negative && rhs.negative)
  {
    digit_list cpy = sub(rhs.digits,this->digits);
    new_list.digits = cpy;
	new_list.negative = true;
	return new_list;
  }
  
  if (!this->negative && rhs.negative)
  {
	digit_list cpy = add(rhs.digits, this->digits);
    new_list.digits = cpy;
	if (!less_than(this->digits, rhs.digits))
      new_list.negative = true;
    return new_list;
  }
  if (this->negative && !rhs.negative)
  {
	digit_list cpy = add(this->digits, rhs.digits);
    new_list.digits = cpy;
	if (!less_than(rhs.digits, this->digits))
      new_list.negative = true;
    return new_list;
  }
  new_list.digits = new_list.sub(this->digits, rhs.digits);
  return new_list;
}

//less than operator
bool Integer::operator <(const Integer &rhs) const
{
  return less_than(this->digits, rhs.digits);	
}

//greater than operator 
bool Integer::operator >(const Integer &rhs) const
{
  return less_than(rhs.digits, this -> digits);
}

//equivalence operator 
bool Integer::operator ==(const Integer &rhs) const
{
  return !(less_than(this -> digits, rhs.digits)) && !(less_than(rhs.digits, this -> digits));	
}

//not equal to operator
bool Integer::operator !=(const Integer &rhs) const
{
  return less_than(this -> digits, rhs.digits) || less_than(rhs.digits, this -> digits);
}

//less than or equal to operator
bool Integer::operator <=(const Integer &rhs) const
{
  return less_than(this -> digits, rhs.digits) || (!(less_than(this -> digits, rhs.digits)) && !(less_than(rhs.digits, this -> digits)));
}

//greater than or equal to operator
bool Integer::operator >=(const Integer &rhs) const
{
  return less_than(rhs.digits, this -> digits) || (!(less_than(this -> digits, rhs.digits)) && !(less_than(rhs.digits, this -> digits)));
}

//add private member function
digit_list Integer::add(const digit_list &lhs, const digit_list &rhs) const
{
  int carry = 0;
  unsigned int i;
  digit_list new_list; 
  digit_list large_num;
  digit_list small_num;
  unsigned int l = lhs.size();
  unsigned int r = rhs.size();
  
  if (l != r)
  {
	if (l > r)
	{
      large_num = lhs;
	  small_num = rhs;
	}
	else 
	{
      large_num = rhs;
	  small_num = lhs;
	}
  }
  if (l == r) //equal case
  {
    for (i = 0; i < l && i < r; i++)
      {
	    int w = lhs.at(i) + rhs.at(i);
	    if (w + carry < 10)
        {		
          new_list.push_back(w);
		  carry = 0;
	    }
	    if (w + carry >= 10)
	    {
		  new_list.push_back(w + carry - 10);
	      carry = 1;
	    }
      } 
  }
  else 
  { 
    unsigned int m = small_num.size();
	unsigned int t = large_num.size();
	for (i = 0; i < m; i++)
    {
	  int y = small_num.at(i) + large_num.at(i);
	  if (y + carry < 10)
      {		
        new_list.push_back(y);
	    carry = 0;
	  }
	  if (y + carry >= 10)
	  {
		new_list.push_back(y + carry - 10);
	    carry = 1;
	  }
    } 
	for (i = m; i < t; i++)
    {
	  int z = large_num.at(i);
	  if (z + carry < 10)
      {		
        new_list.push_back(z);
		carry = 0;
	  }
	  if (z + carry >= 10)
	  {
		new_list.push_back(z + carry - 10);
	    carry = 1;
	  }
    } 
  }
  if (carry != 0)
  {
    new_list.push_back(1);
  }
  return new_list;
}
//sub private member function
digit_list Integer::sub(const digit_list &lhs, const digit_list &rhs) const
{
  int carry = 0;
  unsigned int i;
  digit_list new_list; 
  digit_list large_num;
  digit_list small_num;
  unsigned int l = lhs.size();
  unsigned int r = rhs.size();
  
  if (l != r)
  {
	if (l > r)
	{
      large_num = lhs;
	  small_num = rhs;
	}
	else 
	{
	  large_num = rhs;
	  small_num = lhs;
	}
  }
  if (l == r) //equal case 
  {
    for (i = 0; i < l && i < r; i++)
      {
	    int w = lhs.at(i) - rhs.at(i);
	    if (w + carry < 10 && w + carry >= 0)
        {		
          new_list.push_back(w);
		  carry = 0;
	    }
	    if (w + carry < 0)
	    {
		  new_list.push_back(w - carry + 10);
	      carry = 1;
	    }
      } 
  }
  else 
  { 
    unsigned int m = small_num.size();
	unsigned int t = large_num.size();
	for (i = 0; i < m; i++) 
    {
	  int y = large_num.at(i) - small_num.at(i);
	  if (y + carry < 10 && y + carry >= 0)
      {		
        new_list.push_back(y);
	    carry = 0;
	  }
	  if (y + carry < 0)
	  {
		new_list.push_back(y - carry + 10);
	    carry = 1;
	  }
    } 
	for (i = m; i < t; i++) 
    {
	  int z = large_num.at(i);
	  if (z + carry < 10 && z + carry >= 0)
      {		
        new_list.push_back(z-carry);
		carry = 0;
	  }
	  if (z + carry < 0)
	  {
		new_list.push_back(z - carry + 10);
	    carry = 1;
	  }
    } 
  }
  //loop to take out leftover 0
  for (i = 0; i < new_list.size(); i++)
  {
	if (new_list.at(new_list.size()-1) == 0)
    {
      new_list.erase(new_list.begin() + new_list.size()-1);
    }
  }
  return new_list;
}

//outputs an Integer to ostream
ostream& operator <<(ostream &out, const Integer &val)
{	
  int tmp;	
  digit_list cpy = val.digits;	
  unsigned int size = cpy.size();
  for (unsigned int i = 0; i < size / 2; i++)
  {
	tmp = cpy.at(i);
	cpy.at(i) = cpy.at(size-1-i);
	cpy.at(size-1-i) = tmp;
  }
  for (unsigned int j = 0; j < size; j++)
  {
	out << cpy.at(j);
  }
  return out;
}
  
