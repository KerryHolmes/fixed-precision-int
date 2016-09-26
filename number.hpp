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
  :digits(2048)
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



};

#endif
