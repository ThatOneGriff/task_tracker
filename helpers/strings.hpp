#pragma once
#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>
#include <windows.h>
const std::string HELP_TEXT = " = List of commands =\n - add [name (1 word)] [desc]\n - delete (remove) [ID (can be 'all')]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";

/// Here be:
bool is_num(const std::string& str);
void lower(std::string& str);
std::string textcolor(const int color_code);


/// input length limits for properties
const int NAME_LIMIT   = 25, 
          DESC_LIMIT   = 70,
          STATUS_LIMIT = 11;


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

/// text color codes
const int WHITE  = 7,
          GRAY   = 8,
          RED    = 4,
          GREEN  = 2,
          YELLOW = 6;


std::string textcolor(const int color_code)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
    return std::string(); /// for insertion into 'cout'
}

#endif