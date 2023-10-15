#include "tcp_client.hpp"
#include <fstream>
#include <iostream>

using namespace boost::asio;

tcp_client::tcp_client(const std::string &path, const std::string &address, boost::asio::io_service &service, int port)
        : socket(service) {
    this->file_path = path;
    this->port = port;
    this->address = address::from_string(address);
    auto file_size = std::filesystem::file_size(this->file_path);
    if (file_size >= TERABYTE) {
        std::cerr << "too big file!" << std::endl;
    }
}

void tcp_client::send_file() {
    ip::tcp::endpoint endpoint(this->address, this->port);
    this->socket.open(endpoint.protocol());
    this->socket.connect(endpoint);

    std::ifstream file(this->file_path, std::ios::binary);

    auto time_size = std::to_string(timer::get_time()).length();

    write(socket,
          buffer(this->file_path + '\0' + std::to_string(std::filesystem::file_size(this->file_path)) + '\t' +
                 std::to_string(time_size) + "\r\n"));
    std::string server_response;
    boost::asio::read_until(socket, boost::asio::dynamic_buffer(server_response), "\r\r\r");
    auto resp = server_response.substr(0, server_response.find('\r'));
    if (resp != "ok") {
        std::cerr << resp << std::endl;
        socket.close();
        return;
    }
    std::cout << this->file_path + '\0' + std::to_string(std::filesystem::file_size(this->file_path)) + "\r\n";
    std::vector<char> buffer(20000);
    while (!file.eof() && !server_response.empty()) {
        std::string cur_time = std::to_string(timer::get_time());
        std::copy(cur_time.begin(), cur_time.end(), buffer.begin());
        file.read(buffer.data() + time_size, 20000 - time_size);
        auto bytesRead = file.gcount() + time_size;
        write(socket, boost::asio::buffer(buffer, bytesRead));

    }

    read(socket, boost::asio::buffer(server_response), boost::asio::transfer_at_least(2));

    auto response_end = std::find(server_response.begin(), server_response.end(), '\0');

    if (std::string(server_response.begin(), response_end) != "ok") {
        std::cerr << "error occurred while send: " << std::endl;
    } else {
        std::cout << "file " + this->file_path + " successfully sent" << std::endl;
    }
    socket.shutdown(boost::asio::socket_base::shutdown_send);
    socket.close();
    file.close();
}
