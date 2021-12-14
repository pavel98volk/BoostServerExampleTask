#pragma once

#include <boost/asio.hpp>
#include "LogConnection.h"

using boost::asio::ip::tcp;

class LogListener
{
public:
  LogListener(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept();

  tcp::acceptor acceptor_;
};