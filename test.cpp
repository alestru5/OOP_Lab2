#include "test.h"

namespace Lab2 {
    Test::Test(std::string &surname): mark(0), first_num(1), last_num(1){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = move(surname);
    }

    Test::Test(const std::string &surname, int mark, int first_num, int last_num){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = move(surname);
        (mark != 0 && (mark < 2 || mark > 5)) ? throw std::invalid_argument("invalid mark") : this->mark = mark;
        if (first_num != 1){
            this->mark = 0;
        }
        if (first_num > last_num){
            throw std::invalid_argument("invalid nums");
        }
        (first_num < 0) ? throw std::invalid_argument("invalid first_num") : this->first_num = first_num;
        (last_num < 0) ? throw std::invalid_argument("invalid last_num") : this->last_num = last_num;
    }

    Test &Test::setSurname(std::string surname){
        (surname.size() == 0) ? throw std::invalid_argument("invalid surname") : this->surname = surname;
        return *this;
    }

    Test &Test::setMark(int mark){
        ((mark != 0 && (mark < 2 || mark > 5)) || first_num != 1) ? throw std::invalid_argument("invalid mark") : this->mark = mark;
        return *this;
    }

    Test &Test::setFirst_num(int first_num){
        (first_num < 0) ? throw std::invalid_argument("invalid first_num") : this->first_num = first_num;
        return *this;
    }

    Test &Test::setLast_num(int last_num){
        (last_num < 0) ? throw std::invalid_argument("invalid last_num") : this->last_num = last_num;
        return *this;
    }

    std::vector<Test> Test::split_test() const {
        std::vector <Test> split_test;
        for (int i = 0; i < last_num - first_num + 1; i++){
            if (i == 0){
                split_test.push_back(Test(surname, mark, first_num + i, first_num + i));
            } else {
                split_test.push_back(Test(surname, 0, first_num + i, first_num + i));
            }
            
        }
        return split_test;
    }
    

    Test Test::operator+ (const Test &test) const {
        if (surname != test.getSurname()){
            throw std::invalid_argument("different surname");
        }
        if (first_num - 1 == test.getLast_num()){
            return Test(surname, std::max(mark, test.getMark()), test.getFirst_num(), last_num);
        }
        if (last_num + 1 == test.getFirst_num()){
            return Test(surname, std::max(mark, test.getMark()), first_num, test.getLast_num());
        }
        throw std::invalid_argument("Its imposible");
    }

    

    int Test::operator<=>(const Test &test) const {
        for (size_t i = 0; i < std::min(surname.size(), test.getSurname().size()); i++){
            if (surname[i] < test.getSurname()[i]){
                return -1;
            } else if (surname[i] > test.getSurname()[i]){
                return 1;
            }
        }
        if (first_num < test.getFirst_num()){
            return -1;
        } else if (first_num == test.getFirst_num()){
            return 0;
        } else{
            return 1;
        }
    }

    std::ostream &operator<<(std::ostream &c, const Test &test){
        c<<"Surname: "<<test.surname<<std::endl;
        c<<"Mark: "<<test.mark<<std::endl;
        c<<"First page: "<<test.first_num<<std::endl;
        c<<"Last page: "<<test.last_num<<std::endl;
        c<<std::endl;
        return c;
    }

    std::istream &operator>>(std::istream &c, Test &test){
        std::string sn;
        int m, f_n, l_n;
        c>>sn;
        c>>m;
        c>>f_n;
        c>>l_n;
        if (c){
            test.surname = sn;
            test.mark = m;
            test.first_num = f_n;
            test.last_num = l_n;
        } else{
            throw std::invalid_argument("invalid argument");
        }
        return c;
    }
}