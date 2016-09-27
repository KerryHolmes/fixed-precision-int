/***********************************************************************
* Project 1: Fixed Precision Binary integer
*
* Author: Kerry Holmes
*         kjh80@zips.uakron.edu
*
* Purpose: TODO Write the purpose
*********************************************************************/
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "arithmatic.hpp"

#ifndef NUMBER_HPP
#define NUMBER_HPP

class Number{
  
  std::vector<int> digits; //The digits of the number are stored in this vector

  public:
  Number() //constructs the number to have a 2048 vector with every digit at 0
  :digits(2048,0)
  {}

  Number(Number const &c)//constructs a new number using the vector copy constructor
  :digits(c.digits)
  {}

  Number(int decimal)
  :digits(2048,0)
  {
     int mst_sig_bit = std::floor(std::log2(decimal));
     for( int i = 0; i <= mst_sig_bit; ++i)
     {
        digits[i] = decimal % 2;
        decimal = decimal / 2;
     }
  }

  Number& operator=( const Number& c)
  {
    digits = c.digits;
    return *this;
  }

  Number& operator=( int decimal)
  {
    digits = std::vector<int>(2048,0);
    int mst_sig_bit = std::floor(std::log2(decimal));
     for( int i = 0; i <= mst_sig_bit; ++i)
     {
        digits[i] = decimal % 2;
        decimal = decimal / 2;
     }
     return *this;
  }

  Number operator+( const Number& num)
  {
    int carry = 0;
    Number sum(*this);
    for(int i = 0; i < 2048; ++i)
    {
      carry = add_binary(sum.digits[0], carry);
      carry = add_binary(sum.digits[0], num.digits[0]);
    }
    return sum;
  }

  Number operator-( const Number& num)
  {
    int carry = 0;
    Number sum(*this);
    for(int i = 0; i < 2048; ++i)
    {
      carry = sub_binary(sum.digits[0], carry);
      carry = sub_binary(sum.digits[0], num.digits[0]);
    }
    return sum;
  }
 
 friend bool operator==( const Number& lhs, const Number& rhs);
 friend bool operator<( const Number& lhs, const Number& rhs);
 friend bool operator>( const Number& lhs, const Number& rhs);
};

bool operator==( const Number& lhs, const Number& rhs)
{
    for( int i = 2047; i >= 0; i++)
    {
      if(lhs.digits[i] != rhs.digits[i])
        return false;
    }
    return true;
}

bool operator!=( const Number& lhs, const Number& rhs)
{
  return !(lhs == rhs);
}

bool operator<( const Number& lhs, const Number& rhs)
{
    return std::lexicographical_compare(lhs.digits.begin(), lhs.digits.end(),
                                        rhs.digits.begin(), rhs.digits.end());
}

bool operator>( const Number& lhs, const Number& rhs)
{
    return std::lexicographical_compare(rhs.digits.begin(), rhs.digits.end(),
                                        lhs.digits.begin(), lhs.digits.end());
}

bool operator<=( const Number& lhs, const Number& rhs)
{
    return !(lhs > rhs);
}

bool operator>=( const Number& lhs, const Number& rhs)
{
    return !(lhs < rhs);
}

#endif
