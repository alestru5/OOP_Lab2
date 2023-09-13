#include <iostream>
#include "test.h"

using namespace Lab2;
int main(){ 
    std::string a = "Strugov";
    Test test(a, 5, 1, 3);
    Test test2(a, 5, 4, 10);
    Test test3 = test + test2;
    test3.print(std::cout);
    return 0;
}