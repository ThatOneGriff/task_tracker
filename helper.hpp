#ifndef HELPER_HPP
#define HELPER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>


const std::string HELP_TEXT = " = List of commands =\n - add [name (1 word)] [desc]\n - delete [ID]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";
const int NAME_LIMIT   = 25, /* character limits for properties*/
          DESC_LIMIT   = 70,
          STATUS_LIMIT = 11;
const int WHITE  = 7, /* color codes */
          GRAY   = 8,
          RED    = 4,
          GREEN  = 2,
          YELLOW = 6;


std::string get_cur_date_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y at %H:%M");
    return oss.str();
}


bool is_num(const std::string& str)
{
    for (const char& c: str)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}


void textcolor(const int color_code)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
}


#endif