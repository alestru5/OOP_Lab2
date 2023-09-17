
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
        this->m_size = std::max(m_size, count);
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
        if (f == c){
            throw std::invalid_argument("Stack hasn't zero test");
        }
        return tmp[f]; 
    }

    void Stack::delete_test(const Test &test){
        std::vector<Test> tmp;
        int c = c_size;
        int f = c_size;
        for (int i = 0; i < c; i++){
            Test t = (*this).pop();
            tmp.push_back(t);
            if (t <=> test == 0){
                f = i;
                break;
            }
        }
        for (int i = 0; i < f; i++){
            (*this) += tmp[i];
        }
        if (f == c){
            throw std::invalid_argument("Stack hasn't this test");
        }
    }

    void Stack::union_stack(){
        std::unordered_map <std::string, std::vector<int>> mp;
        for (int i = 0; i < c_size; i++){
            Test test = arr[i];
            if (test.getLast_num() > (int) mp[test.getSurname()].size()){
                mp[test.getSurname()].resize(test.getLast_num(), -1);
            }    
            for (int j = test.getFirst_num() - 1; j < test.getLast_num(); j++){
                mp[test.getSurname()][j] = test.getMark();
            }
        }
        c_size = 0;
        delete [] arr;
        std::vector<Test> t;
        for (auto &i: mp){
            int l = -1, r = -1;
            for (size_t j = 0; j < i.second.size(); j++){
                if (i.second[j] != -1){
                    if (l == -1){
                        l = j;
                    }
                    r = j;
                } else if (l != -1){
                    Test tmp(i.first, i.second[l], l + 1, r + 1);
                    t.push_back(tmp);
                    l = -1;
                    r = -1;
                } 
            }
            if (l != -1 && r != -1){
                Test tmp(i.first, i.second[l], l + 1, r + 1);
                t.push_back(tmp);
            }
        }
        arr = new Test[(int) t.size()];
        c_size = (int) t.size();
        for (size_t j = 0; j < t.size(); j++){
            arr[j] = t[j];
        }
    }

    void Stack::operator+=(const Test &test){
        if (c_size == m_size){
            m_size += 1;
        }
        Test *tmp = new Test[c_size + 1];
        std::copy(arr, arr + c_size, tmp);
        delete [] arr;
        arr = tmp;
        arr[c_size] = test;
        c_size += 1;
    }

    Stack &Stack::operator=(const Stack &stack){
        m_size = stack.getM_size();
        c_size = stack.getC_size();
        delete [] arr;
        arr = new Test[c_size];
        for (int i = 0; i < c_size; i++){
            arr[i] = stack.getArr()[i];
        }
        return *this;
    }

    Stack &Stack::operator=(Stack &&stack){
        if (this != &stack){
            m_size = stack.getM_size();
            c_size = stack.getC_size();
            delete [] arr;
            arr = stack.getArr();
            stack.arr = nullptr;
            stack.c_size = 0;
            stack.m_size = 0;
        }  
        return *this;
    }

    std::ostream &operator<<(std::ostream &c, const Stack &stack){
        if(stack.c_size == 0){
            c << "Stack is empty";
        }else{
            c << "Your stack: "<<std::endl;
            for(int i = stack.c_size - 1; i >= 0; --i){
                c<<"----------"<<i+1<<"----------"<<std::endl;
                c<<stack.arr[i];
            }
        }    
        c << std::endl;
        return c;
    }

    std::istream &operator>>(std::istream &c, Stack &stack){
        if (stack.c_size != 0){
            throw std::invalid_argument("stack isn't empty");
        }
        try{
            int t;
            c>>t;
            for (int i = 0; i < t; i++){
                Test test;
                c>>test;
                stack += test;
            }
        } catch(...){
            throw;
        }    
        return c;
    }

}