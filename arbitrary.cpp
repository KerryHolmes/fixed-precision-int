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
//These two functions run in constant time, as they only return the element at
//the specified position for the vector, and vectors support access in
//constant time, or O(1).
int& Number::operator[]( int place)
{
  return digits[place];
}

int Number::operator[]( int place) const
{
  return digits[place];
}
//This constructor creates a vector with one digit that is a 0. Construction of
//a vector is linear with the container size, as the size will always be only 1,
//the complexity of this operation is constant. The complexity of assigning the 
//base to 2 is also constant. Overall this will run in constant time. O(1)
Number::Number() 
:digits(1,0), base(2) 
{}
//The copy constructor copies the base from c which is a trivial constant time 
//operation. The copying of the vector is done via the vector's copy constructor
//which will execute in linear time with the size of the array. Meaning overall,
//this operation will execute in linear time, or O(n).
Number::Number(const Number& c)
:digits(c.digits), base(c.base)
{}
//This function is similar to the one above. Two logarithms are used to 
//determine the size of the vector, which is then created using the vector
//fill constructor and copy assignment. Both of which will execute once in 
//linear time. Then, the for loop occurs, again once for each element in the 
//vector. In side the loop are four constant time operations. This results in 
//an overall complexity of O(n) + O(n) + O(n), which will simplify to O(n).
//There is an early exit case if the decimal number is 0, that will execute in
//constant time, however this is not considered typical.
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
//This operator is similar to the copy constructor, and will also perform is 
//linear time, O(n).
Number& Number::operator=( const Number& c)
{
  digits = c.digits;
  base = c.base;
  return *this;
}
//This will perform similarly to the constructor above that takes a decimal 
//number, does the same operations, and will also execute in linear time, O(n).
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
//This operator creates a temporary copy of the number it is called on in linear
//time. Then the vector insert function is called to fill the temporary vector
//with the amount of zeros specified before the least significant digit. Overall
//This results in a time complexity of O(n) + O(n), which is O(n) overall. There
//is the possibility of reallocation of the vector, which would result in 
//another linear operation, that would not change the overall complexity of the
//operation.
Number Number::operator<<(unsigned int shift )
{
  Number result(*this);
  result.digits.insert(result.digits.begin(), shift, 0);
  return result;
}
//This operator will perform largely the same as the above, sans the initial
//copy. In the end the result will be a linear operation, O(n).
Number& Number::operator<<=(unsigned int shift )
{
  digits.insert(digits.begin(), shift, 0);
  return *this;
}
//The operator begins with a copy of the number which will take place in linear
//time. There will be a number of constant pop_back and copy operations that
//will occur a number of times determined by the shift provided. O(s) and O(n-s)
//respectively, where s is the number of shits provided. Overall, these costs
//will be absorbed by the initial linear cost, resulting in a complexity of
//O(n). There is an early exit case if the shift is greater than the number of 
//digits, however it uses the clear function, which will still cause it to 
//execute in linear time.
Number Number::operator>>(unsigned int shift )
{
  Number result(*this);
  if(shift >= result.digits.size())
  {
    result.digits.clear();
    result.digits.push_back(0);
    return result;
  }
  for(unsigned int i = shift; i < digits.size(); ++i)
    result[i-shift] = result[i];

  for(; shift > 0; --shift)
    result.digits.pop_back();
    
  return result;
}
//This operator is similar to the one above, without the initial copy. This 
//means that the determining factor is the term O(n-s), as long as the shift is 
//strictly less than the number of digits. Otherwise it will be O(n).
Number& Number::operator>>=(unsigned int shift )
{
  if(shift >= digits.size())
  {
    digits.clear();
    digits.push_back(0);
    return *this;
  }
  for(unsigned int i = shift; i < digits.size(); ++i)
    digits[i-shift] = digits[i];

  for(; shift > 0; --shift)
    digits.pop_back();

  return *this;
}
//This operator starts with a constant size comparison and initialization. Then,
//a copy of the left operand is made in linear time. Next the match_size 
//function is called, which will execute in linear complexity based on the 
//difference in size of the two operands. After that, the for loop runs based on
//the size of number. This will execute using an assignment, an integer addition 
//and two calls to the add arbitrary function which, from its analysis below 
//executes in constant time. The result of that is a linear complexity loop. 
//After that is a branch and possibly a call to push_back, which are both 
//constant time, unless a reallocation is required. In that case, push_back 
//would execute in linear time. Overall this would yield 
//O(1)+O(n)+O(|n-m|)+O(n)+O(1)+O(n). The overall analysis thus yields O(n).
Number Number::operator+( Number num)
{
  assert(base == num.base);
  int carry = 0;
  Number sum(*this);
  match_length(sum, num);
  for(unsigned int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( add_arbitrary(sum[i], carry, sum.base) 
            + add_arbitrary(sum[i], num[i], sum.base) );
  }
  if(carry)
    sum.digits.push_back(carry);
  return sum;
}
//The analysis of this function is the same as above, sans the initail copy 
//which results in the runtime of O(n).
Number& Number::operator+=( Number num)
{
  assert(base == num.base);
  int carry = 0;
  match_length(*this, num);
  for(unsigned int i = 0; i < digits.size(); ++i)
  {
    carry = ( add_arbitrary(digits[i], carry, base) 
              + add_arbitrary(digits[i], num.digits[i], base) );
  }
  if(carry)
     digits.push_back(carry);
  return *this;
}
//This operator starts with a constant size comparison and initialization. Then,
//a check is made that the right operand is not greater than the left. As shown
//below, this is a linear time operation. After that a copy of the left operand 
//is made in linear time. Next the a for loop may be called, which will 
//execute in linear complexity based on the difference in size of the two 
//operands. After that, the for loop runs based on the size of number. 
//This will execute using an assignment, an integer addition and two calls
//to the sub arbitrary function which, from its analysis below executes in
//constant time. The result of that is a linear complexity loop. 
//This results in O(1)+O(n)+O(n)+O(|n-m|)+O(n)
//The overall analysis thus yields O(n).
Number Number::operator-( Number num)
{
  assert(base == num.base);
  assert(*this >= num);
  int carry = 0;
  Number sum(*this);

  if(num.digits.size() < sum.digits.size())
    for(unsigned int i = num.digits.size(); i < sum.digits.size(); ++i)
      num.digits.push_back(0);

  for(unsigned int i = 0; i < sum.digits.size(); ++i)
  {
    carry = ( sub_arbitrary(sum[i], carry, sum.base) 
            + sub_arbitrary(sum[i], num[i], sum.base) );
  }
  return sum;
}
//The analysis of this function is the same as above, sans the initail copy 
//which results in the runtime of O(n).
Number& Number::operator-=( Number num)
{
  assert(base == num.base);
  unsigned int carry = 0;
  assert(*this >= num);

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
//The operator starts with a constant time comparison. It is followed by two
//number constructions. The first is a copy construction which is linear, and 
//the other is a construction of 0 wihch is constant time. Next, the while loop
//will execute until the right operand is 0. This will occur log2(v) times,
//where v is the value of the right operand. Inside of this loop, there is an 
//addition, a call to double_num, and a call to half. All of which run in linear
//time. There is also a comparison which is constant. The final equation works
//into O(1)+O(n)+O(1)+O(log2(v)*(n+n+n+1)). This simplifies into O(log2(v)*n)
Number Number::operator*( Number num)
{
  assert(base == num.base);
  Number temp(*this);
  Number product(0,base);
  while(num[num.mst_sig_dig()] != 0)
  {
    if(num[0] % 2 == 1 )
    {
      product += temp;
    }
    temp.double_num();
    num.half();
  }
  return product;
}
//The analysis of this is largely the same as the operator above, minus one 
//initial copy operation. Resulting in a runtime of 
Number& Number::operator*=( Number num)
{
  assert(base == num.base);
  Number product(0,base);
  while(num[num.mst_sig_dig()] != 0)
  {
    if(num[0] % 2 == 1 )
    {
      product += *this;
    }
    double_num();
    num.half();
  }
  *this = product;
  return *this;
}
//This starts with a constant time comparison, and a linear construction of
//a temporary number. After that, the match_length function is called which
//will run in O(|n-m|) as shown in its own analysis below. Next, the recur_
//division function is called which based on its own analysis will run in 
//O(lhs/rhs(n)). The result of this operation will then be copied back into
//the temporary number. Finally the most significant digit of the number will
//be removed until it is a non zero number, or there is only one number left.
//This obviously can only occur n times in the worst case making it a linear 
//operation. The final equation is O(1)+O(n)+O(|n-m|)+O(lhs/rhs(n))+O(n)+O(n)
//The dominating term is O(lhs/rhs(n)) where lhs > rhs and O(n) otherwise.
Number Number::operator/(Number num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  temp = recur_division(temp, num);
  while(temp[temp.mst_sig_dig()] == 0 && temp.digits.size() > 1)
      temp.digits.pop_back();
  return temp;
}
//The analysis of this operator is roughly the same as the above.
//The difference is that there is no temporary copy constructed.
//Overall this will result in the runtime analysis of the recur_modulus
//function carrying thorugh, resulting in O(lhs/rhs(n)), where lhs > rhs 
//and O(n) otherwise.
Number& Number::operator/=(Number num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_division(*this, num);
  while(digits[mst_sig_dig()] == 0 && digits.size() > 1)
      digits.pop_back();
  return *this;
}
//This starts with a constant time comparison, and a linear construction of
//a temporary number. After that, the match_length function is called which
//will run in O(|n-m|) as shown in its own analysis below. Next, the recur_
//modulus function is called which based on its own analysis will run in 
//O(lhs/rhs(n)). The result of this operation will then be copied back into
//the temporary number. Finally the most significant digit of the number will
//be removed until it is a non zero number, or there is only one number left.
//This obviously can only occur n times in the worst case making it a linear 
//operation. The final equation is O(1)+O(n)+O(|n-m|)+O(lhs/rhs(n))+O(n)+O(n)
//The dominating term is O(lhs/rhs(n)) where lhs > rhs and O(n) otherwise.
Number Number::operator%(Number num)
{
  assert(base == num.base);
  Number temp(*this);
  match_length(temp, num);
  temp = recur_modulus(temp, num);
  while(temp[temp.mst_sig_dig()] == 0 && temp.digits.size() > 1)
      temp.digits.pop_back();
  return temp;
}
//The analysis of this operator is roughly the same as the above.
//The difference is that there is no temporary copy constructed.
//Overall this will result in the runtime analysis of the recur_modulus
//function carrying thorugh, resulting in O(lhs/rhs(n)), where lhs > rhs 
//and O(n) otherwise.
Number& Number::operator%=(Number num)
{
  assert(base == num.base);
  match_length(*this, num);
  *this = recur_modulus(*this, num);
  while(digits[mst_sig_dig()] == 0 && digits.size() > 1)
       digits.pop_back();
  return *this;
}
//This function is similar to the one below. It will be called recursively based
//on the difference in value of lhs and rhs. The number of recusrive calls is 
//the same as lhs / rhs. For each call there is a single subtraction which,
//by its analysis below, is linear. This causes a runtime complexity of
//O(lhs/rhs(n)).
Number Number::recur_modulus(Number lhs, const Number& rhs)
{
  if(lhs < rhs)
    return lhs;
  return recur_modulus(lhs-rhs, rhs);
}
//This function will be called recursively until the left operand is evaluated
//to be less than the right. This number varies based on the size of both 
//operands. The number of times it will run is equivalent to its value. It will
//be called lhs/rhs times. On each recursive call, there will be a constant time
//Number construction, an addition and a subtraction. This results in a time of
//O(lhs/rhs(n+n+1)) which simplifies to O(lhs/rhs(n)).
Number Number::recur_division( Number lhs, const Number& rhs)
{
  if(lhs < rhs)
    return Number(0, lhs.base);
  return (Number(1,lhs.base) + recur_division(lhs-rhs, rhs));
}
//These two function execute in constant time, as the call the constant time
//function of vectir size, and then return that value minus one.
int Number::mst_sig_dig()
{
  return digits.size()-1;
}

int Number::mst_sig_dig() const
{
  return digits.size()-1;
}
//This function will execute a series of constant operations in a for loop that
// execute exaclty once for every digit in the number. This results in the time
//complexity being linear O(n).
int Number::convert_decimal()
{
  int sum = 0;
  int power = 1;
  for(unsigned int i = 0; i < digits.size(); ++i)
  {
     sum += digits[i] * power;
     power *= base;
  }
  return sum;
}
//This function contains one loop that will iterate over every element in the
//vector and execute 8 primitive operations on the integer values of them.
//This results in the overall runtime complexity of O(n).
void Number::double_num()
{
  int carry = 0;
  for(unsigned int i = 0; i < digits.size(); ++i)
  {
    digits[i] *= 2;
    digits[i] += carry;
    carry = digits[i] / base;
    digits[i] = digits[i] % base;
  }
  if(carry)
    digits.push_back(carry);
}
//This function is nearly identical to the one above, with the added copy of
//a number at the beginning. This happens sequentially however and is additive
//to the complexity above. Resulting in a linear execution time O(n).
Number Number::multiply_by_two()
{
  Number temp(*this);
  int carry = 0;
  for(unsigned int i = 0; i < temp.digits.size(); ++i)
  {
    temp[i] *= 2;
    temp[i] += carry;
    carry = temp[i] / temp.base;
    temp[i] = temp[i] % temp.base;
  }
  if(carry)
    temp.digits.push_back(carry);
  return temp;
}
//This function will execute a for loop onve for ever digit in the number. The
//while loop after that will execute until the most significant digit is not 0
//or the size is one. These loops execute outside of eachother, and in the worst
//case will execute n times and n-1 times respectively. This results in O(n).
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
//The analysis of this function is the same as the above, with the added cost of
//a copy. This will not change the run time which will still be O(n).
Number Number::divide_by_two()
{
  Number temp(*this);
  for(int i = temp.mst_sig_dig(); i > 0; --i)
  {
    temp[i-1] += base * (temp[i] % 2);
    temp[i] = temp[i] / 2;
  }
  temp[0] = temp[0] / 2;
  while(temp[temp.mst_sig_dig()] == 0 && temp.digits.size() > 1)
  {
    temp.digits.pop_back();
  }
  return temp;
}
//This operator executes in linear time based on the difference in sizes of the
//numbers passed in. This is because the operation in each loop will run in 
//constant time, and only one loop will run. The loop that runs will do so
//until the two lenghts match. Thus the complexity is of O(|n-m|), where n and m
//are the sizes of the left and right operands respectively.
void Number::match_length( Number& lhs, Number& rhs)
{
  while(lhs.digits.size() < rhs.digits.size())
         lhs.digits.push_back(0);

  while(rhs.digits.size() < lhs.digits.size())
         rhs.digits.push_back(0);
}
//This operator starts with a few constant operations, and then uses the getline
//function from std cin to copy the input from cin to a string which is then
//converted into an istringstream. This stream is iterated over once for 
//each digit from input. The digits are then copied into the vector and reversed
//in order. After that, elements are removed until the element at the end of the
//vector is the most significant. Each of these operations is linear in 
//complexity, however they happen in sequence and thus their complexities are 
//additivie. Meaning the overall cost is still considered to be linear, O(n).
std::istream& operator>>(std::istream &in, Number& num)
{
  int temp;
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
//This operator contains a single loop that will execute once for each
//digit. It is apparrent that this is a linear time operation, O(n).
 std::ostream& operator<<(std::ostream &out, const Number& num)
{
  for(int i = num.mst_sig_dig(); i >= 0; --i)
  {
     out << num[i];
     out << " ";
  }
  out << "x";
  out << num.base;
  return out;
}
//This operator begins with comparisons of two expressions that can be evaluated
//in constant time. After those comparisons, the two numbers are compared
//lexicographically until a difference is found. In the worst case, every 
//element will be compared resulting in a linear function, O(n).
bool operator==( const Number& lhs, const Number& rhs)
{
  assert(lhs.base == rhs.base);
  if(lhs.digits.size() != rhs.digits.size())
  {
    return false;
  }
  for(int i = lhs.mst_sig_dig(); i >= 0; --i)
  {
    if(lhs[i] != rhs[i])
    {
       return false;
    }
  }
  return true;
}
//This operator is largely the same as the above, however it is does a few more
//comparisons in the begining and during the loop. All of the comparisons are 
//still on constant time expressions, so the overall analysis will still yield
//linear time, O(n).
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
    if(lhs[i] < rhs[i])
      return true;
    if(lhs[i] > rhs[i])
     return false;
  }
  return false;
}
//This operator is also similar except with the added cost of constructing a new
//number. However, this cost is additive and also linear, resulting in the 
//analysis remaining linear time, O(n).
bool operator==( const Number& lhs, const int rhs)
{
  Number temp(rhs, lhs.base);
  return lhs == temp;

}
//These operators are implemented in terms of the comparison operators above.
//They do not add any loops or functions, and thus have the same complexity,
//O(n).
bool operator!=( const Number& lhs, const Number& rhs)
{
  return !(lhs == rhs);
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
//These operations happen on single integers, and execute in constant time. 
//This is not to say they execute instantly, only that they do not vary cost
//based on the number of digits in the number.
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