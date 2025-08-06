#include <iostream>
#include <sstream>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"


/* TODO
- include scheme
- wstring
- dynamic character limiting
- find a way to implement regions into code

- more detailed help text, with mention of quote marks
- 'delete 1-5'
- load system that can handle invalid files
- list todo, in-progress
- invalid data handling
- dailies, due dates
- add build instructions to 'readme.md'
- make the project fine with moving into different folders
*/

/* IDEAS
- 'done' auto-deletion => settings
- activity overview
- settings
- storing saved data anywhere => handling absolute paths
*/


void clean_input();
void distribute_input();

std::string raw_input;

const int INPUT_VAR_AMOUNT = 4; /// 1 command, 3 args
std::string input[INPUT_VAR_AMOUNT];
#define command input[0]
#define arg1    input[1]
#define arg2    input[2]
#define arg3    input[3]


int main()
{
    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    std::vector<Task> tasks = load();
    
    /// NOTE: minimal ID of a task IN THE INTERFACE is 1,
    /// however, they're still stored in a vector,
    /// thus have a FACTUAL, IN-CODE minimal index of 0.
    while(true)
    {
        clean_input();
        std::cout << "\n > ";
        getline(std::cin, raw_input);
        lower(raw_input); /// input has no point in being case-sensitive
        distribute_input();
        std::cout << '\n';


        if (command == "add")
        {
            arg1 = arg1.substr(0, NAME_LIMIT);
            arg2 = arg2.substr(0, DESC_LIMIT);
            Task new_task(arg1, arg2);
            tasks.push_back(new_task);

            std::cout << textcolor(GREEN) << "Task created successfully [ID: " << tasks.size() << "]." << textcolor(WHITE);
        }


        else if (command == "delete" || command == "remove")
        {
            if (arg1 == "all")
            {
                tasks.clear();
                std::cout << textcolor(GREEN) << "All tasks cleared!\n\n" << textcolor(WHITE);
                continue;
            }
            if (! is_num(arg1) || stoi(arg1) < 1)
            {
                std::cout << textcolor(RED) << "Invalid ID!\n\n" << textcolor(WHITE);
                continue;
            }
            if (stoi(arg1) > tasks.size())
            {
                std::cout << textcolor(YELLOW) << "No tasks of ID " << arg1 << "!\n\n" << textcolor(WHITE);
                continue;
            }

            tasks.erase(tasks.begin() + stoi(arg1)-1);
            std::cout << textcolor(GREEN) << "Task deleted successfully!" << textcolor(WHITE);
        }


        else if (command == "help")
        {
            std::cout << '\n' << HELP_TEXT << "\n\n";
            continue;
        }
        

        else if (command == "list")
        {
            if (tasks.size() == 0)
            {
                std::cout << textcolor(YELLOW) << "Task list is empty!\n\n" << textcolor(WHITE);
                continue;
            }

            bool output_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if ((arg1 == "all") || (tasks[i].updatable_properties["status"] == arg1))
                {
                    output_happened = true;
                    tasks[i].output(i+1);
                    std::cout << "\n\n";
                }
            }

            if (! output_happened)
                std::cout << textcolor(YELLOW) << "No tasks with such status!\n\n" << textcolor(WHITE);
            continue;
        }


        else if (command == "update")
        {
            if (! is_num(arg2) || stoi(arg2) < 1)
            {
                std::cout << textcolor(RED) << "Invalid ID!\n\n" << textcolor(WHITE);
                continue;
            }
            if (stoi(arg2) > tasks.size())
            {
                std::cout << textcolor(YELLOW) << "No tasks of ID " << arg2 << "!\n\n" << textcolor(WHITE);
                continue;
            }
            
            /// if update didn't take place
            if (! tasks[stoi(arg2)-1].update(arg1, arg3)) /// 'update()' function returns whether anything has been updated
            {
                std::cout << "\n\n";
                continue; /// No warning message since it's all handled by the 'Task' class
            }
        }


        else
        {
            std::cout << textcolor(RED) << "Unknown command!\n\n" << textcolor(WHITE);
            continue;
        }


        std::cout << "\n\n";
        save(tasks); /// only reached when changes truly happened
    }

    return 0;
}



void clean_input()
{
    std::cin.clear();
    for (int i = 0; i < INPUT_VAR_AMOUNT; i++)
        input[i] = "";
}



void distribute_input()
{
    std::stringstream input_stream(raw_input);
    std::string word;
    bool quote_marks_open = false;
    int i = 0;

    while (input_stream >> word && i < 4)
    {
        if (word[0] == '"') /// start of a multi-word argument [MWA]
        {
            quote_marks_open = true;
            input[i] += word.substr(1, word.size() - 1);
            continue;
        }

        if (quote_marks_open)
            input[i] += ' ' + word;
        if (word[word.size() - 1] == '"') /// last word in an [MWA] cascades through the previous 'if' to here
        {
            quote_marks_open = false;
            input[i] = input[i].substr(0, input[i].size() - 1);
            ++i;
            continue;
        }
        
        if (! quote_marks_open)
            input[i++] += word;
    }
}