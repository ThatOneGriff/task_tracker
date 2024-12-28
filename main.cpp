#include <iostream>
#include <string>
#include <vector>

#include "helper.hpp"
#include "save_load.hpp"



int main()
{
    std::vector<Task> tasks = load();
    std::string command, args;

    while(true)
    {
        std::cin >> command;
        
        if (command == "add")
        {
            unsigned int id;
            std::string name, desc;
            std::cin >> id >> name >> desc;
            
            name = name.substr(0, 20);
            desc = desc.substr(0, 50);
            Task new_task(id, name, get_cur_date_time(), desc);
        }

        std::cin.clear();
    }

return 0;
}