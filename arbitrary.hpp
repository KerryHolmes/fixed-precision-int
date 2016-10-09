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
  Number operator<<(unsigned int shift);
//Left shift compound assignment operator which will copy the sequence of digits
//forward by the number of digits specified in shift, padding the beginning of 
//the sequence with 0 and returning a reference to this. This does change the 
//value of the number the operator is called on.
  Number& operator<<=(unsigned int shift);
//Right shift operator which will copy digits backwards in the vector by the
//number of digits specified in shift. If this amount is greater than the 
//number of digits, it will result in a 1 digits vector valued at 0. It returns
//a temporary number and does not modify the number it is called on.
  Number operator>>(unsigned int shift);
//Right shift compound assignment operator which will copy digits backwards in 
//the vector by the number of digits specified in shift. If this amount is
//greater than the number of digits, it will result in a 1 digits vector valued 
//at 0. It returns reference to this and does modify the number it is called on.
  Number& operator>>=(unsigned int shift);
//Adds two numbers of the same base, and returns a temporary number. It uses
//the helper function add_arbitrary to add individual digits. Does not modify
//the numbers used.
  Number operator+( Number num);
//Adds two numbers of the same base, and returns a reference to this number. 
//It uses the helper function add_arbitrary to add individual digits. It does 
//modify the numbers used.
  Number& operator+=( Number num);
//Subtracts two numbers of the same base, and returns a temporary number. 
//It uses the helper function sub_arbitrary to subtract individual digits. 
//Does not modify the numbers used.
  Number operator-( Number num);
//Subtracts two numbers of the same base, and returns a refernce to this number. 
//It uses the helper function sub_arbitrary to subtract individual digits. 
//It does modify the numbers used.
  Number& operator-=( Number num);
//Multiplication implemented using the Russian peasant method.
//The result is a temp number with the original numbers unmodified.
  Number operator*( Number num);
//Multiplication implemented using the Russian peasant method.
//The result is a refernce number with the original number modified.
  Number& operator*=( Number num);
//Divison recursively implemented by repeated subtraction. This takes place on a 
//temporary variable to not modify the original number. This relies on the 
//recur_division function.
  Number operator/( Number num);
//Divison recursively implemented by repeated subtraction. This takes place on  
//this variable and does modify the original number. This relies on the 
//recur_division function.
  Number& operator/=( Number num);
//Modulus recursively implemented by repeated subtraction. This takes place on a 
//temporary variable to not modify the original number. This relies on the 
//recur_modulus function.
  Number operator%( Number num);
//Modulus recursively implemented by repeated subtraction. This takes place on  
//this variable and does modify the original number. This relies on the 
//recur_modulus function.
  Number& operator%=( Number num);
//Recurively determines the value of the modulo expression via repeated 
//subtraction of the rhs from the lhs. Once lhs < rhs the value of lhs is 
//returned as the solution.
  Number recur_modulus(Number lhs, const Number& rhs);
//Recurively determines the value of the division expression via repeated 
//subtraction of the rhs from the lhs. Once lhs < rhs the value of lhs + the  
//number of recursions is returned as the solution.
  Number recur_division( Number lhs, const Number& rhs);
//Returns the most significant digit. In this implementation this should always
//be size minus 1.
  int mst_sig_dig();
//Returns the most significant digit. In this implementation this should always
//be size minus 1.
  int mst_sig_dig() const;
//Converts a number into decimal by addition of digits, with each digit being
//multiplied by the base to the power of its position in the vector
//EX: 1 0 0 1 -> 1*2^0 + 0*2 + 0*2^2 + 1*2^3
  int convert_decimal();
//Multiplies a number of any base by two and returns nothing. This does change
//the number it is called on. This is done using the properties of integers.
  void double_num();
//Does the same as the function above, but returns a temporary and does not 
//modify the number used.
  Number multiply_by_two();
//Divides a number of any base by two and returns nothing. This does change
//the number it is called on. This is done using the properties of integers.
  void half();
//Does the same as the function above, but returns a temporary and does not 
//modify the number used.
  Number divide_by_two();
//Makes two numbers have the same length by padding one of them with 0
//This is done temporarily to support math operators on numbers of different
//lengths.
  void match_length( Number& lhs, Number& rhs);
//Overload of the stream insertion operator. It will read in a fully formed 
//number from standard input. The first digit is taken as the base, and
//the digits are separated by a space. Digits read in until a newline is read.
  friend std::istream& operator>>(std::istream &in, Number& num);
//OVerload of the stream extraction operator. It will output all of the
//digits in the vector in reverse order. The vector is stored in reverse order,
//so this results in the output appearing in the correct format.
  friend std::ostream& operator<<(std::ostream &out, const Number& num);
//These functions use a lexicographical compare to determin the value of 
//these comparison operators. They are friends so that they can access private
//members.
  friend bool operator==( const Number& lhs, const Number& rhs);
  friend bool operator<( const Number& lhs, const Number& rhs);
  friend bool operator==( const Number& lhs, const int rhs);
 
};
//These comparison overloads function similarlly to their friend counter parts,
//yet they are implemented in terms of other operators, and thus do not need to
//be friends themselves
bool operator>( const Number& lhs, const Number& rhs);
bool operator!=( const Number& lhs, const Number& rhs);
bool operator<=( const Number& lhs, const Number& rhs);
bool operator>=( const Number& lhs, const Number& rhs);
//Adds two numbers of the same base and returns the carry of the operation.
//The lhs is modified and the right remains contanst. This is done to allow
//one return value and still compute the correct result.
int add_arbitrary( int& lhs, const int& rhs, int base);
//Subtracts two numbers of the same base and returns the carry of the operation.
//The lhs is modified and the right remains contanst. This is done to allow
//one return value and still compute the correct result. The carry is using
//the austruan method, meaning that the borrow is from the right operand instead
//of the left.
int sub_arbitrary( int& lhs, const int& rhs, int base);

#endif