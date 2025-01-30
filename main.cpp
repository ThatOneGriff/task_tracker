#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"



int main()
{
    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    std::vector<Task> tasks = load();

    std::string command, arg1, arg2, arg3;
    bool changes_happened = false;

    while(true)
    {
        std::cin >> command;

        if (command == "add")
        {
            std::cin >> arg1; // name
            getline(std::cin, arg2); // description
            
            arg1 = arg1.substr(0, 20);
            arg2 = arg2.substr(0, 50);
            Task new_task(arg1, arg2, get_cur_date_time());
            tasks.push_back(new_task);
            std::cout << "Task created successfully [ID: " << tasks.size() - 1 << "].";
            changes_happened = true;
        }


        else if (command == "delete")
        {
            std::cin >> arg1; // ID

            if (! is_num(arg1))
            {
                std::cout << "Invalid ID!\n\n";
                continue;
            }
            if (stoi(arg1) >= tasks.size())
            {
                std::cout << "No tasks of ID " << arg1 << "!\n\n";
                continue;
            }

            tasks.erase(tasks.begin() + stoi(arg1));
            changes_happened = true;
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
                continue;
            for (int i = 0; i < tasks.size(); i++)
            {
                if ((arg1 == "all") || (tasks[i].status == arg1))
                {
                    tasks[i].output(i);
                    std::cout << "\n\n";
                }
            }
            continue;
        }


        else if (command == "update")
        {
            std::cin >> arg1 >> arg2; // to update, ID
            getline(std::cin, arg3);  // new value
            arg3.erase(0, 1);         // arguments are spaced with ' ', but 'getline' thinks it's a part of 'arg3'

            if (task_updatable_properties.find(arg1) == task_updatable_properties.end())
            {
                std::cout << "Task property '" << arg1 << "' doesn't exist or isn't updatable!\n\n";
                continue;
            }
            if (! is_num(arg2))
            {
                std::cout << "Invalid ID!\n\n";
                continue;
            }
            if (stoi(arg2) >= tasks.size())
            {
                std::cout << "No tasks of ID " << arg2 << "!\n\n";
                continue;
            }

            changes_happened = tasks[stoi(arg2)].update(arg1, arg3); // 'update()' returns whether the update was successful
        }


        std::cout << "\n\n";
        std::cin.clear();
        if (changes_happened)
        {
            save(tasks);
            changes_happened = false;
        }
    }

    return 0;
}