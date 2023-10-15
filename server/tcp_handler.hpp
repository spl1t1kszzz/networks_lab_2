#ifndef LAB_2_CPP_TCP_HANDLER_HPP
#define LAB_2_CPP_TCP_HANDLER_HPP


#include <cstddef>
#include <iostream>
#include <boost/asio.hpp>
#include <functional>
#include <fstream>
#include <string>
#include <codecvt>
#include "timer/timer.hpp"


using namespace boost::asio::ip;

class tcp_handler {
private:
    size_t file_size{};
    long long send_time{};
    size_t all_bytes_read{};
    std::vector<char> buffer;
    void timer_handler(const boost::system::error_code& e);
public:
    explicit tcp_handler(size_t buffer_size);

    void connection_handler(tcp::socket socket);


};


#endif //LAB_2_CPP_TCP_HANDLER_HPP
