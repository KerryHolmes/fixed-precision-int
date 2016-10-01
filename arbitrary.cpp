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
#include "aribitrary.hpp"

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

Number Number::operator+( const Number& num)
{
  int carry = 0;
  Number sum(*this);
  if(sum.digits.size() < std::min(sum.digits.size(), num.digits.size()))
  {
      for(int i = sum.digits.size(); i < num.digits.size(); ++i)
         sum.digits.push_back(0);
  }
  elseif(num.digits.size() < std::min(sum.digits.size(), num.digits.size()))
  {
      for(int i = num.digits.size(); i < sum.digits.size(); ++i)
         num.digits.push_back(0);
  }
  for(int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( add_arbitrary(sum.digits[i], carry) ^ add_arbitrary(sum.digits[i], num.digits[i]) );
  }

  if(carry)
         sum.digits.push_back(carry);

  return sum;
}


Number& Number::operator+=( const Number& num)
{
  int carry = 0;
  if(digits.size() < std::min(digits.size(), num.digits.size()))
  {
      for(int i = digits.size(); i < num.digits.size(); ++i)
         digits.push_back(0);
  }
  elseif(num.digits.size() < std::min(digits.size(), num.digits.size()))
  {
      for(int i = num.digits.size(); i < digits.size(); ++i)
         num.digits.push_back(0);
  }
  for(int i = 0; i < digits.size(); ++i)
  {
    carry = ( add_arbitrary(digits[i], carry) ^ add_arbitrary(digits[i], num.digits[i]) );
  }

  if(carry)
         digits.push_back(carry);

  return *this;
}

Number Number::operator-( const Number& num)
{
  int carry = 0;
  Number sum(*this);
  if(sum.digits.size() < std::min(digits.size(), num.digits.size()))
  {
    throw exception("Negative Number");
  }
  elseif(num.digits.size() < std::min(sum.digits.size(), num.digits.size()))
  {
    for(int i = num.digits.size(); i < sum.digits.size(); ++i)
    {
      num.digits.push_back(0);
    }
  }
  for(int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( sub_binary(sum.digits[i], carry) ^ sub_binary(sum.digits[i], num.digits[i]) );
  }
  if(carry)
  {
    throw exception("Negative Number");
  }

  return sum;
}

Number Number::operator-=( const Number& num)
{
  int carry = 0;
  if(digits.size() < std::min(digits.size(), num.digits.size()))
  {
    throw exception("Negative Number");
  }
  elseif(num.digits.size() < std::min(digits.size(), num.digits.size()))
  {
    for(int i = num.digits.size(); i < digits.size(); ++i)
    {
      num.digits.push_back(0);
    }
  }
  for(int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( sub_arbitrary(sum.digits[i], carry) ^ sub_arbitrary(sum.digits[i], num.digits[i]) );
  }
  if(carry)
  {
    throw exception("Negative Number");
  }

  return sum;
}

int add_arbitrary( int& lhs, const int& rhs, int base)
{
  if( base > (lhs + rhs)  )
  {
    lhs += rhs;
    return 0;
  }
  else
  {
    lhs += (lhs + rhs) - base;
    return 1;
  }
}

int sub_arbitrary( int& lhs, const int& rhs, int base)
{
  if( 0 > (lhs - rhs) )
  {
    lhs = (base + lhs) - rhs;
    return 1;
  }
  else
  {
    lhs -= rhs;
    return 0;
  }
}

int Number::convert_decimal()
{
  int sum = 0;
  int power = 1;
  for( int i = 0; i < digits.size(); i++)
  {
     sum += digits[i] * power;
     power *= 2;
  }
  return sum;
}

Number& Number::half()
{
  for(int i = digits.size(); i > 0; --i)
  {
    digits[i] = digits[i] / 2;
    digits[i-1] *= digits[i] % 2;
  }
  digits[0] = digits[0] / 2;
  returns *this;
}

Number Number::divide_by_two()
{
  Number temp(*this);
  for(int i = digits.size(); i > 0; --i)
  {
    temp.digits[i] = temp.digits[i] / 2;
    temp.digits[i-1] *= temp.digits[i] % 2;
  }
  temp.digits[0] = temp.digits[0] / 2;
  returns temp;
}

bool operator==( const Number& lhs, const Number& rhs)
{
  if(lhs.mst_sig_bit() != rhs.mst_sig_bit())
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