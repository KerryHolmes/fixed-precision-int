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
#include "anumber.hpp"

Number::Number() //constructs the number to have a 1 digit vector with every digit at 0
:digits(1,0)
{}

Number::Number(Number const &c)//constructs a new number using the vector copy constructor
:digits(c.digits)
{}

//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
Number::Number(int decimal)
:digits(std::floor(std::log2(decimal))+1,0)
{
  for( int i = 0; i <= mst_sig_bit(); ++i)
  {
    digits[i] = decimal % 2;
    decimal = decimal / 2;
  }
}
//Copy assignment operatior works by using the vector assignment operator to replace the
//current vector for this object
Number& Number::operator=( const Number& c)
{
  digits = c.digits;
  return *this;
}
//This assignment operator converts a decimal number to a type Number via repeated division as above
Number& Number::operator=( int decimal)
{
  digits = std::vector<int>(std::floor(std::log2(decimal))+1,0);
  for( int i = 0; i <= mst_sig_bit(); ++i)
     {
        digits[i] = decimal % 2;
        decimal = decimal / 2;
     }
     return *this;
  }

int mst_sig_bit()
{
    return digits.size()-1;
}

Number Number::operator<<( int shift )
{
   Number result(*this);
   for(shift; shift > 0; --shift)
   {
     digits.push_back(digits[mst_sig_bit]);
     for(int i = mst_sig_bit()-1; i >= 0; --i)
     {
       result.digits[i+1] = result.digits[i];
     }
     digits[0] = 0;
    }
    return result;
  }
