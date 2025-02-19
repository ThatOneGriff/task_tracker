#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"



/* TODO
- 'cout << GREEN << ... << WHITE' stuff
- invalid data handling
- non-case-sensitivity
- add build instructions to 'readme.md'
*/

/* POSSIBILITIES
- activity overview
- settings
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

        if (command == "add")
        {
            input >> arg1; // name
            getline(input, arg2); // description
            
            arg1 = arg1.substr(0, NAME_LIMIT);
            arg2 = arg2.substr(1, DESC_LIMIT + 1); // since 1st symbol is always a whitespace
            Task new_task(arg1, arg2);
            tasks.push_back(new_task);

            textcolor(GREEN);
            std::cout << "Task created successfully [ID: " << tasks.size() << "].";
            textcolor(WHITE);
        }


        else if (command == "delete" || command == "remove")
        {
            input >> arg1; // ID

            if (arg1 == "all")
            {
                tasks.clear();
                textcolor(GREEN);
                std::cout << "All tasks cleared!\n\n";
                textcolor(WHITE);
                continue;
            }
            if (! is_num(arg1) || stoi(arg1) < 1)
            {
                textcolor(RED);
                std::cout << "Invalid ID!\n\n";
                textcolor(WHITE);
                continue;
            }
            if (stoi(arg1) > tasks.size())
            {
                textcolor(YELLOW);
                std::cout << "No tasks of ID " << arg1 << "!\n\n";
                textcolor(WHITE);
                continue;
            }

            tasks.erase(tasks.begin() + stoi(arg1)-1);
            textcolor(GREEN);
            std::cout << "Task deleted successfully!";
            textcolor(WHITE);
        }


        else if (command == "help")
        {
            std::cout << HELP_TEXT << "\n\n";
            continue;
        }
        

        else if (command == "list")
        {
            input >> arg1; // status to list
            if (tasks.size() == 0)
            {
                textcolor(YELLOW);
                std::cout << "Task list is empty!\n\n";
                textcolor(WHITE);
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
            {
                textcolor(YELLOW);
                std::cout << "No tasks with such status!\n\n";
                textcolor(WHITE);
            }
            continue;
        }


        else if (command == "update")
        {
            input >> arg1; // property
            input >> arg2; // ID
            getline(input, arg3);  // new value
            arg3.erase(0, 1);      // since 1st symbol is always a whitespace

            if (! is_num(arg2) || stoi(arg2) < 1)
            {
                textcolor(RED);
                std::cout << "Invalid ID!\n\n";
                textcolor(WHITE);
                continue;
            }
            if (stoi(arg2) > tasks.size())
            {
                textcolor(YELLOW);
                std::cout << "No tasks of ID " << arg2 << "!\n\n";
                textcolor(WHITE);
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
            textcolor(RED);
            std::cout << "Unknown command!\n\n";
            textcolor(WHITE);
            continue;
        }


        std::cout << "\n\n";
        save(tasks); // only reached when changes truly happened
    }

    return 0;
}