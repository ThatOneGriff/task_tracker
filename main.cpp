#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"

unsigned int max_id;


/* TODO
- "task not found" while deleting
- 'help' command */



int main()
{
    std::vector<Task> tasks;
    max_id = load(tasks);


    std::cout << " === Task Tracker (type 'help' to list all commands) ===\n\n";
    switch (tasks.size())
    {
    case 0:
        std::cout << "No tasks loaded.\n\n";
        break;
    case 1:
        std::cout << "1 task loaded.\n\n";
        break;
    default:
        std::cout << tasks.size() << " tasks loaded.\n\n";
        break;
    }


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
            Task new_task(++max_id, name, desc, get_cur_date_time());
            tasks.push_back(new_task);
            changes_happened = true;
        }


        else if (command == "delete")
        {
            std::string search_arg;
            std::cin >> search_arg;

            if (is_num(search_arg))
            {
                for (int i = 0; i < tasks.size(); i++)
                {
                    if (tasks[i].id == stoi(search_arg))
                    {
                        tasks[i].status = "deleted";
                        changes_happened = true;
                        break;
                    }
                    else
                        std::cout << "No tasks with '" << search_arg << "' ID!";
                }
            }
            else
                std::cout << "Invalid ID!";
        }
        

        else if (command == "list")
        {
            std::string status_to_list;
            std::cin >> status_to_list;
            
            for (int i = 0; i < tasks.size(); i++)
            {
                if ((status_to_list == "all") && (tasks[i].status != "deleted") || (tasks[i].status == status_to_list))
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

            if (is_num(search_arg))
            {
                for (int i = 0; i < tasks.size(); i++)
                {
                    if (tasks[i].id == stoi(search_arg))
                    {
                        tasks[i].update_status(new_status);
                        changes_happened = true;
                    }
                    else
                        std::cout << "No tasks with '" << search_arg << "' ID!";
                }
            }
            else
                std::cout << "Invalid ID!";
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