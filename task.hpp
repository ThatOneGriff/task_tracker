#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_set>
using json = nlohmann::json;


const std::unordered_set<std::string> task_statuses = {"todo", "in-progress", "done"};
const std::unordered_set<std::string> task_updatable_properties = {"name", "desc", "status"};


class Task
{
public:

    std::string name;
    std::string desc;
    std::string status = "todo";


    // Operators = and == are needed for erasing a task out of 'tasks' vector.
    bool operator==(Task task2)
    {
        if (name       == task2.name       &&
            desc       == task2.desc       && 
            status     == task2.status     &&
            created_at == task2.created_at &&
            updated_at == task2.updated_at) return true;
        return false;
    }


    Task operator=(Task task2)
    {
        if (*this == task2) return *this;

        name = task2.name;
        desc = task2.desc;
        status = task2.status;
        created_at = task2.created_at;
        updated_at = task2.updated_at;

        return *this;
    }


    // for console-created tasks
    Task(const std::string& _name, const std::string& _desc, const std::string& _created_at)
    : name(_name), desc(_desc), created_at(_created_at)
    {}


    // for loaded tasks
    Task(const std::string& _name, const std::string& _desc, const std::string& _status, const std::string& _created_at, const std::string& _updated_at)
    : name(_name), desc(_desc), created_at()
    {}


    json as_json()
    {
        json data = {
            {"name", name},
            {"desc", desc},
            {"status", status},
            {"created_at", created_at},
            {"updated_at", updated_at}
        };
        return data;
    }


    void output(const int id)
    {
        std::cout << "=== "             <<   name    << " [ID: " << id << "]\n\n"
                  <<                         desc    << '\n'
                  << " - Status: "     <<   status   << '\n'
                  << " - Created at: " << created_at << '\n'
                  << " - Updated at: " << updated_at;
    }


    bool update(const std::string& property, std::string& new_value) // 'update()' returns whether the update was successful
    {
        if (task_updatable_properties.find(property) == task_updatable_properties.end())
        {
            std::cout << "Property '" << property << "' doesn't exist or is not updatable!";
            return false;
        }

        if (property == "name")
        {
            new_value = new_value.substr(0, 20);
            name = new_value;
        }
        else if (property == "desc")
        {
            new_value = new_value.substr(0, 50);
            desc = new_value;
        }
        else if (property == "status")
        {
            if (task_statuses.find(new_value) == task_statuses.end())
            {
                std::cout << "Invalid status!";
                return false;
            }
            status = new_value;
        }
        
        updated_at = get_cur_date_time();
        std::cout << "Update successful!";
        return true;
    }


private:

    std::string created_at;
    std::string updated_at = "-";
};


#endif