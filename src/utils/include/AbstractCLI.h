#pragma once
#include <memory>
#include "synchronized_io.h"
#include <iostream>
#include <csignal>
#include <vector>
#include "CommandDescription.h"

class AbstractCLI{
    public:
    AbstractCLI(std::string program_name);
    void start();
    protected:
    static void printHelp(const std::vector<CommandDescription>& command_descriptions);
    protected:
    bool keep_running_;
    private:
    virtual void handleCommand(const std::vector<std::string>& args) = 0;
    std::string program_name_;
};