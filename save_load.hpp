#pragma once
#ifndef SAVE_LOAD_HPP
#define SAVE_LOAD_HPP

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

#include "helper.hpp"
#include "task.hpp"
using json = nlohmann::json;


const std::wstring SAVE_PATH = L"data.json";


std::vector<Task> load()
{
    std::vector<Task> tasks;
    std::ifstream f(SAVE_PATH);
    if (f.peek() == std::ifstream::traits_type::eof())
    {
        show_warning(L"No tasks loaded: data file '" + SAVE_PATH + L"' not found.");
        f.close();
        return tasks;
    }
    
    const json data = json::parse(f);
    f.close();

    tasks.reserve(data.size());
    for (const auto& element: data)
    {
        // IDEA: a less fragile load system that avoids errors
        Task task(element[L"name"], element[L"desc"], element[L"status"], element[L"created_at"], element[L"updated_at"]);
        tasks.push_back(task);
    }

    switch (tasks.size())
    {
    case 0:
        show_warning(L"No tasks loaded: data file '" + SAVE_PATH + L"' is empty.");
        break;
    case 1:
        std::wcout << L"1 task loaded.";
        break;
    default:
        std::wcout << tasks.size() << L" tasks loaded.";
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
    // WARNING: setw(8)?
    file << std::setw(4) << data << std::endl;
    file.close();
}


#endif