#include "utils.h"

std::vector<std::string> splitString(std::string input, std::string delimiter){
    std::vector<std::string> result;
    size_t pos;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        if(pos!= 0){
            result.push_back(input.substr(0, pos));
        }
        input.erase(0, pos + delimiter.length());
    }
    if(pos!= 0){
        result.push_back(input.substr(0, pos));
    }
    return result;
}