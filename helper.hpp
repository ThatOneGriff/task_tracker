#ifndef HELPER_HPP
#define HELPER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <time.h>


const std::string HELP_TEXT = "List of commands:\n - add [name] [desc]\n - delete [ID]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";


std::string get_cur_date_time()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
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


#endif