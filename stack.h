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
            Stack(Stack&& other);
            ~Stack() {m_size = 0, c_size = 0, delete [] arr; };

            int getM_size() const { return m_size; };
            int getC_size() const { return c_size; };
            Test *getArr() const { return arr; };

            /*Stack &setM_size(int m_size){ this->m_size = m_size; return *this;};
            Stack &setC_size(int c_size) { this->c_size = c_size; return *this; };
            Stack &setArr(Test *arr) { this->arr= arr; return *this; };*/

            std::pair <int, int> check() const { return std::make_pair(c_size, m_size); };

            void split_stack();
            Test pop();
            Test zero_mark();
            void delete_test(const Test &test);
            void union_stack();


            void operator+=(const Test &test);
            Stack &operator=(const Stack &stack);
            Stack &operator=(Stack &&stack);
            Stack &operator++();
            Test &operator[](int i);
            friend std::ostream &operator<<(std::ostream &c, const Stack &stack);
            friend std::istream &operator>>(std::istream &c, Stack &stack);
        


    };
}


#endif