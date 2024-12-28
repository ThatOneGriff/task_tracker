#ifndef HELPER_HPP
#define HELPER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>


std::string get_cur_date_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}


#endif