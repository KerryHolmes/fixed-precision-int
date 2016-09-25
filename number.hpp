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

#ifndef NUMBER_HPP
#define NUMBER_HPP

struct number{

  private:
  
  std::vector<int> digits;
  
  public:
  number()
  :digits(2048,0)
  {}

};

#endif
