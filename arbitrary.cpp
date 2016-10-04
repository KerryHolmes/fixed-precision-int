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
#include "arbitrary.hpp"

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
   return(*this);
}

Number Number::operator<<( int shift )
{
  Number result(*this);
  for(; shift > 0; --shift)
  {
    result.digits.push_back(result[result.size()-1]);
    for(int i = digits.size()-2; i >= 0; --i)
     {
       result.digits[i+1] = result.digits[i];
     }
     result.digits[0] = 0;
  }
  return result;
}

Number& Number::operator<<=( int shift )
{
  for(; shift > 0; --shift)
  {
    digits.push_back(digits[digits.size()-1]);
    for(int i = digits.size()-2; i >= 0; --i)
    {
      digits[i+1] = digits[i];
    }
    digits[0] = 0;
  }
  return *this;
}

Number Number::operator>>( int shift )
{
  Number result(*this);
  for(; shift > 0; --shift)
  {
    for(int i = 1; i < digits.size(); ++i)
    {
      result.digits[i-1] = result.digits[i];
    }
    result.digits.pop_back();
  }
  return result;
}

Number& Number::operator>>=( int shift )
{
  for(; shift > 0; --shift)
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
  assert(base == num.base);
  int carry = 0;
  Number sum(*this);
  match_length(sum, num);
  for(int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( add_arbitrary(sum.digits[i], carry, sum.base) + add_arbitrary(sum.digits[i], num.digits[i], num.base) );
  }

  if(carry)
         sum.digits.push_back(carry);

  return sum;
}


Number& Number::operator+=( const Number& num)
{
  assert(base == num.base);
  int carry = 0;
  match_length(*this, num);
  for(int i = 0; i < digits.size(); ++i)
  {
    carry = ( add_arbitrary(digits[i], carry, base) + add_arbitrary(digits[i], num.digits[i], num.base) );
  }

  if(carry)
         digits.push_back(carry);

  return *this;
}

Number Number::operator-( const Number& num)
{
  assert(base == num.base);
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
    carry = ( sub_binary(sum.digits[i], carry) + sub_binary(sum.digits[i], num.digits[i]) );
  }
  if(carry)
  {
    throw exception("Negative Number");
  }

  return sum;
}

Number Number::operator-=( const Number& num)
{
  assert(base == num.base);
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
    carry = ( sub_arbitrary(sum.digits[i], carry) + sub_arbitrary(sum.digits[i], num.digits[i]) );
  }
  if(carry)
  {
    throw exception("Negative Number");
  }

  return sum;
}

Number Number::operator*( const Number& num)
{
  assert(base == num.base);
  Number temp(*this);
  Number product;
  while(num.digits.size() > 1 && num[num.mst_sig_digit()] > 0)
  {
    if(num.digits[0] % 2 == 1 )
    {
      product += temp;
    }
    double();
    num.half();
  }
  return product;
}

Number& Number::operator*=( const Number& num)
{
  assert(base == num.base);
  Number product;
  while(num.digits.size() > 1 && num[num.mst_sig_digit()] > 0)
  {
    if(num.digits[0] % 2 == 1 )
    {
      product += *this;
    }
    this->double();
    num.half();
  }
  *this = product;
  return *this;
}

Number Number::operator/(const Number& num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  return recur_division(temp, num);
}

Number& Number::operator/=(const Number& num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_division(*this, num);
  return *this;
}

Number Number::operator%(const Number& num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  return recur_modulus(temp, num);
}

Number& Number::operator%=(const Number& num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_modulus(*this, num);
}

Number Number::recur_modulus(Number& lhs, const Number& rhs)
{
  if(lhs < rhs)
    return lhs;
  return recur_modulus(lhs-rhs, rhs);
}

Number Number::recur_division( Number& lhs, const Number& rhs)
{
  if(lhs < rhs)
    return 0;
  return Number(1,lhs.base) + recur_division(lhs-rhs, rhs);
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

Number& Number::double()
{
  int carry = 0;
  for(int i = 0; i < digits.size(); ++i)
  {
    digits[i] *= 2;
    carry = (digits[i] += carry) / base;
    digits[i] = digits[i] % base;
  }
  if(carry)
    digits.push_back(carry);
  return *this;
}

Number Number::multiply_by_two()
{
  Number temp(*this);
  int carry = 0;
  for(int i = 0; i < temp.digits.size(); ++i)
  {
    temp.digits[i] *= 2;
    carry = (temp.digits[i] += carry) / temp.base;
    temp.digits[i] = temp.digits[i] % temp.base;
  }
  if(carry)
    temp.digits.push_back(carry);
  return temp;
}

Number& Number::half()
{
  for(int i = digits.size(); i > 0; --i)
  {
    digits[i] = digits[i] / 2;
    digits[i-1] += base * (digits[i] % 2);
  }
  digits[0] = digits[0] / 2;
  while(digits[mst_sig_bit()] == 0)
  {
    digits.pop_back();
  }
  returns *this;
}

Number Number::divide_by_two()
{
  Number temp(*this);
  for(int i = digits.size(); i > 0; --i)
  {
    temp.digits[i] = temp.digits[i] / 2;
    temp.digits[i-1] += base * (temp.digits[i] % 2);
  }
  temp.digits[0] = temp.digits[0] / 2;
  while(temp.digits[temp.mst_sig_bit()] == 0)
  {
    temp.digits.pop_back();
  }
  returns temp;
}

bool operator==( const Number& lhs, const Number& rhs)
{
  assert(lhs.base == rhs.base);
  if(lhs.mst_sig_bit() != rhs.mst_sig_bit())
  {
    return false;
  }
  for( int i = lhs.mst_sig_bit(); i >= 0; ++i)
  {
    if(lhs.digits[i] != rhs.digits[i])
    {
       return false;
    }
  }
  return true;
}

bool operator==( const Number& lhs, const int rhs)
{
  Number temp(rhs, lhs.base);
  return lhs == temp;

}

bool operator!=( const Number& lhs, const Number& rhs)
{
  return !(lhs == rhs);
}

bool operator<( const Number& lhs, const Number& rhs)
{
  assert(lhs.base == rhs.base);
  return std::lexicographical_compare(lhs.digits.begin(), lhs.digits.end(),
                                      rhs.digits.begin(), rhs.digits.end());
}

bool operator>( const Number& lhs, const Number& rhs)
{
    return rhs < lhs;
}

bool operator<=( const Number& lhs, const Number& rhs)
{
    return !(lhs > rhs);
}

bool operator>=( const Number& lhs, const Number& rhs)
{
    return !(lhs < rhs);
}

void Number::match_length( Number& lhs, Number& rhs)
{
  while(lhs.digits.size() < rhs.digits.size())
         lhs.digits.push_back(0);

  while(rhs.digits.size() < lhs.digits.size())
         rhs.digits.push_back(0);
}