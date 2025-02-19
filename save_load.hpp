#ifndef SAVE_LOAD_HPP
#define SAVE_LOAD_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "task.hpp"
using json = nlohmann::json;


const std::string SAVE_PATH = "data.json";


std::vector<Task> load()
{
    std::vector<Task> tasks;
    std::ifstream f(SAVE_PATH);
    if (f.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << textcolor(YELLOW) << "No tasks loaded: data file '" << SAVE_PATH << "' not found.\n\n" << textcolor(WHITE);
        f.close();
        return tasks;
    }
    
    const json data = json::parse(f);
    f.close();

    tasks.reserve(data.size());
    for (const auto& element: data)
    {
        Task task(element["name"], element["desc"], element["status"], element["created_at"], element["updated_at"]);
        tasks.push_back(task);
    }

    switch (tasks.size())
    {
    case 0:
        std::cout << textcolor(YELLOW) << "No tasks loaded: data file '" << SAVE_PATH << "' is empty.\n\n" << textcolor(WHITE);
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
    std::ofstream file(SAVE_PATH);
    file << std::setw(4) << data << std::endl;
    file.close();
}


#endif