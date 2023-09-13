#include "test.h"

namespace Lab2{
    Test::Test(std::string &surname): mark(0), first_num(1), last_num(1){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = move(surname);
    };  

    Test::Test(const std::string &surname, int mark, int first_num, int last_num){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = move(surname);
        (mark < 2 || mark > 5) ? throw std::invalid_argument("invalid mark") : this->mark = mark;
        if (first_num > last_num){
            throw std::invalid_argument("invalid nums");
        }
        (first_num < 0) ? throw std::invalid_argument("invalid first_num") : this->first_num = first_num;
        (last_num < 0) ? throw std::invalid_argument("invalid last_num") : this->last_num = last_num;
    };

    void Test::setSurname(std::string surname){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = surname;
    }

    void Test::setMark(int mark){
        (mark < 2 || mark > 5) ? throw std::invalid_argument("invalid mark") : this->mark = mark;
    }

    void Test::setFirst_num(int first_num){
        (first_num < 0) ? throw std::invalid_argument("invalid first_num") : this->first_num = first_num;
    }

    void Test::setLast_num(int last_num){
        (last_num < 0) ? throw std::invalid_argument("invalid last_num") : this->last_num = last_num;
    }
    const Test Test::operator+ (const Test &test) {
        if (surname != test.getSurname()) throw std::invalid_argument("different surname");
        if (first_num - 1 == test.getLast_num()){
            return Test(surname, mark, test.getFirst_num(), last_num);
        }
        if (last_num + 1 == test.getFirst_num()){
            return Test(surname, mark, first_num, test.getLast_num());
        }
        throw std::invalid_argument("Its imposible");
    }  
}