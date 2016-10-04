#include "arbitrary.hpp"
#include "arbitrary.cpp"
#include <iostream>

int main(int argc, char ** argv)
{
    Number test;
    test = 100;
    Number test2(test);
    std::cout << (test == test2);
    return 0;
}