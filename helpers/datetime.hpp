#pragma once
#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <iomanip>
#include <time.h>
#include <windows.h>


std::wstring get_cur_date_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::wostringstream woss;
    woss << std::put_time(&tm, L"%d.%m.%Y at %H:%M");
    return woss.str();
}


#endif