#include "menu.h"


int (*menu())(Stack &stack){
    try{
        int (*foo[])(Stack &stack) = {enter_stack, show_stack, show_info, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
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
        int m_size, c_size;
        std::cout<<"Enter max size: ";
        m_size = getNum<int>(0);
        std::cout<<"Enter size stack: ";
        c_size = getNum<int>(0, m_size);
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
            mp[stack.getArr()[i].getSurname()] = 0;
        } else{
            mp[stack.getArr()[i].getSurname()] += 1;
        }
    }
    std::cout<<"Autors and counts: "<<std::endl;
    for (auto &i: mp){
        std::cout<<i.first<<": "<<i.second<<std::endl;
    }
    return 0;  
}