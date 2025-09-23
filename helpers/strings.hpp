#pragma once
#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <string>

/// Input length limits for properties. NOTE: lifted to 999 to solely serve a stability purpose.
const int NAME_LIMIT   = 999, 
          DESC_LIMIT   = 999,
          STATUS_LIMIT = 11; /// Longest status ('in-progress') is 11 symbols long.

/// Here be:
bool is_num(const std::wstring& str);
void lower(std::wstring& str);


bool is_num(const std::wstring& str)
{
    for (const wchar_t& c: str)
    {
        if (c < L'0' || c > L'9')
            return false;
    }
    return true;
}


void lower(std::wstring& str)
{
    for (wchar_t& c: str)
        c = tolower(c);
}

#endif