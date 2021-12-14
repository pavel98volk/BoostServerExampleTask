#include "AbstractCLI.h"
#include <string>
#include <vector>
#include "utils.h"

AbstractCLI::AbstractCLI(std::string program_name):
    program_name_(program_name),keep_running_(true){};

void AbstractCLI::start(){
    std::string input_string;
    while(keep_running_){
        g_cout_s << program_name_+">";
        std::getline(std::cin,input_string); 
        handleCommand(splitString(input_string," "));
    }
}

void AbstractCLI::printHelp(const std::vector<CommandDescription>& descriptions){
    std::string output = "Commands available:\n";
    for(const CommandDescription& cd: descriptions){
        output+=" - "+cd.name;
        for(const std::string& arg_type: cd.parameter_types){
            output+=" <"+arg_type+">";
        }
        output+="\n         "+cd.description+"\n";
    }
    g_cout_s << output;
}