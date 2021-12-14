
#include "LogClientCLI.h"
#include "utils.h"
#include "synchronized_io.h"

const std::vector<CommandDescription> LogClientCLI::command_descriptions_ = {
        CommandDescription({"help",{},"Show this message"}),
        CommandDescription({"exit",{},"Quit the session"}),
        CommandDescription({"connect",{"string"},"Connect to server"}),
        CommandDescription({"send",{"string"},"Send message"})
    };

void LogClientCLI::connect(std::string ip_string, std::string port_string){
    try{
    g_cout_s << "Connect to "+ip_string+":"+port_string+"\n";
    boost::asio::connect(socket_, resolver_.resolve(ip_string, port_string));
    connection_active_ = true;
    g_cout_s << "Successfully connected\n";
    }catch(std::exception& e){
        std::cerr << "Connection failed: " << e.what() << "\n";
    }
}

void LogClientCLI::send_message(std::string message){
    std::string x;
    std::string recepient_address = socket_.remote_endpoint().address().to_string() + ":" + std::to_string(socket_.remote_endpoint().port());
    try{
    boost::asio::write(socket_,boost::asio::buffer(message.c_str(), message.size()));
        
    std::string output = "Message sent to ";
    output += recepient_address;
    output += " with data: ";
    output += message;
    g_cout_s << output+"\n";

    }catch(std::exception e){
        connection_active_ = false;
        g_cout_s << std::string("Error during sending a message: ")+e.what()+"\n";
    }

    /*
    socket_.async_send(boost::asio::buffer((message).c_str(), message.size()),
        [=](boost::system::error_code error, std::size_t){
          if (!error){
            std::string output = "Message sent to ";
            output += recepient_address;
            output += " with data: ";
            output += message;
            g_cout_s << message+"\n";
          } else{
              g_cout_s <<"There was an error delivering the message!\n";
          }
        });*/
}

void LogClientCLI::handleCommand(const std::vector<std::string>& args){  
    if(args.size() == 0){
        printHelp(command_descriptions_);
    } else if(args[0] == "exit"){
        g_cout_s << "Exiting....\n";
        keep_running_ = false;
    }else if(args[0] == "connect" && args.size() == 2){
        //1. split address to ip_string and port_string
        std::vector<std::string>ip_port = splitString(args[1],":");
        if(ip_port.size() != 2){
            g_cout_s << "Please enter this command using notation similar to \"connect 127.0.0.1:9999\"";
            return;
        }
        connect(ip_port[0],ip_port[1]);
        
    }else if(args[0] == "send" && args.size() >= 2){
        std::string message;
        for(int i =1;i<args.size();i++){
            message+=args[i]+" ";
        }
        message.pop_back(); // removing last space.
        send_message(message);
    }else{
        printHelp(command_descriptions_);
    }
}