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
    size_t buff_size{};
    long long send_time{};
    long long time_size{};
    size_t all_bytes_read{};
    std::vector<char> buffer;
public:
    explicit tcp_handler(size_t buffer_size);

    void connection_handler(tcp::socket socket);

    bool my_completion_condition(const boost::system::error_code &ec, std::size_t bytes_transferred) const;


};


#endif //LAB_2_CPP_TCP_HANDLER_HPP
