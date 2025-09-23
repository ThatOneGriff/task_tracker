#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"


/* TODO
- delete by full & partial name
- wwstring
- dynamic character limiting

- 'delete 1-5'
- loading system that can handle invalid files
- invalid input handling
- dailies, due dates
- 'list todo, in-progress'
- add build instructions to 'readme.md'
*/

/* IDEA-S
- settings
-'done' auto-delete on closure
 => settings
 => close detection
- storing saved data anywhere => handling absolute paths => make the project fine with moving into different folders
*/


void clean_input();
void distribute_input();

std::wstring raw_input;

const unsigned int INPUT_VAR_AMOUNT = 4; /// 1 command, 3 args
std::wstring input[INPUT_VAR_AMOUNT];
#define command input[0]
#define arg1    input[1]
#define arg2    input[2]
#define arg3    input[3]


int main()
{
    std::wcout << L" === Task Tracker (type 'help' to list all commands) === \n\n";
    std::vector<Task> tasks = load();
    
    /// NOTE: minimal ID of a task IN THE INTERFACE is 1,
    /// however, they're still stored in a vector,
    /// thus have a FACTUAL, IN-CODE minimal index of 0.
    while(true)
    {
        clean_input();
        std::wcout << L"\n\n > ";
        getline(std::wcin, raw_input);
        lower(raw_input); /// input has no point in being case-sensitive
        distribute_input();
        std::wcout << '\n';


        if (command == L"add")
        {
            arg1 = arg1.substr(0, NAME_LIMIT);
            arg2 = arg2.substr(0, DESC_LIMIT);
            Task new_task(arg1, arg2);
            tasks.push_back(new_task);

            show_info(L"Task created successfully [ID: " + std::to_wstring(tasks.size()) + L"].");
        }


        else if (command == L"delete" || command == L"remove")
        {
            if (arg1 == L"all")
            {
                tasks.clear();
                show_info(L"All tasks cleared!");
                continue;
            }
            else if (! is_num(arg1) || stoi(arg1) < 1)
            {
                show_error(L"Invalid ID!");
                continue;
            }
            else if (stoi(arg1) > tasks.size())
            {
                show_warning(L"No tasks of ID " + arg1 + L'!');
                continue;
            }

            tasks.erase(tasks.begin() + stoi(arg1)-1);
            show_info(L"Task deleted successfully!");
        }
        

        else if (command == L"list")
        {
            if (tasks.size() == 0)
            {
                show_warning(L"Task list is empty!");
                continue;
            }

            bool output_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if ((arg1 == L"all") || (tasks[i].updatable_properties[L"status"] == arg1))
                {
                    /// Proper separation of tasks (just in between)
                    if (output_happened)
                        std::wcout << L"\n\n";
                    output_happened = true;
                    tasks[i].output(i+1);
                }
            }

            if (! output_happened)
                show_warning(L"No tasks with such status!");
            continue;
        }


        else if (command == L"update")
        {
            if (! is_num(arg2) || stoi(arg2) < 1)
            {
                show_error(L"Invalid ID!");
                continue;
            }
            else if (stoi(arg2) > tasks.size())
            {
                show_warning(L"No tasks of ID " + arg2 + L'!');
                continue;
            }
            
            /// Update didn't take place
            if (! tasks[stoi(arg2)-1].update(arg1, arg3)) /// 'update()' function returns whether anything has been updated
                continue; /// No warning message since it's all handled by the 'Task' class
        }


        // TODO: check '\n's
        else if (command == L"help")
        {
            if (arg1 == L"")
                std::wcout << HELP_TEXT;
            else if (DETAILED_HELP.find(arg1) == DETAILED_HELP.end())
                show_warning(L"Command '" + arg1 + L"' doesn't exist.");
            else
                std::wcout << DETAILED_HELP.at(arg1);
            continue;
        }


        else
        {
            show_error(L"Unknown command!");
            continue;
        }

        save(tasks); /// only reached when changes truly happened
    }

    return 0;
}



void clean_input()
{
    std::wcin.clear();
    for (int i = 0; i < INPUT_VAR_AMOUNT; i++)
        input[i] = L"";
}



void distribute_input()
{
    std::wstringstream input_stream(raw_input);
    std::wstring word;
    bool quote_marks_open = false;
    int i = 0;

    while (input_stream >> word && i < 4)
    {
        if (word[0] == L'"') /// start of a multi-word argument [MWA]
        {
            quote_marks_open = true;
            input[i] += word.substr(1, word.size() - 1);
            continue;
        }

        if (quote_marks_open)
            input[i] += L' ' + word;
        if (word[word.size() - 1] == L'"') /// last word in an [MWA] cascades through the previous 'if' to here
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