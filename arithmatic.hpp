//This file intentionally mispelled
#ifndef ARITHMATIC_HPP
#define ARITHMATIC_HPP

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

int sub_binary( int& lhs, const int& rhs)
{
  if( 0 > (lhs - rhs)  )
  {
    lhs = 2 -rhs;
    return 1;
  }
  else
  {
    lhs -= rhs;
    return 0;
  }
}

#endif
