#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>
using json = nlohmann::json;


const std::unordered_map<std::string, const int> task_statuses_and_colors =
{
    {"todo",        GRAY},
    {"in-progress", YELLOW},
    {"done",        GREEN}
};


class Task
{
public:

    std::unordered_map<std::string, std::string> updatable_properties =
    {
        {"name",   ""},
        {"desc",   ""},
        {"status", "todo"}
    };

    // Operators = and == are needed for erasing a task out of 'tasks' vector.
    bool operator==(Task task2)
    {
        if (updatable_properties == task2.updatable_properties &&
            created_at           == task2.created_at           &&
            updated_at           == task2.updated_at)     return true;
        return false;
    }


    Task operator=(Task task2)
    {
        if (*this == task2) return *this;

        updatable_properties = task2.updatable_properties;
        created_at = task2.created_at;
        updated_at = task2.updated_at;

        return *this;
    }


    // for console-created tasks
    Task(const std::string& _name, const std::string& _desc)
    : created_at(get_cur_date_time())
    {
        updatable_properties["name"] = _name;
        updatable_properties["desc"] = _desc;
    }


    // for loaded tasks
    Task(const std::string& _name, const std::string& _desc, const std::string& _status, const std::string& _created_at, const std::string& _updated_at)
    : created_at(_created_at), updated_at(_updated_at)
    {
        updatable_properties["name"] = _name;
        updatable_properties["desc"] = _desc;
        updatable_properties["status"] = _status;
    }


    json as_json()
    {
        json data = {
            {"name", updatable_properties["name"]},
            {"desc", updatable_properties["desc"]},
            {"status", updatable_properties["status"]},
            {"created_at", created_at},
            {"updated_at", updated_at}
        };
        return data;
    }


    void output(const int id)
    {
        std::cout << "=== "            << updatable_properties["name"]   << " [ID: " << id << "]\n\n"
                  <<                      updatable_properties["desc"]   << '\n'
                  << " - Status: ";
        textcolor(task_statuses_and_colors.at(updatable_properties["status"])); // coloring status text in this status' predetermined color
        std::cout <<                      updatable_properties["status"] << '\n';
        textcolor(WHITE);
        std::cout << " - Created at: " << created_at                     << '\n'
                  << " - Updated at: " << updated_at;
    }


    bool update(const std::string& property, std::string& new_value) // 'update()' also returns whether anything has been updated
    {
        if (updatable_properties.find(property) == updatable_properties.end())
        {
            textcolor(RED);
            std::cout << "Property '" << property << "' doesn't exist or is not updatable!";
            textcolor(WHITE);
            return false;
        }
        
        // value preparation
        if (property == "name")
            new_value = new_value.substr(0, NAME_LIMIT);
        else if (property == "desc")
            new_value = new_value.substr(0, DESC_LIMIT);
        else if (property == "status")
        {
            new_value = new_value.substr(0, STATUS_LIMIT);
            if (task_statuses_and_colors.find(new_value) == task_statuses_and_colors.end())
            {
                textcolor(RED);
                std::cout << "Invalid status!";
                textcolor(WHITE);
                return false;
            }
        }

        // checking for false editing
        if (updatable_properties[property] == new_value)
        {
            textcolor(YELLOW);
            std::cout << "No changes have taken place: value is the same!";
            textcolor(WHITE);
            return false;
        }

        // updating
        updatable_properties[property] = new_value;
        updated_at = get_cur_date_time();
        textcolor(GREEN);
        std::cout << "Update successful!";
        textcolor(WHITE);
        return true;
    }


private:

    std::string created_at;
    std::string updated_at = "-";
};


#endif