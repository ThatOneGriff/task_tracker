#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"



/* TODO
- might make a colored output function
- add build instructions to 'readme.md'
*/



int main()
{
    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    std::vector<Task> tasks = load();

    std::string command, arg1, arg2, arg3;
    
    // Note: minimal task ID in the interface is 1,
    // however, they're still stored in a vector,
    // thus have a minimal index of 0.
    while(true)
    {
        std::cout << "> ";
        std::cin >> command;

        if (command == "add")
        {
            std::cin >> arg1; // name
            getline(std::cin, arg2); // description
            
            arg1 = arg1.substr(0, NAME_LIMIT);
            arg2 = arg2.substr(0, DESC_LIMIT);
            Task new_task(arg1, arg2);
            tasks.push_back(new_task);

            textcolor(GREEN);
            std::cout << "Task created successfully [ID: " << tasks.size() << "].";
            textcolor(WHITE);
        }


        else if (command == "delete")
        {
            std::cin >> arg1; // ID

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
            std::cin >> arg1; // status to list
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
            std::cin >> arg1 >> arg2; // property, ID
            getline(std::cin, arg3);  // new value
            arg3.erase(0, 1);         // arguments are spaced with ' ', but 'getline' thinks it's a part of 'arg3'

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

            if (! tasks[stoi(arg2)-1].update(arg1, arg3)) // 'update()' also returns whether anything has been updated
                continue; // if update didn't happen
        }


        else
        {
            textcolor(RED);
            std::cout << "Unknown command!\n\n";
            textcolor(WHITE);
            continue;
        }


        std::cout << "\n\n";
        std::cin.clear();
        save(tasks); // is only reached if changes truly happened
    }

    return 0;
}