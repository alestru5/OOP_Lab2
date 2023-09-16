
#include "stack.h"
    
namespace Lab2{
    Stack::Stack(const Stack& other){
        m_size = other.getM_size();
        c_size = other.getC_size();
        arr = new Test[c_size];
        for (int i = 0; i < c_size; i++){
            arr[i] = other.getArr()[i];
        }
    }

    Stack::Stack(int count, std::vector<Test> tmp, int m_size){
        if (count > m_size){
            throw std::invalid_argument("stack overflow");
        }
        arr = new Test[count];
        this->c_size = count;
        this->m_size = m_size;
        for (int i = 0; i < count; i++){
            arr[i] = tmp[i];
        }
    }

    Stack::Stack(const Stack&& other){
        m_size = other.m_size;
        c_size = other.c_size;
        arr= other.arr;
    }

    void Stack::split_stack(){
        int n = 0;
        for (int i = c_size - 1; i >= 0; i--){
            n += arr[i].getLast_num() - arr[i].getFirst_num() + 1; 
        }
        Test *tmp = new Test[n];
        int k = 0;
        int c = c_size;
        for (int i = 0; i < c; i++){
            std::vector<Test> t = (*this).pop().split_test();
            for (size_t j = 0; j < t.size(); j++){
                tmp[k] = t[j];
                k += 1;
            }
        }
        delete [] arr;
        arr = tmp;
        c_size = k;
        m_size = std::max(m_size, k);
    }

    Test Stack::pop(){
        if (c_size == 0){
            throw std::invalid_argument("stack is empty");
        }
        Test ans = arr[c_size - 1];
        Test *tmp = new Test[c_size - 1];
        std::copy(arr, arr + c_size - 1, tmp);
        delete [] arr;
        arr = tmp;
        c_size -= 1;
        return ans;
    }

    Test Stack::zero_mark(){
        std::vector<Test> tmp;
        int c = c_size;
        int f = c_size;
        for (int i = 0; i < c; i++){
            Test t = (*this).pop();
            tmp.push_back(t);
            if (t.getMark() == 0){
                f = i;
                break;
            }
        }
        for (int i = 0; i < f; i++){
            (*this) += tmp[i];
        }
        if (f == c_size){
            Test empty;
            return empty;
        }
        return tmp[f];
        
    }

    void Stack::union_stack(){
        
    }

    void Stack::operator+=(const Test &test){
        if (c_size == m_size){
            throw std::invalid_argument("stack overflow");
        }
        Test *tmp = new Test[c_size + 1];
        std::copy(arr, arr + c_size, tmp);
        delete [] arr;
        arr = tmp;
        arr[c_size] = test;
        c_size += 1;
    }
}