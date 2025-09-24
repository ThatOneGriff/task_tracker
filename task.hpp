#pragma once
#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "helper.hpp"
using json         = nlohmann::json;
using json_element = nlohmann::json_abi_v3_11_3::basic_json<>;



const std::unordered_map<std::wstring, const int> color_code_by_status =
{
    {L"todo",        8}, /* GRAY */
    {L"in-progress", 6}, /* YELLOW */
    {L"done",        2}  /* GREEN */
    /// Colors done by 'int's due to new text coloring system.
};


class Task
{
public:

    std::unordered_map<std::wstring, std::wstring> updatable_properties =
    {
        {L"name",   L""},
        {L"desc",   L""},
        {L"status", L"todo"}
    };

    /// Operators = and == are needed for erasing a task out of 'tasks' vector.
    bool operator==(Task task2)
    {
        if (updatable_properties == task2.updatable_properties &&
            created_at           == task2.created_at           &&
            updated_at           == task2.updated_at)
            return true;
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


    /// For console-created tasks.
    Task(const std::wstring& _name, const std::wstring& _desc)
    : created_at(get_cur_date_time())
    {
        updatable_properties[L"name"] = _name;
        updatable_properties[L"desc"] = _desc;
    }


    /// For loaded tasks. DEPRECATED
    /*Task(const std::wstring& _name, const std::wstring& _desc, const std::wstring& _status, const std::wstring& _created_at, const std::wstring& _updated_at)
    : created_at(_created_at), updated_at(_updated_at)
    {
        updatable_properties[L"name"] = _name;
        updatable_properties[L"desc"] = _desc;
        updatable_properties[L"status"] = _status;
    }*/


    /// For loaded tasks.
    Task(const json_element data)
    {
        //Task task(element[L"name"], element[L"desc"], element[L"status"], element[L"created_at"], element[L"updated_at"]);
        
    }


    json as_json()
    {
        json data = {
            {"name",   to_utf8(updatable_properties[L"name"])},
            {"desc",   to_utf8(updatable_properties[L"desc"])},
            {"status", to_utf8(updatable_properties[L"status"])},
            {"created_at", to_utf8(created_at)},
            {"updated_at", to_utf8(updated_at)}
        };
        return data;
    }


    void output(const int id)
    {
        std::wcout << L"=== "           << updatable_properties[L"name"] << L" [ID: " << id << L"]\n"
                   <<                      updatable_properties[L"desc"] << L'\n'
                   << L" - Status: "
                     << textcolor(color_code_by_status.at(updatable_properties[L"status"]))
                     << updatable_properties[L"status"] << '\n'
                     << WHITE
                   << L" - Created at: " << created_at  << '\n'
                   << L" - Updated at: " << updated_at;
    }


    bool update(const std::wstring& property, std::wstring& new_value) /// 'update()' also returns whether anything has been updated
    {
        if (updatable_properties.find(property) == updatable_properties.end())
        {
            show_error(L"Task property '" + property + L"' doesn't exist or is not updatable!");
            return false;
        }
        
        /// value preparation
        // IDEA: auto limiting. 'Updatable properties' obj?
        if (property == L"name")
            new_value = new_value.substr(0, NAME_LIMIT);
        else if (property == L"desc")
            new_value = new_value.substr(0, DESC_LIMIT);
        else if (property == L"status")
        {
            new_value = new_value.substr(0, STATUS_LIMIT);
            lower(new_value);
            if (color_code_by_status.find(new_value) == color_code_by_status.end())
            {
                show_error(L"Invalid status!");
                return false;
            }
        }

        /// checking for false editing
        if (updatable_properties[property] == new_value)
        {
            show_warning(L"No changes have taken place: value is the same!");
            return false;
        }

        /// updating
        updatable_properties[property] = new_value;
        updated_at = get_cur_date_time();
        show_info(L"Update successful!");
        return true;
    }


private:

    std::wstring created_at = L"";
    std::wstring updated_at = L"-";
};


#endif