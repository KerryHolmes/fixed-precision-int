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
* The comments in this file are to specify the purpose and effects of the 
* member functions and variables. Runtime analysis is contained in the cpp file
* along with actual function definitions.
*******************************************************************************/

#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>
#include <vector>

class Number{
//The digits of the number are stored in this vector as unsigned integers.
//It is private to maintain the integrity of its data.
  std::vector<unsigned int> digits;
//This member represents the current base of the number.
  unsigned int base; 
//These operators allow access to the members of the digits vector from
//the class itself, rather than the dot accessor. They are private
//to ensure that the vector is not manipulated directly
  unsigned int& operator[](int place);
  unsigned int operator[](int place) const;

public:
//constructs the number to have a 1element vector with every digit at 0
//And a base of two.
  Number(); 
//Constructs a new number using the vector copy constructor
  Number(const Number& c);
//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit create a 
//vector that is just large enough to hold the value provided.
//The array is stored least significant to most significant, so there is no 
//need to reverse the result of the repeated division. As the number can be an
//arbitrary base, the base must also be provided.
  Number(int decimal, int use_base);
//Copy assignment operator works by using the vector assignment operator to
//replace the current vector for this object. The base is also taken from the
//reference vector, making a complete copy of the reference.
  Number& operator=( const Number& c);
//This assignment operator converts a decimal number to a type Number via 
//repeated division as above
  Number& operator=(int decimal);
//Left shift 
  Number operator<<(int shift);

  Number& operator<<=(int shift);

  Number operator>>( int shift);

  Number& operator>>=( int shift);

  Number operator+( Number num);

  Number& operator+=( Number num);

  Number operator-( Number num);

  Number& operator-=( Number num);

  Number operator*( Number num);

  Number& operator*=( Number num);

  Number operator/( Number num);

  Number& operator/=( Number num);

  Number operator%( Number num);

  Number& operator%=( Number num);

  Number recur_modulus(Number lhs, const Number& rhs);

  Number recur_division( Number lhs, const Number& rhs);

  unsigned int mst_sig_dig();

  unsigned int mst_sig_dig() const;

  unsigned int convert_decimal();

  void double_num();

  Number divide_by_two();

  void half();

  Number multiply_by_two();

  void match_length( Number& lhs, Number& rhs);

 friend bool operator==( const Number& lhs, const Number& rhs);
 friend bool operator<( const Number& lhs, const Number& rhs);
 friend bool operator==( const Number& lhs, const int rhs);
 friend std::istream& operator>>(std::istream &in, Number& num);
 friend std::ostream& operator<<(std::ostream &out, const Number& num);
 
};

bool operator>( const Number& lhs, const Number& rhs);
bool operator!=( const Number& lhs, const Number& rhs);
bool operator<=( const Number& lhs, const Number& rhs);
bool operator>=( const Number& lhs, const Number& rhs);

unsigned int add_arbitrary( int& lhs, const int& rhs, int base);
unsigned int sub_arbitrary( int& lhs, const int& rhs, int base);

#endif