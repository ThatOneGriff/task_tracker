#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_set>
using json = nlohmann::json;


const std::unordered_set<std::string> task_statuses = {"todo", "in-progress", "done"};


class Task
{
public:

    std::string name;
    std::string status = "todo";


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


    // console-created task
    Task(const std::string& _name, const std::string& _desc, const std::string& _created_at)
    : name(_name), desc(_desc), created_at(_created_at)
    {
        std::cout << "Task created successfully [ID: *].";
    }


    // out-of-file task
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


    void output()
    {
        std::cout << "=== "             <<   name    << " [ID: *]\n\n"
                  <<                         desc    << '\n'
                  << " - Status: "     <<   status   << '\n'
                  << " - Created at: " << created_at << '\n'
                  << " - Updated at: " << updated_at;
    }


    void update_status(const std::string& new_status)
    {
        if (task_statuses.find(new_status) != task_statuses.end())
        {
            status = new_status;
            updated_at = get_cur_date_time();
            std::cout << "Status of task '" << name << "' successfully updated!";
        }
        else
            std::cout << "Invalid status!";
    }


private:

    std::string desc;
    std::string created_at;
    std::string updated_at = "-";
};


#endif