#ifndef LAB_2_CPP_TCP_SERVER_HPP
#define LAB_2_CPP_TCP_SERVER_HPP
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <functional>
#include <fstream>
#include <chrono>


using namespace boost::asio::ip;

class tcp_server {
private:
    int port;
    boost::asio::io_service& service;
    size_t buffer_size;
public:

    tcp_server(int port, boost::asio::io_service& service, size_t buffer_size);

    [[noreturn]] void receive_files();

};


#endif //LAB_2_CPP_TCP_SERVER_HPP
