#pragma once
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <windows.h>
const std::string HELP_TEXT = " = List of commands =\n - add [name (1 word)] [desc]\n - delete (remove) [ID (can be 'all')]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";

/// Text-color codes
#define WHITE  textcolor(7)
#define GRAY   textcolor(8)
#define RED    textcolor(4)
#define GREEN  textcolor(2)
#define YELLOW textcolor(6)

/// Here be:
void show_info(const std::string& info_text);
void show_error(const std::string& error_text);
void show_warning(const std::string& warning_text);
std::string textcolor(const short int color_code);


/// Color: GREEN. Defaults to white.
void show_info(const std::string& info_text)
{
    std::cout << GREEN << info_text << WHITE;
}


/// Color: RED. Defaults to white.
void show_error(const std::string& error_text)
{
    std::cout << RED << error_text << WHITE;
}


/// Color: YELLOW. Defaults to white.
void show_warning(const std::string& warning_text)
{
    std::cout << YELLOW << warning_text << WHITE;
}


std::string textcolor(const short int color_code)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
    return std::string(); /// for insertion into 'cout'
}


#endif