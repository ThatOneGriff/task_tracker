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

    const unsigned int id;
    const std::string name;
    std::string status = "todo";


    // console-created task
    Task(const unsigned int _id, const std::string& _name, const std::string& _desc, const std::string& _created_at)
    : id(_id), name(_name), desc(_desc), created_at(_created_at)
    {
        std::cout << "Task created successfully [ID: " << id << "].";
    }


    // loaded task
    Task(const unsigned int _id, const std::string& _name, const std::string& _desc, const std::string& _created_at, const std::string& _updated_at)
    : id(_id), name(_name), desc(_desc), created_at()
    {}


    json as_json()
    {
        json data = {
            {"id", id},
            {"name", name},
            {"desc", desc},
            {"created_at", created_at},
            {"updated_at", updated_at}
        };
        return data;
    }


    void output()
    {
        std::cout << "=== "             <<   name    << " [ID: " << id << "]\n\n"
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
    const std::string created_at;
    std::string updated_at = "-";
};


#endif