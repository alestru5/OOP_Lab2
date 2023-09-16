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
            
            

            std::ostream & print(std::ostream &c) const {
                c<<"Surname: "<<surname<<std::endl;
                c<<"Mark: "<<mark<<std::endl;
                c<<"First page: "<<first_num<<std::endl;
                c<<"Last page: "<<last_num<<std::endl;
                return c;
            };

            Test operator+(const Test &test) const;
            std::vector<Test> split_test() const;
            int operator<=>(const Test &test) const;
    };
    
}

#endif