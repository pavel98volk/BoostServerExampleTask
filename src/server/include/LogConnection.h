#pragma once
/*#include <cstdlib>
#include <memory>
#include <utility>*/
#include <boost/asio.hpp>
#include "synchronized_io.h"

using boost::asio::ip::tcp;

class LogConnection
  : public std::enable_shared_from_this<LogConnection>
{
public:
  LogConnection(tcp::socket socket)
    : socket_(std::move(socket)){}

  void start();

private:
  void read_message_size();
  void read_message();


  tcp::socket socket_;
  static const int BUFFER_SIZE = 0x10000;
  unsigned short next_message_size_;
  char buffer_[BUFFER_SIZE];
  boost::asio::streambuf s_buf_;
  
};