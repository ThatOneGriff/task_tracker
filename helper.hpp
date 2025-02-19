#ifndef HELPER_HPP
#define HELPER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>


const std::string HELP_TEXT = " = List of commands =\n - add [name (1 word)] [desc]\n - delete (remove) [ID (can be 'all')]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";
// character limits for properties
const int NAME_LIMIT   = 25, 
          DESC_LIMIT   = 70,
          STATUS_LIMIT = 11;
// text color codes
const int WHITE  = 7,
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


void lower(std::string& str)
{
    for (char& c: str)
        c = tolower(c);
}


std::string textcolor(const int color_code)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
    return ""; // for insertion into 'cout'
}


#endif