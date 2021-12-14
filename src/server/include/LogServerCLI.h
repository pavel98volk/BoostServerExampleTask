#pragma once
#include <memory>
#include "synchronized_io.h"
#include <iostream>
#include <signal.h>
#include "AbstractCLI.h"
#include "LogListener.h"
#include "CommandDescription.h"
#include <vector>
#include <boost/asio.hpp>

class LogServerCLI: public AbstractCLI{
    public:
    LogServerCLI():
        AbstractCLI("Server"),
        port_(0),
        listener_ptr_(nullptr) {}
    private:

    void handleCommand(const std::vector<std::string>& args) override;
    void startServer();
    void stopServer();
    uint16_t port_;
    boost::asio::io_context io_context_;
    std::unique_ptr<std::thread> run_thread_ptr_;
    std::unique_ptr<LogListener> listener_ptr_;
    static const std::vector<CommandDescription> command_descriptions_;
};