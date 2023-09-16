#include "menu.h"


int (*menu())(Stack &stack){
    try{
        int (*foo[])(Stack &stack) = {enter_stack, show_stack, show_info, add_test, link_tests, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
        std::cout<<"Menu:"<<std::endl;
        std::string msg[]{"Enter stack.", "Show stack", "Show info", "Add test", "Link tests", "Split test", "Split stack", "Stack's pop", "Union tests", "Zero pop", "Quit"};
        for (size_t i = 0; i < sizeof(msg) / sizeof(msg[0]); i++){
            std::cout<<i + 1<<". "<<msg[i]<<std::endl;
        }
        int a = getNum<int>(1, 11);
        return foo[a - 1];
    } catch(...){
        throw;
    }    
}

int enter_stack(Stack &stack){
    try{
        if (stack.getC_size() != 0){
            throw std::invalid_argument("stack isn't empty");
        }
        int c_size;
        std::cout<<"Enter size stack: ";
        c_size = getNum<int>(0, 10);
        for (int i = 0; i < c_size; i++){
            stack += inputTest();
            std::cout<<std::endl;
        }
    } catch(...){
        throw;
    }
    return 0;    
}

int show_stack(Stack &stack){
    std::cout<<std::endl;
    std::cout<<"Your stack:"<<std::endl;
    for (int i = 0; i < stack.getC_size(); i++){
        stack.getArr()[i].print(std::cout);
        std::cout<<std::endl;
    }
    return 0;  
}

int show_info(Stack &stack){
    std::unordered_map <std::string, int> mp;
    std::cout<<std::endl;
    std::cout<<"C_size: "<<stack.getC_size()<<std::endl;
    std::cout<<"M_size: "<<stack.getM_size()<<std::endl;
    for (int i = 0; i < stack.getC_size(); i++){
        if (mp.count(stack.getArr()[i].getSurname()) == 0){
            mp[stack.getArr()[i].getSurname()] = 1;
        } else{
            mp[stack.getArr()[i].getSurname()] += 1;
        }
    }
    std::cout<<"Autors and counts: "<<std::endl;
    for (auto &i: mp){
        std::cout<<i.first<<": "<<i.second<<std::endl;
    }
    std::cout<<std::endl;
    return 0;  
}

int add_test(Stack &stack){
    std::cout<<std::endl;
    Test push = inputTest();
    stack += push;
    return 0;  
}

int link_tests(Stack &stack){
    try{
        int f, s;
        show_stack(stack);
        std::cout<<"Choice tests: ";
        f = getNum<int>(1, stack.getC_size());
        s = getNum<int>(1, stack.getC_size());
        Test first = stack.getArr()[s-1];
        Test second = stack.getArr()[f-1];
        (first + second).print(std::cout);
        stack.delete_test(first);
        stack.delete_test(second);
        stack += (first + second);
    } catch (...){
        throw;
    }
    return 0;
}
