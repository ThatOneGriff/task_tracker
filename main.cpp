#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"


/* TODO
- Standardize console argument variables
- 'help' command
- solve 'erase' riddle */



int main()
{
    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    std::vector<Task> tasks = load();

    std::string command;
    bool changes_happened = false;

    while(true)
    {
        std::cin >> command;

        if (command == "add")
        {
            std::string name, desc;
            std::cin >> name;
            getline(std::cin, desc);
            
            name = name.substr(0, 20);
            desc = desc.substr(0, 50);
            Task new_task(name, desc, get_cur_date_time());
            tasks.push_back(new_task);
            changes_happened = true;
        }


        else if (command == "delete")
        {
            std::string search_arg;
            std::cin >> search_arg;

            if (! is_num(search_arg))
            {
                std::cout << "Invalid ID!";
                continue;
            }
            if (stoi(search_arg) >= tasks.size())
            {
                std::cout << "No tasks of ID " << search_arg << "!";
                continue;
            }

            tasks.erase(tasks.begin() + stoi(search_arg));
            changes_happened = true;
        }
        

        else if (command == "list")
        {
            std::string status_to_list;
            std::cin >> status_to_list;
            
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].status == "deleted")
                    continue;
                
                if ((status_to_list == "all") || (tasks[i].status == status_to_list))
                {
                    if (i > 0) std::cout << "\n\n";
                    tasks[i].output();
                }
            }
        }


        else if (command == "update-status")
        {
            std::string search_arg, new_status;
            std::cin >> search_arg >> new_status;

            if (! is_num(search_arg))
            {
                std::cout << "Invalid ID!";
                continue;
            }
            if (stoi(search_arg) >= tasks.size())
            {
                std::cout << "No tasks of ID " << search_arg << "!";
                continue;
            }

            tasks[stoi(search_arg)].update_status(new_status);
            changes_happened = true;
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