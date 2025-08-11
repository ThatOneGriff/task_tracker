#pragma once
#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <unordered_map>
#include <windows.h>

///// = Help = /////

const std::string HELP_TEXT =
     (std::string)" = List of commands = \n"
    + " [arg] - mandatory argument. \n"
    + "~[arg] - optional argument. \n"
    + '\n'
    + " - add [name] ~[desc] \n"
    + " - delete/remove [ID] \n"
    + " - list [status] \n"
    + " - update [property] [ID] [value] \n"
    + '\n'
    + "Inquire about usage of commands using help ~[command name]. \n"
    + "If an argument contains white-spaces, use quotation marks [\"arg arg\"].";

const std::unordered_map<std::string, std::string> DETAILED_HELP = {
    {
        "help", (std::string)"- No args: shows list of commands. \n"
                           + "- Arg 1: ~[command name] - details usage of a command. \n"
                           + "Example: 'help add'"
    },
    {
        "add", (std::string)"Adds a task of status 'todo' to the list. \n"
                          + '\n'
                          + "- Arg 1: [name] - task name; \n"
                          + "- Arg 2: ~[desc] - task description. \n"
                          + "Example: 'add \"Buy groceries\" \"Milk, sugar, oil\"'"
    },
    {
        "delete", (std::string)"Deletes a task from the list. \n"
                             + '\n'
                             + "- Arg 1: [ID] - ID of task to be removed | 'all' - clears task list (can't be undone). \n"
                             + "(Use 'list' to see a task's ID). \n"
                             + "Example: 'delete 1'"
    },
    {
        "remove", (std::string)"Deletes a task from the list. \n"
                             + '\n'
                             + "- Arg 1: [ID] - ID of task to be removed | 'all' - clears task list (can't be undone). \n"
                             + "(Use 'list' to see a task's ID). \n"
                             + "Example: 'remove 1'"
    },
    {
        "list", (std::string)"Lists tasks of a status. \n"
                           + '\n'
                           + "- Arg 1: [status] - 'todo'/'in-progress'/'done' | 'all' - lists all tasks. \n"
                           + "Example: 'list in-progress'"
    },
    {
        "update", (std::string)"Updates a property of a task. \n"
                             + '\n'
                             + "- Arg 1: [property] - 'name'/'desc'/'status'; \n"
                             + "- Arg 2: [ID] - ID of target task; \n"
                             + "- Arg 3: [value] - new value of target property. \n"
                             + "Example: 'update status 7 done'"
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