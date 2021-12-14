#pragma once
#include <memory>
#include "synchronized_io.h"
#include <iostream>
#include "AbstractCLI.h"
#include "CommandDescription.h"
#include <vector>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class LogClientCLI: public AbstractCLI{
    public:
    LogClientCLI():
        AbstractCLI("Client"),
        port(0),
        context_(),
        socket_(context_),
        resolver_(context_),
        connection_active_(false){}
    private:
    void handleCommand(const std::vector<std::string>& args) override;
    void connect(std::string ip_string, std::string port_string);
    void send_message(std::string message);
    uint16_t port;
    static const std::vector<CommandDescription> command_descriptions_;
    boost::asio::io_context context_;
    tcp::socket socket_;
    tcp::resolver resolver_;
    bool connection_active_;
};