#pragma once
#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <iomanip>
#include <time.h>
#include <windows.h>


std::string get_cur_date_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y at %H:%M");
    return oss.str();
}


#endif