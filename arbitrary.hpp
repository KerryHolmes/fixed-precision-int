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
  std::vector<int> digits;
//This member represents the current base of the number.
  int base; 
//These operators allow access to the members of the digits vector from
//the class itself, rather than the dot accessor. They are private
//to ensure that the vector is not manipulated directly
 int& operator[]( int place);
 int operator[]( int place) const;

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
  Number(unsigned int decimal, int use_base);
//Copy assignment operator works by using the vector assignment operator to
//replace the current vector for this object. The base is also taken from the
//reference vector, making a complete copy of the reference.
  Number& operator=(const Number& c);
//This assignment operator converts a decimal number to a type Number via 
//repeated division as above
  Number& operator=(unsigned int decimal);
//Left shift operator which will copy the sequence of digits forward by 
//the number of elements specified in shift, padding the beginning of the
//sequence with 0 and returning a temporary number. This does not change the 
//value of the number the operator is called on.
  Number operator<<( int shift);
//Left shift compound assignment operator which will copy the sequence of digits
//forward by the number of digits specified in shift, padding the beginning of 
//the sequence with 0 and returning a reference to this. This does change the 
//value of the number the operator is called on.
  Number& operator<<=( int shift);
//Right shift operator which will copy digits backwards in the vector by the
//number of digits specified in shift. If this amount is greater than the 
//number of digits, it will result in a 1 digits vector valued at 0. It returns
//a temporary number and does not modify the number it is called on.
  Number operator>>( int shift);
//Right shift compound assignment operator which will copy digits backwards in 
//the vector by the number of digits specified in shift. If this amount is
//greater than the number of digits, it will result in a 1 digits vector valued 
//at 0. It returns reference to this and does modify the number it is called on.
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

  int mst_sig_dig();

  int mst_sig_dig() const;

  int convert_decimal();

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

int add_arbitrary( int& lhs, const int& rhs, int base);
int sub_arbitrary( int& lhs, const int& rhs, int base);

#endif