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

#include <iostream>
#include <vector>

class Number{
    std::vector<int> digits; //The digits of the number are stored in this vector
    int base; //The decimal value of the current base
    int& operator[](int place);
    int operator[](int place) const;

public:
  Number(); //constructs the number to have a 2048 vector with every digit at 0
  Number(const Number& c);//constructs a new number using the vector copy constructor
//Converts and stores a base 10 value in this number through repeated division
//The logarithm is used to determine the most significant digit and stop writing there
//The array is stored least significant to most significant, so there is no need to 
//reverse the result of the repeated division
  Number(int decimal, int use_base);
//Copy assignment operatior works by using the vector assignment operator to replace the
//current vector for this object
  Number& operator=( const Number& c);
//This assignment operator converts a decimal number to a type Number via repeated division as above
  Number& operator=(int decimal);

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
 friend std::istream& operator>>(std::istream &in, const Number& num);
 friend std::ostream& operator<<(std::ostream &out, const Number& num);
 
};

bool operator>( const Number& lhs, const Number& rhs);
bool operator!=( const Number& lhs, const Number& rhs);
bool operator<=( const Number& lhs, const Number& rhs);
bool operator>=( const Number& lhs, const Number& rhs);

int add_arbitrary( int& lhs, const int& rhs, int base);
int sub_arbitrary( int& lhs, const int& rhs, int base);

#endif