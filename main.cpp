#include <iostream>
#include "test.h"

using namespace Lab2;
int main(){ 
    std::string a = "Strugov";
    Test test(a, 5, 1, 3);
    Test test2(a, 5, 4, 10);
    Test test3 = test + test2;
    Test test4 = test2 + test;
    std::cout<<std::endl;
    test.print(std::cout);
    std::cout<<std::endl;
    test2.print(std::cout);
    std::cout<<std::endl;
    test3.print(std::cout);
    std::cout<<std::endl;
    test4.print(std::cout);
    std::cout<<std::endl;
    std::cout<<(test3 <=> test4)<<" "<<(test4 <=> test3)<<std::endl;
    
    return 0;
}