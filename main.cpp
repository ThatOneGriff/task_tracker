#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"

unsigned int max_id;



int main()
{
    std::vector<Task> tasks;
    max_id = load(tasks);
    std::string command, args;
    bool changes_happened;

    while(true)
    {
        changes_happened = true;
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
                        tasks[i].update_status(new_status);
                    else
                        std::cout << "No tasks with '" << search_arg << "' ID!";
                }
            }
            else
                std::cout << "Invalid ID!";
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
                        break;
                    }
                    else
                        std::cout << "No tasks with '" << search_arg << "' ID!";
                }
            }
            else
                std::cout << "Invalid ID!";
        }
        

        else if (command == "list-all")
        {
            changes_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].status == "deleted")
                    continue;
                tasks[i].output();
                std::cout << "\n\n";
            }
        }


        else if (command == "list-done")
        {
            changes_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].status == "done")
                {
                    tasks[i].output();
                    std::cout << "\n\n";
                }
            }
        }


        else if (command == "list-in-progress")
        {
            changes_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].status == "in-progress")
                {
                    tasks[i].output();
                    std::cout << "\n\n";
                }
            }
        }


        else if (command == "list-todo")
        {
            changes_happened = false;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].status == "todo")
                {
                    tasks[i].output();
                    std::cout << "\n\n";
                }
            }
        }

        std::cout << "\n";
        std::cin.clear();
        save(tasks);
    }

return 0;
}