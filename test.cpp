#include "arbitrary.hpp"
#include <iostream>

int main(int argc, char ** argv)
{
    Number test;
    test = 100;
    Number test2(50,2);
    std::cout.setf(std::ios::boolalpha);
    std::cout<< test.convert_decimal()<<std::endl;
    std::cout<< test2.convert_decimal()<<std::endl;
    std::cout << static_cast<bool>(test == test)<<std::endl;
    std::cout << static_cast<bool>(test == 100)<<std::endl;
    std::cout << static_cast<bool>(test == test2)<<std::endl;
    std::cout << static_cast<bool>(test > test2)<<std::endl;
    std::cout << static_cast<bool>(test < test2)<<std::endl;
    std::cout<<test.convert_decimal()<<std::endl;
    test *= test2;
    std::cout<< test.convert_decimal()<<std::endl;
    test /= test2;
    std::cout<< test.convert_decimal()<<std::endl;
    test += test2;
    std::cout<< test.convert_decimal()<<std::endl;
    test -= test2;
    std::cout<< test.convert_decimal()<<std::endl;

    return 0;
}