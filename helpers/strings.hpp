#pragma once
#ifndef STRINGS_HPP
#define STRINGS_HPP

#include <codecvt> // codecvt_utf8
#include <locale>  // wstring_convert
#include <string>

/// Input length limits for properties. NOTE: lifted to 999 temporarily before a better system is put in place.
const int NAME_LIMIT   = 999, 
          DESC_LIMIT   = 999,
          STATUS_LIMIT = 11; /// Longest status ('in-progress') is 11 symbols long.

/// Here be:
bool is_num(const std::wstring& str);
void lower(std::wstring& str);
std::string to_utf8(const std::wstring& target);
std::wstring to_wstring(const std::string& target);


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


/// For JSON compatibility.
/// Copied from: https://json.nlohmann.me/home/faq/#wide-string-handling
std::string to_utf8(const std::wstring& target)
{
    static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    return utf8_conv.to_bytes(target);
}


/// Baffled how it isn't built-in.
std::wstring to_wstring(const std::string& target)
{
    return std::wstring(target.begin(), target.end());
}


#endif