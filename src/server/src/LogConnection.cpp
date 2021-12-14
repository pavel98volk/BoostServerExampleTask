#include "LogConnection.h"

void LogConnection::start(){
    read_message_size();
}
void LogConnection::read_message_size(){
    auto self(shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer((char*)&next_message_size_,2),
        [this, self](const boost::system::error_code& error, std::size_t length){
          if (!error){
            std::string result = "Next message size: ";
            result+=next_message_size_;
            g_cout_s << result+"\n";
            read_message();
          }else{
              g_cout_s <<"There was an error delivering the message or the client is disconnected!\n";
          }
        }); 
}



void LogConnection::read_message(){
  auto self(shared_from_this());
  boost::asio::async_read(socket_, boost::asio::buffer(buffer_,next_message_size_),
      [this, self](const boost::system::error_code& error, std::size_t length){
        if (!error){
          std::string result = "Message received from IP: ";
          result+=socket_.remote_endpoint().address().to_string();
          result+=", with data: ";
          result+= std::string(buffer_);
          g_cout_s << result+"\n";
          read_message_size();
        }else{
            g_cout_s <<"There was an error delivering the message or the client is disconnected!\n";
        }
      });

/* // this works, but async_receive does not guarantee to separate the input data stream to messages
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
    */
    /* // this version for some reason never calls the handler
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