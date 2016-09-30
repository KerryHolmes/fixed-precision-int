/***********************************************************************
* Project 1: Fixed Precision Binary integer
*
* Author: Kerry Holmes
*         kjh80@zips.uakron.edu
*
* Purpose: TODO Write the purpose
*********************************************************************/

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <cassert>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Number{
    std::vector<int> digits; //The digits of the number are stored in this vector
    public:
  Number(); //constructs the number to have a 2048 vector with every digit at 0
  Number(Number const &c);//constructs a new number using the vector copy constructor
//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
  Number(int decimal);
//Copy assignment operatior works by using the vector assignment operator to replace the
//current vector for this object
  Number& operator=( const Number& c);
//This assignment operator converts a decimal number to a type Number via repeated division as above
  Number& operator=( int decimal);

  Number operator<<( const int shift);

  Number& operator<<=(const int shift);

  Number operator>>( const int shift);

  Number& operator>>=(const int shift);

  Number operator+( const Number& num);

  Number& operator+=( const Number& num);

  Number operator-( const Number& num);

  Number& operator-=( const Number& num);

//Multiplication using russian peasant method
  Number operator*( const Number& num);

  Number& operator*=( const Number& num);

 friend bool operator==( const Number& lhs, const Number& rhs);
 friend bool operator<( const Number& lhs, const Number& rhs);

};

bool operator>( const Number& lhs, const Number& rhs);
bool operator!=( const Number& lhs, const Number& rhs);
bool operator<=( const Number& lhs, const Number& rhs);
bool operator>=( const Number& lhs, const Number& rhs);

#endif