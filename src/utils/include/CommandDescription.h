#pragma once
#include <string>
#include <vector>
struct CommandDescription{
    CommandDescription(std::string name, std::vector<std::string> parameter_types, std::string description):
        name(name), parameter_types(parameter_types), description(description){};
    std::string name;
    std::vector<std::string> parameter_types;
    std::string description;
};