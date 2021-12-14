#include "LogConnection.h"

void LogConnection::start(){
    read_message();
}

void LogConnection::read_message(){
  auto self(shared_from_this());
  socket_.async_receive(boost::asio::buffer(buffer_,BUFFER_SIZE),
      [this, self](const boost::system::error_code& error, std::size_t length){
        if (!error){
          std::string result = "Message received from IP: ";
          result+=socket_.remote_endpoint().address().to_string();
          result+=", with data: ";
          result+= std::string(buffer_);
          g_cout_s << result+"\n";
          read_message();
        }else{
            g_cout_s <<"There was an error delivering the message or the client is disconnected!\n";
        }
      });

    /*
    boost::asio::async_read_until(socket_,s_buf_,'\n',
      [this, self](const boost::system::error_code& error, std::size_t length){
        if (!error){ 
          std::string result = "Message received from IP: ";
          result+=socket_.remote_endpoint().address().to_string();
          result+=", with data: ";
          //std::string data;
          //std::getline(std::istream(&s_buf_), data);
          //result+= data;
          //g_cout_s << result+"\n";
        }else{
            g_cout_s <<"There was an error delivering the message!\n";
        }
      });*/
}