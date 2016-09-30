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

  Number::Number() //constructs the number to have a 2048 vector with every digit at 0
  :digits(2048,0)
  {}

  Number::Number(Number const &c)//constructs a new number using the vector copy constructor
  :digits(c.digits)
  {}
//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
  Number::Number(int decimal)
  :digits(2048,0)
  {
     int mst_sig_bit = std::floor(std::log2(decimal));
     for( int i = 0; i <= mst_sig_bit; ++i)
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
    digits = std::vector<int>(2048,0);
    int mst_sig_bit = std::floor(std::log2(decimal));
     for( int i = 0; i <= mst_sig_bit; ++i)
     {
        digits[i] = decimal % 2;
        decimal = decimal / 2;
     }
     return *this;
  }

  Number Number::operator<<( const int shift )
  {
    Number result(*this);
    for(shift; shift > 0; --shift)
    {
        for(int i = 2046; i >= 0; --i)
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
        for(int i = 2046; i >= 0; --i)
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
        for(int i = 1; i <= 2047; ++i)
        {
          result.digits[i-1] = result.digits[i];
        }
        result.digits[2047] = 0;
    }
    return result;
  }

   Number& Number::operator>>=( const int shift )
  {
    for(shift; shift > 0; --shift)
    {
        for(int i = 1; i <= 2047; ++i)
        {
          digits[i-1] = digits[i];
        }
        digits[2047] = 0;
    }
    return *this;
  }

  Number Number::operator+( const Number& num)
  {
    int carry = 0;
    Number sum(*this);
    for(int i = 0; i < 2048; ++i)
    {
      carry = ( add_binary(sum.digits[i], carry) ^ add_binary(sum.digits[i], num.digits[i]) );
    }
    return sum;
  }


  Number& Number::operator+=( const Number& num)
  {
    int carry = 0;
    for(int i = 0; i < 2048; ++i)
    {
      carry = ( add_binary(digits[i], carry) ^ add_binary(digits[i], num.digits[i]) );
    }
    return *this;
  }

  Number Number::operator-( const Number& num)
  {
    int carry = 0;
    Number sum(*this);
    for(int i = 0; i < 2048; ++i)
    {
      carry = ( sub_binary(sum.digits[i], carry) ^ sub_binary(sum.digits[i], num.digits[i]) );
    }
    return sum;
  }

  Number& Number::operator-=( const Number& num)
  {
    int carry = 0;
    for(int i = 0; i < 2048; ++i)
    {
      carry = ( sub_binary(digits[i], carry) ^ sub_binary(digits[i], num.digits[i]) );
    }
    return *this;
  }

//Multiplication using russian peasant method
  Number Number::operator*( const Number& num)
  {
    Number temp(*this);
    Number product;
    int counter = to_decimal(num);
    while (counter > 0)
    {
      if( num.digits[0] & 1)
        {
          product += temp;
        }
      counter = counter / 2;
      num >>= 1;
      temp <<= 1;
    }
    return product;
  }

  Number& Number::operator*=( const Number& num)
  {
    Number temp(*this);
    Number product;
    int counter = to_decimal(num);
    while (counter > 0)
    {
      if( num.digits[0] & 1)
        {
          product += temp;
        }
      counter = counter / 2;
      num >>= 1;
      temp <<= 1;
    }
    digits = product;
    return (*this);
  }
 
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

std::ostream& operator<<(std::ostream& os, const Number& num)
{
  for(int i = 0; i < 2048; ++i)
  {
    os << num.digits[i];
  }
  return os;
}

std::istream& operator>>(std::istream& os, const Number& num)
{
  for(int i = 0; i < 2048; ++i)
  {
    os >> num.digits[i];
  }
  return os;
}

//This function is used to add two digits in binary
//The result is stored in the first digit, which is passed by reference
//The carry is the return value of the function
int add_binary( int& lhs, const int& rhs)
{
  lhs = lhs ^ rhs;
  return lhs * rhs;
}

//This function is used to subtract two digits in binary
//The result is stored in the first digit, which is passed by reference
//The carry is the return value of the function, The carry is for the denomenator
//Instead of borrowing from the next digit, the function increases the next number to 
//be subtracted from that digit
//If the numbers subtracted will be less than 0, 
//And the return value will be 1
int sub_binary( int& lhs, const int& rhs)
{
  if( 0 > (lhs - rhs)  )
  {
    lhs = (2 + lhs) - rhs;
    return 1;
  }
  else
  {
    lhs -= rhs;
    return 0;
  }
}

int to_decimal(const Number& num)
{
  int sum = 0;
  int power = 1;
     for( int i = 0; i <= 2048; ++i)
     {
        sum += digits[i] * power;
        power *= 2;
     }
     return sum;
}