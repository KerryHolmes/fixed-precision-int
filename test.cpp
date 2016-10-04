#include "arbitrary.hpp"
#include <iostream>

int main(argc, argv[])
{
    Number test();
    test = 100;
    Number test2(test);
    std::cout << test == test2;
    return 0;
}