/*******************************************************************************
* Project 1: Fixed Precision Binary integer
*
* Author: Kerry Holmes
*         kjh80@zips.uakron.edu
*
* Purpose: To create a class that can represent a number of arbitrary base and
* precision. The class supports the basic operations of numbers, such as 
* addition, subtraction, multiplication, division, and modulus. This 
* implementation only supports positive numbers.
*
* The comments in this file are to specify the runtime analysis of this 
* implementation of the member functions and operators. The purpose of the 
* functions and variables can be found in the hpp file accompanied by the 
* function declarations.
*******************************************************************************/
#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include "arbitrary.hpp"

Number::Number() //constructs the number to have a size 1 vector with the only digit at 0
:digits(1,0), base(2) //The base defaults to being two
{}

Number::Number(const Number& c)//constructs a new number using the vector copy constructor
:digits(c.digits), base(c.base)
{}

//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
Number::Number(unsigned int decimal, int use_base)
:digits(), base(use_base)
{
   if(decimal == 0)
    digits = std::vector<int>(0,1);
  else
  {
   digits = std::vector<int>(std::floor((std::log(decimal)
                              /std::log(use_base)))+1,0);
   for(unsigned int i = 0; decimal > 0; ++i)
   {
      digits[i] = decimal % base;
      decimal = decimal / base;
   }
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
Number& Number::operator=(unsigned int decimal)
{
  if(decimal == 0)
    digits = std::vector<int>(0,1);
  else
  {
  digits = std::vector<int>(std::floor((std::log(decimal)/std::log(base)))+1,0);
   for(unsigned int i = 0; decimal > 0; ++i)
   {
      digits[i] = decimal % base;
      decimal = decimal / base;
   }
  }
   return(*this);
}

Number Number::operator<<( int shift )
{
  Number result(*this);
  result.digits.insert(result.digits.begin(), shift, 0);
  return result;
}

Number& Number::operator<<=( int shift )
{
  digits.insert(digits.begin(), shift, 0);
  return *this;
}

Number Number::operator>>( int shift )
{
  Number result(*this);
  if(shift >= result.digits.size())
  {
    result.digits.clear();
    result.digits.push_back(0);
    return result;
  }
  for( int i = shift; i < digits.size(); ++i)
    result.digits[i-shift] = result.digits[i];

  for(; shift > 0; --shift)
    result.digits.pop_back();
    
  return result;
}

Number& Number::operator>>=( int shift )
{
  if(shift >= digits.size())
  {
    digits.clear();
    digits.push_back(0);
    return *this;
  }
  for( int i = shift; i < digits.size(); ++i)
    digits[i-shift] = digits[i];

  for(; shift > 0; --shift)
    digits.pop_back();

  return *this;
}

Number Number::operator+( Number num)
{
  assert(base == num.base);
  int carry = 0;
  Number sum(*this);
  match_length(sum, num);
  for( int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( add_arbitrary(sum.digits[i], carry, sum.base) 
            + add_arbitrary(sum.digits[i], num.digits[i], sum.base) );
  }
  if(carry)
    sum.digits.push_back(carry);
  return sum;
}


Number& Number::operator+=( Number num)
{
  assert(base == num.base);
  int carry = 0;
  match_length(*this, num);
  for( int i = 0; i < digits.size(); ++i)
  {
    carry = ( add_arbitrary(digits[i], carry, base) 
              + add_arbitrary(digits[i], num.digits[i], base) );
  }
  if(carry)
     digits.push_back(carry);
  return *this;
}

Number Number::operator-( Number num)
{
  assert(base == num.base);
  assert(*this > num);
  int carry = 0;
  Number sum(*this);

  if(num.digits.size() < sum.digits.size())
    for(int i = num.digits.size(); i < sum.digits.size(); ++i)
      num.digits.push_back(0);

  for(unsigned int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( sub_arbitrary(sum.digits[i], carry, sum.base) 
            + sub_arbitrary(sum.digits[i], num.digits[i], sum.base) );
  }
  return sum;
}

Number& Number::operator-=( Number num)
{
  assert(base == num.base);
  unsigned int carry = 0;
  assert(*this > num);

  if(num.digits.size() < digits.size() )
    for(unsigned int i = num.digits.size(); i < digits.size(); ++i)
      num.digits.push_back(0);

  for(unsigned int i = 0; i < digits.size(); ++i)
  {
    carry = ( sub_arbitrary(digits[i], carry, base) 
            + sub_arbitrary(digits[i], num.digits[i], base) );
  }
  return *this;
}

Number Number::operator*( Number num)
{
  assert(base == num.base);
  Number temp(*this);
  Number product(0,base);
  while(num.digits[num.mst_sig_dig()] != 0)
  {
    if(num.digits[0] % 2 == 1 )
    {
      product += temp;
    }
    temp.double_num();
    num.half();
  }
  return product;
}

Number& Number::operator*=( Number num)
{
  assert(base == num.base);
  Number product(0,base);
  while(num.digits[num.mst_sig_dig()] != 0)
  {
    if(num.digits[0] % 2 == 1 )
    {
      product += *this;
    }
    double_num();
    num.half();
  }
  *this = product;
  return *this;
}

Number Number::operator/(Number num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  return recur_division(temp, num);
}

Number& Number::operator/=(Number num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_division(*this, num);
  return *this;
}

Number Number::operator%(Number num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  return recur_modulus(temp, num);
}

Number& Number::operator%=(Number num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_modulus(*this, num);
  return *this;
}

Number Number::recur_modulus(Number lhs, const Number& rhs)
{
  if(lhs < rhs)
    return lhs;
  return recur_modulus(lhs-rhs, rhs);
}

Number Number::recur_division( Number lhs, const Number& rhs)
{
  if(lhs < rhs)
    return Number(0, lhs.base);
  return (Number(1,lhs.base) + recur_division(lhs-rhs, rhs));
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
    lhs = (lhs + rhs) - base;
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
  for(int i = 0; i < digits.size(); ++i)
  {
     sum += digits[i] * power;
     power *= base;
  }
  return sum;
}

void Number::double_num()
{
  int carry = 0;
  for(int i = 0; i < digits.size(); ++i)
  {
    digits[i] *= 2;
    digits[i] += carry;
    carry = digits[i] / base;
    digits[i] = digits[i] % base;
  }
  if(carry)
    digits.push_back(carry);
}

Number Number::multiply_by_two()
{
  Number temp(*this);
  int carry = 0;
  for(int i = 0; i < temp.digits.size(); ++i)
  {
    temp.digits[i] *= 2;
    temp.digits[i] += carry;
    carry = temp.digits[i] / temp.base;
    temp.digits[i] = temp.digits[i] % temp.base;
  }
  if(carry)
    temp.digits.push_back(carry);
  return temp;
}

void Number::half()
{
  for(int i = mst_sig_dig(); i > 0; --i)
  {
    digits[i-1] += base * (digits[i] % 2);
    digits[i] = digits[i] / 2;
  }
  digits[0] = digits[0] / 2;
  while(digits[mst_sig_dig()] == 0 && digits.size() > 1)
  {
    digits.pop_back();
  }
}

Number Number::divide_by_two()
{
  Number temp(*this);
  for(int i = temp.mst_sig_dig(); i > 0; --i)
  {
    temp.digits[i-1] += base * (temp.digits[i] % 2);
    temp.digits[i] = temp.digits[i] / 2;
  }
  temp.digits[0] = temp.digits[0] / 2;
  while(temp.digits[temp.mst_sig_dig()] == 0 && temp.digits.size() > 1)
  {
    temp.digits.pop_back();
  }
  return temp;
}

bool operator==( const Number& lhs, const Number& rhs)
{
  assert(lhs.base == rhs.base);
  if(lhs.digits.size() != rhs.digits.size())
  {
    return false;
  }
  for(int i = lhs.mst_sig_dig(); i >= 0; --i)
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
  if( lhs.digits.size() < rhs.digits.size() )
  {
    return true;
  }
  else if(lhs.digits.size() > rhs.digits.size())
  {
     return false;
  }
  for(int i = lhs.mst_sig_dig(); i >= 0; --i)
  {
    if(lhs.digits[i] < rhs.digits[i])
      return true;
    if(lhs.digits[i] > rhs.digits[i])
     return false;
  }
  return false;

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

int Number::mst_sig_dig()
{
  return digits.size()-1;
}

int Number::mst_sig_dig() const
{
  return digits.size()-1;
}

int& Number::operator[]( int place)
{
  return digits[place];
}

int Number::operator[]( int place) const
{
  return digits[place];
}

std::istream& operator>>(std::istream &in, Number& num)
{
  unsigned int temp;
  num.digits.clear();
  in >> num.base;
  std::string line;
  std::getline(in, line);
  std::istringstream stream(line);
  while(stream >> temp)
  {
   assert(temp < num.base);
   num.digits.push_back(temp);
  }
  std::reverse(num.digits.begin(), num.digits.end());
  while(num[num.mst_sig_dig()] == 0)
       num.digits.pop_back();
  return in;
}
 std::ostream& operator<<(std::ostream &out, const Number& num)
{
  for(int i = num.mst_sig_dig(); i >= 0; --i)
  {
     out << num[i];
     out << " ";
  }
  return out;
}