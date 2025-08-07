#include <iostream>
#include <sstream>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"


/* TODO
- standardize newlines after text
- delete by full & partial name
- wstring
- dynamic character limiting

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
    std::cout << " === Task Tracker (type 'help' to list all commands) === \n\n";
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

            show_info("Task created successfully [ID: " + to_string(tasks.size()) + "]. \n\n");
        }


        else if (command == "delete" || command == "remove")
        {
            if (arg1 == "all")
            {
                tasks.clear();
                show_info("All tasks cleared! \n\n");
                continue;
            }
            else if (! is_num(arg1) || stoi(arg1) < 1)
            {
                show_error("Invalid ID! \n\n");
                continue;
            }
            else if (stoi(arg1) > tasks.size())
            {
                show_warning("No tasks of ID " + to_string(arg1) + "! \n\n");
                continue;
            }

            tasks.erase(tasks.begin() + stoi(arg1)-1);
            show_info("Task deleted successfully! \n\n");
        }

        // TODO: check '\n's
        else if (command == "help")
        {
            std::cout << '\n' << HELP_TEXT << "\n\n";
            continue;
        }
        

        else if (command == "list")
        {
            if (tasks.size() == 0)
            {
                show_warning("Task list is empty! \n\n");
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
                show_warning("No tasks with such status! \n\n");
            continue;
        }


        else if (command == "update")
        {
            if (! is_num(arg2) || stoi(arg2) < 1)
            {
                show_error("Invalid ID! \n\n");
                continue;
            }
            else if (stoi(arg2) > tasks.size())
            {
                show_warning("No tasks of ID " + to_string(arg2) + "! \n\n");
                continue;
            }
            
            /// Update didn't take place
            if (! tasks[stoi(arg2)-1].update(arg1, arg3)) /// 'update()' function returns whether anything has been updated
            {
                std::cout << "\n\n"; // TODO: '\n
                continue; /// No warning message since it's all handled by the 'Task' class
            }
        }


        else
        {
            show_error("Unknown command! \n\n");
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