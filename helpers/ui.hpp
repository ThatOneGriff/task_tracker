#pragma once
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <windows.h>
const std::string HELP_TEXT = " = List of commands =\n - add [name (1 word)] [desc]\n - delete (remove) [ID (can be 'all')]\n - list [status: 'todo', 'in-progress', 'done'; 'all' to list all tasks]\n - update [property: 'name', 'desc', 'status' ('todo', 'in-progress', 'done')] [ID] [new value]";

/// Here be:
void show_error(const std::string& error_text)
void show_warning(const std::string& warning_text);
std::string textcolor(const int color_code);


#endif