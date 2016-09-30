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

Number::Number() //constructs the number to have a size 1 vector with the only digit at 0
:digits(1,0), base(2) //The base defaults to being two
{}

Number::Number(Number const &c)//constructs a new number using the vector copy constructor
:digits(c.digits), base(c.base)
{}

//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
Number::Number(int decimal, int use_base)
:digits(std::floor((std::log(decimal)/std::log(use_base))),0), base(use_base)
{
   for( int i = 0; decimal > 0; ++i)
   {
      digits[i] = decimal % base;
      decimal = decimal / base;
   }
}

//Copy assignment operatior works by using the vector assignment operator to replace the
//current vector for this object
Number& Number::operator=( const Number& c)
{
  digits = c.digits;
  base = c.base;
  return *this;
}

//This assignment operator converts a decimal number to a type Number via repeated division as above
Number& Number::operator=( int decimal)
{
  digits = std::vector<int>(std::floor((std::log(decimal)/std::log(base))),0);
   for( int i = 0; decimal > 0; ++i)
   {
      digits[i] = decimal % base;
      decimal = decimal / base;
   }
}

Number Number::operator<<( const int shift )
{
  Number result(*this);
  for(shift; shift > 0; --shift)
  {
    result.push_back(result[result.size()-1]);
    for(int i = digit.size()-2; i >= 0; --i)
     {
       result.digits[i+1] = result.digits[i];
     }
     result.digits[0] = 0;
  }
  return result;
}

Number& Number::operator<<=( const int shift )
{
  for(shift; shift > 0; --shift)
  {
    digits.push_back(digits[digits.size()-1]);
    for(int i = digit.size()-2; i >= 0; --i)
    {
      digits[i+1] = digits[i];
    }
    digits[0] = 0;
  }
  return *this;
}

Number Number::operator>>( const int shift )
{
  Number result(*this);
  for(shift; shift > 0; --shift)
  {
    for(int i = 1; i < digits.size(); ++i)
    {
      result.digits[i-1] = result.digits[i];
    }
    result.digits.pop_back();
  }
  return result;
}

Number& Number::operator>>=( const int shift )
{
  for(shift; shift > 0; --shift)
  {
    for(int i = 1; i < digits.size(); ++i)
    {
      digits[i-1] = digits[i];
    }
    digits.pop_back();
  }
  return *this;
}