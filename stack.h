#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "test.h"

namespace Lab2{
    class Stack{
        private:
            int m_size;
            int c_size;
            Test *arr;
        public:
            Stack(): m_size(10), c_size(0), arr(nullptr){};
            Stack(const Stack& other);
            Stack(int count, std::vector<Test> tmp, int m_size);
            Stack(const Stack&& other);
            ~Stack() {m_size = 0, c_size = 0, delete [] arr; };

            int getM_size() const { return m_size; };
            int getC_size() const { return c_size; };
            Test *getArr() const { return arr; };

            std::pair <int, int> check() const { return std::make_pair(c_size, m_size); };

            void split_stack();
            Test pop();
            Test zero_mark();
            void delete_test(const Test &test);
            void union_stack();


            void operator+=(const Test &test);
            
        


    };
}


#endif