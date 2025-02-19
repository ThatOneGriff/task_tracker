#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"



/* TODO
- invalid data handling
- dailies, due dates
- names that are multiple words long without manually changing it to be so ?=> input modes
- add build instructions to 'readme.md'
- make the project fine with moving into different folders
*/

/* POSSIBILITIES
- "simple" (current) and "advanced" (add --name "..." --desc "...") input modes => settings
- activity overview
- settings
- storing saved data anywhere => handling absolute paths
*/



int main()
{
    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    std::vector<Task> tasks = load();

    std::string unprocessed_input;
    std::stringstream input;

    std::string command;
    std::string arg1, arg2, arg3;
    
    // Note: minimal ID of a task IN THE INTERFACE is 1,
    // however, they're still stored in a vector,
    // thus have a FACTUAL, IN-CODE minimal index of 0.
    while(true)
    {
        // cleaning leftover input
        //getline(input, unprocessed_input);
        input.clear();
        std::cin.clear();

        std::cout << "> ";
        getline(std::cin, unprocessed_input);
        input << unprocessed_input;
        input >> command;
        lower(command); // non-case sensitivity

        if (command == "add")
        {
            input >> arg1; // name
            getline(input, arg2); // description
            
            arg1 = arg1.substr(0, NAME_LIMIT);
            arg2 = arg2.substr(1, DESC_LIMIT + 1); // since 1st symbol is always a whitespace
            Task new_task(arg1, arg2);
            tasks.push_back(new_task);

            std::cout << textcolor(GREEN) << "Task created successfully [ID: " << tasks.size() << "]." << textcolor(WHITE);
        }


        else if (command == "delete" || command == "remove")
        {
            input >> arg1; // ID
            lower(arg1); // non-case sensitivity

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

            input >> arg1; // status to list
            lower(arg1); // non-case sensitivity

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
            input >> arg1; // property
            lower(arg1); // non-case sensitivity
            input >> arg2; // ID
            getline(input, arg3);  // new value
            arg3.erase(0, 1);      // since 1st symbol is always a whitespace

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
            
            // if update didn't take place
            if (! tasks[stoi(arg2)-1].update(arg1, arg3)) // 'update()' function returns whether anything has been updated
            {
                std::cout << "\n\n";
                continue; // No warning message since it's all handled by the 'Task' class
            }
        }


        else
        {
            std::cout << textcolor(RED) << "Unknown command!\n\n" << textcolor(WHITE);
            continue;
        }


        std::cout << "\n\n";
        save(tasks); // only reached when changes truly happened
    }

    return 0;
}