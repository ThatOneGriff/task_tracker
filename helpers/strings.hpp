#pragma once
#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>

/// Input length limits for properties
const int NAME_LIMIT   = 25, 
          DESC_LIMIT   = 70,
          STATUS_LIMIT = 11;

/// Here be:
bool is_num(const std::string& str);
void lower(std::string& str);


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

#endif