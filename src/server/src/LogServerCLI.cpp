#include "LogServerCLI.h"
#include <thread>
#include <boost/bind/bind.hpp>
const std::vector<CommandDescription> LogServerCLI::command_descriptions_ ={
            CommandDescription({"help",{},"This help message"}),

            CommandDescription({"exit",{},"Quit the session"}),
            CommandDescription({"start",{},"Start server"}),
            CommandDescription({"setPort",{"int"},"Set port for server"}),
            CommandDescription({"stop",{},"Stop server"})

        };

void LogServerCLI::startServer(){
    if(!run_thread_ptr_){
    
        if (port_ == 0)
        {
          g_cout_s << "Please set the port number first!\n";
          return;
        }
        try
        {
          listener_ptr_ = std::make_unique<LogListener>(io_context_, port_);
          run_thread_ptr_ = std::make_unique<std::thread>(boost::bind(&boost::asio::io_context::run, &io_context_));
          g_cout_s <<"Server started on port "+std::to_string(port_)+"\n";
        }
        catch (std::exception& e)
        {
          g_cout_s << std::string("Exception: ") + e.what() + "\n";
        }
    } else{
        g_cout_s <<"Server is already running!\n";
    }
}
void LogServerCLI::stopServer(){
    if(run_thread_ptr_){
        io_context_.stop();
        run_thread_ptr_->join();
        run_thread_ptr_.reset(nullptr);
        listener_ptr_.reset(nullptr);
        g_cout_s <<"Server stopped on port "+std::to_string(port_)+"\n";
    } else{
        g_cout_s <<"Server was not running!\n";
    }
}


void LogServerCLI::handleCommand(const std::vector<std::string>& args){  
        if(args.size() == 0){
            printHelp(command_descriptions_);
        }
        if(args[0] == "exit"){
            if(run_thread_ptr_){
                stopServer();
            }
            g_cout_s << "exiting the program...\n";
            keep_running_ = false;
        }else if(args[0] == "start"){
            // start 
            startServer();
        }else if(args[0] == "setPort" && args.size() == 2){
            if(run_thread_ptr_){
                g_cout_s<<"Unable to change port while the server is running!\n";
            }else{
                try{
                    int x = stoi(args[1]);
                    if(x<1 || x>0xFFFF){
                        throw std::out_of_range("invalid port number");
                    } else{
                        port_ = x;
                        g_cout_s << "Server will be on port "+std::to_string(port_)+"\n";
                    }
                }catch(std::invalid_argument e){
                        g_cout_s << "Error:Port number is not an integer!\n";
                }catch(std::out_of_range e){
                    g_cout_s <<"Error: invalid port number!";
                }
            }
        }else if(args[0] == "stop"){
            stopServer();
        }else{
            printHelp(command_descriptions_);
        }
    }