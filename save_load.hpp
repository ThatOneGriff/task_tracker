#ifndef SAVE_LOAD_HPP
#define SAVE_LOAD_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "task.hpp"
using json = nlohmann::json;


std::vector<Task> load()
{
    std::vector<Task> tasks;
    std::ifstream f("tasks.json");
    if (f.peek() == std::ifstream::traits_type::eof())
        return tasks;
    
    const json data = json::parse(f);
    f.close();

    for (const auto& element: data)
    {
        Task task(element["name"], element["desc"], element["status"], element["created_at"], element["updated_at"]);
        tasks.push_back(task);
    }

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

    return tasks;
}


void save(std::vector<Task>& tasks)
{
    json data;
    for (Task& task : tasks)
        data.push_back(task.as_json());
    std::ofstream file("tasks.json");
    file << std::setw(4) << data << std::endl;
    file.close();
}


#endif