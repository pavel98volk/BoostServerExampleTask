#include "LogListener.h"

void LogListener::do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<LogConnection>(std::move(socket))->start();
          }

          do_accept();
        });
  }