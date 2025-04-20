#include "../include/logs.hpp"
#include <iostream>
#include <ctime>


std::string get_current_time(){
    time_t now;
    time(&now);
    std::string cur_time = ctime(&now);
    return cur_time.substr(11, 9); 
}


int print_to_log(std::string msg){
    
    
    std::cout << get_current_time() << msg << std::endl;
    return 0;
}

