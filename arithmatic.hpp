//This file intentionally mispelled
#ifndef ARITHMATIC_HPP
#define ARITHMATIC_HPP

//This function is used to add two digits in binary
//The result is stored in the first digit, which is passed by reference
//The carry is the return value of the function
//If the numbers add to be 2, the result is the first variable will be set to 0
//And the return value will be 1
int add_binary( int& lhs, const int& rhs)
{
  if( 2 > (lhs + rhs)  )
  {
    lhs += rhs;
    return 0;
  }
  else
  {
    lhs += rhs;
    lhs -= 2;
    return 1;
  }
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

#endif
