
#include "stack.h"
    
namespace Lab2{
    Stack::Stack(const Stack& other){
        //! Копирование всех полей
        m_size = other.getM_size();
        c_size = other.getC_size();
        arr = new Test[c_size];
        for (int i = 0; i < c_size; i++){
            arr[i] = other.getArr()[i];
        }
    }

    Stack::Stack(int count, std::vector<Test> tmp, int m_size){
        //! Копирование всех аргументов
        this->m_size = std::max(m_size, count);
        arr = new Test[count];
        this->c_size = count;
        this->m_size = m_size;
        for (int i = 0; i < count; i++){
            arr[i] = tmp[i];
        }
    }

    Stack::Stack(Stack&& other){
        //! Перемещение всех аргументов
        m_size = other.m_size;
        c_size = other.c_size;
        arr= other.arr;
        other.arr = nullptr;
        other.m_size = 0;
        other.c_size = 0;
    }

    void Stack::split_stack(){
        int n = 0;
        //! Подсчет размера итогового стэка
        for (int i = c_size - 1; i >= 0; i--){
            n += arr[i].getLast_num() - arr[i].getFirst_num() + 1; 
        }
        Test *tmp = new Test[n];
        int k = 0;
        int c = c_size;
        //! Получение и сохранение работ из стэка методом pop, параллельно деля каждую работу на отдельные работы
        for (int i = 0; i < c; i++){
            std::vector<Test> t = (*this).pop().split_test();
            for (size_t j = 0; j < t.size(); j++){
                tmp[k] = t[j];
                k += 1;
            }
        }
        delete [] arr;
        //! Задание новых значений полям
        arr = tmp;
        c_size = k;
        m_size = std::max(m_size, k);
    }

    Test Stack::pop(){
        //! Невозможность достать работу из пустой стопки
        if (c_size == 0){
            throw std::invalid_argument("stack is empty");
        }
        //! Удаление последний работы и изменение состояния
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
        //! Цикл доставания последней работы и сохранения ее в другой стэк, для дальнейшего возврата
        for (int i = 0; i < c; i++){
            Test t = (*this).pop();
            tmp.push_back(t);
            if (t.getMark() == 0){
                f = i;
                break;
            }
        }
        //! Возврат неподходящих работ
        for (int i = 0; i < f; i++){
            (*this) += tmp[i];
        }
        //! Проверка на нахождение работы
        if (f == c){
            throw std::invalid_argument("Stack hasn't zero test");
        }
        //! Возврат работы
        return tmp[f]; 
    }

    void Stack::delete_test(const Test &test){
        std::vector<Test> tmp;
        int c = c_size;
        int f = c_size;
        //! Достаем работы, пока не встретим нужную
        for (int i = 0; i < c; i++){
            Test t = (*this).pop();
            tmp.push_back(t);
            if (t <=> test == 0){
                f = i;
                break;
            }
        }
        //! Возврат, доставаемых работ
        for (int i = 0; i < f; i++){
            (*this) += tmp[i];
        }
        //! Проверка на нахождение работы
        if (f == c){
            throw std::invalid_argument("Stack hasn't this test");
        }
    }

    void Stack::union_stack(){
        std::unordered_map <std::string, std::vector<int>> mp;
        //! Копирование верхних работ, сортирую по фамилиям
        int c = c_size;
        for (int i = 0; i < c; i++){
            Test test = (*this).pop();
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
        //! Прохождение по всем работам, объединяя их
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
        //! Возврат всех объединенных работ
        arr = new Test[(int) t.size()];
        c_size = (int) t.size();
        for (size_t j = 0; j < t.size(); j++){
            arr[j] = t[j];
        }
    }

    Stack &Stack::operator+=(const Test &test){
        //! Проверка на необходимость увелечения размера стека
        if (c_size == m_size){
            m_size += step;
        }
        //! Работу из аргумента помещаем на верх стека
        Test *tmp = new Test[c_size + 1];
        std::copy(arr, arr + c_size, tmp);
        delete [] arr;
        arr = tmp;
        arr[c_size] = test;
        c_size += 1;
        return (*this);
    }

    Stack &Stack::operator=(const Stack &stack){
        //! Копирование всех полей
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
        //! Проверка на перемещение себя же
        if (this != &stack){
            //! Перемещение всех полей
            m_size = stack.m_size;
            c_size = stack.c_size;
            delete [] arr;
            arr = stack.getArr();
            stack.arr = nullptr;
            stack.c_size = 0;
            stack.m_size = 0;
        }  
        return *this;
    }

    Stack &Stack::operator++(){
        //! Если стек пуст, нельзя получить верхнюю работу
        if (c_size == 0){
            throw std::invalid_argument("stack is empty");
        }
        //! Дублирование последней работы
        Test tmp = arr[c_size - 1];
        *this += tmp;
        return *this;
    }

    Stack Stack::operator++(int){
        //! Если стек пуст, нельзя получить верхнюю работу
        if (c_size == 0){
            throw std::invalid_argument("stack is empty");
        }
        //! Дублирование последней работы
        Test tmp = arr[c_size - 1];
        Stack ans(*this);
        *this += tmp;
        return ans;
    }

    Test &Stack::operator[](int i) const{
        //! Проверка на корректность индекса
        if (i >= c_size || i < 0){
            throw std::invalid_argument("index out of range");
        }
        return arr[i];
    }

    std::ostream &operator<<(std::ostream &c, const Stack &stack){
        //! Провекра на пустоту стека
        if(stack.c_size == 0){
            c << "Stack is empty";
        }else{
            //! Вывод стека

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
        //! Проверка на пустоту стека
        if (stack.c_size != 0){
            throw std::invalid_argument("stack isn't empty");
        }
        try{
            int t;
            c>>t;
            if (c.good()){
                for (int i = 0; i < t; i++){
                    Test test;
                    c>>test;
                    stack += test;
                }
            } else{
                throw std::invalid_argument("invalid argument");
            }    
        } catch(...){
            throw;
        }    
        return c;
    }

}