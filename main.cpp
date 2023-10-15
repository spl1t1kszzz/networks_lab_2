#include <iostream>
#include <boost/asio.hpp>
#include "client/tcp_client.hpp"
#include "server/tcp_server.hpp"


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough args" << std::endl;
        return -1;
    }
    boost::asio::io_service io_service;
    if (strcmp(argv[1], "send") == 0) {
        tcp_client client(std::string(argv[2]), std::string(argv[3]), io_service, std::stoi(argv[4]));
        client.send_file();
    } else if (strcmp(argv[1], "listen") == 0) {
        std::system("open -g -a /Users/nikson/Downloads/networks_lab_2_cpp/cmake-build-debug/lab_2.app");
        tcp_server server(std::stoi(argv[2]), io_service);
        server.receive_files();
    }
    return 0;
}
