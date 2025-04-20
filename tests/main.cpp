#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char** argv){

    time_t now;
    time(&now);
    std::string cur_time = ctime(&now);

    std::cout << cur_time.substr(11, 8) << std::endl;
    return 0;
}