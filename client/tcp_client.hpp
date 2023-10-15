#ifndef LAB_2_CPP_TCP_CLIENT_HPP
#define LAB_2_CPP_TCP_CLIENT_HPP

#include <boost/asio.hpp>
#include "timer/timer.hpp"

using namespace boost::asio::ip;
constexpr auto TIME_SIZE = 13;
constexpr auto TERABYTE = 1024ULL * 1024 * 1024 * 1024;

class tcp_client {
private:
    std::string file_path;
    address address;
    int port;
    tcp::socket socket;
public:
    tcp_client(const std::string& path, const std::string& address, boost::asio::io_service& service, int port);

    void send_file();
};


#endif //LAB_2_CPP_TCP_CLIENT_HPP