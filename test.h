#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <vector>


namespace Lab2{
    class Test{
        private:
            std::string surname;
            int mark;
            int first_num; 
            int last_num;
        public:
            explicit Test(): surname(""), mark(0), first_num(1), last_num(1){};
            explicit Test(std::string &surname);
            explicit Test(const std::string &surname, int mark, int first_num, int last_num);

            const std::string &getSurname() const {return surname; }
            int getMark() const {return mark; }
            int getFirst_num() const {return first_num; }
            int getLast_num() const {return last_num; };

            Test &setSurname(std::string surname);
            Test &setMark(int mark);
            Test &setFirst_num(int first_num);
            Test &setLast_num(int last_num);

            Test operator+(const Test &test) const;
            std::vector<Test> split_test() const;
            int operator<=>(const Test &test) const;
            Test operator!() const;
            friend std::ostream &operator<<(std::ostream &c, const Test &test);
            friend std::istream &operator>>(std::istream &c, Test &test);
    };
    
}

#endif