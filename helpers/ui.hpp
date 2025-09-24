#pragma once
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <unordered_map>
#include <windows.h>

///// = Help = /////

const std::wstring HELP_TEXT =
     (std::wstring)L" = List of commands = \n"
    + L" [arg] - mandatory argument. \n"
    + L"~[arg] - optional argument. \n"
    + L'\n'
    + L" - add [name] ~[desc] \n"
    + L" - delete/remove [ID] \n"
    + L" - list/show [status] \n"
    + L" - update [property] [ID] [value] \n"
    + L'\n'
    + L"Inquire about usage of commands using help ~[command name]. \n"
    + L"If an argument contains white-spaces, use quotation marks [\"arg arg\"].";

const std::unordered_map<std::wstring, std::wstring> DETAILED_HELP = {
    {
        L"help", (std::wstring)L"- No args: shows list of commands. \n"
                           + L"- Arg 1: ~[command name] - details usage of a command. \n"
                           + L"Example: 'help add'"
    },
    {
        L"add", (std::wstring)L"Adds a task of status 'todo' to the list. \n"
                          + L'\n'
                          + L"- Arg 1: [name] - task name; \n"
                          + L"- Arg 2: ~[desc] - task description. \n"
                          + L"Example: 'add \"Buy groceries\" \"Milk, sugar, oil\"'"
    },
    {
        L"delete", (std::wstring)L"Deletes a task from the list. \n"
                             + L'\n'
                             + L"- Arg 1: [ID] - ID of task to be removed | 'all' - clears task list (can't be undone). \n"
                             + L"(Use 'list' to see a task's ID). \n"
                             + L"Example: 'delete 1'"
    },
    {
        L"remove", (std::wstring)L"Deletes a task from the list. \n"
                             + L'\n'
                             + L"- Arg 1: [ID] - ID of task to be removed | 'all' - clears task list (can't be undone). \n"
                             + L"(Use 'list' to see a task's ID). \n"
                             + L"Example: 'remove 1'"
    },
    {
        L"list", (std::wstring)L"Lists tasks of a status. \n"
                           + L'\n'
                           + L"- Arg 1: [status] - 'todo'/'in-progress'/'done' | 'all' - lists all tasks. \n"
                           + L"Example: 'list in-progress'"
    },
    {
        L"show", (std::wstring)L"Lists tasks of a status. \n"
                           + L'\n'
                           + L"- Arg 1: [status] - 'todo'/'in-progress'/'done' | 'all' - lists all tasks. \n"
                           + L"Example: 'show in-progress'"
    },
    {
        L"update", (std::wstring)L"Updates a property of a task. \n"
                             + L'\n'
                             + L"- Arg 1: [property] - 'name'/'desc'/'status'; \n"
                             + L"- Arg 2: [ID] - ID of target task; \n"
                             + L"- Arg 3: [value] - new value of target property. \n"
                             + L"Example: 'update status 7 done'"
    }
};


///// = Text coloring = /////

/// Color codes
#define WHITE  textcolor(7)
#define GRAY   textcolor(8)
#define RED    textcolor(4)
#define GREEN  textcolor(2)
#define YELLOW textcolor(6)

/// Here be:
void show_info(const std::wstring& info_text);
void show_error(const std::wstring& error_text);
void show_warning(const std::wstring& warning_text);
std::wstring textcolor(const short int color_code);


/// Color: GREEN. Defaults to white.
void show_info(const std::wstring& info_text)
{
    std::wcout << GREEN << info_text << WHITE;
}


/// Color: RED. Defaults to white.
void show_error(const std::wstring& error_text)
{
    std::wcout << RED << error_text << WHITE;
}


/// Color: YELLOW. Defaults to white.
void show_warning(const std::wstring& warning_text)
{
    std::wcout << YELLOW << warning_text << WHITE;
}


std::wstring textcolor(const short int color_code)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_code);
    return std::wstring(); /// for insertion into 'wcout'
}


#endif