#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;



int main()
{
    json j = {
        {"pi", 3.1415},
        {"1", true}
    };

    std::ofstream o("test.json");
    o << j << std::endl;
    o.close();

    return 0;
}