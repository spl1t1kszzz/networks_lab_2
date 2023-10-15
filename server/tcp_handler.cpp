#include <boost/bind/bind.hpp>
#include "server/tcp_handler.hpp"


void tcp_handler::connection_handler(tcp::socket socket) {
    boost::asio::io_service ioService;
    boost::asio::deadline_timer timer(ioService, boost::posix_time::seconds(3));
    boost::asio::streambuf stream_buffer;
    // getting file name and size
    size_t bytes_read = boost::asio::read_until(socket, stream_buffer, "\r\n");
    std::istream filename_size_stream(&stream_buffer);
    std::string filename_size;
    auto extra_data = stream_buffer.size() - bytes_read;
    std::getline(filename_size_stream, filename_size);
    std::string filename = filename_size.substr(0, filename_size.find('\0'));
    this->file_size = std::stoul(filename_size.substr(filename_size.find('\0') + 1, filename_size.find('\t')));
    auto time_size = std::stoul(filename_size.substr(filename_size.find('\t') + 1, bytes_read));
    if (std::filesystem::exists("uploads/" + filename)) {
        std::cerr << "this file is already exists!" << std::endl;
        boost::asio::write(socket, boost::asio::buffer("rename the file plz\r\r\r"));
        socket.close();
        return;
    } else {
        boost::asio::write(socket, boost::asio::buffer("ok\r\r\r"));
    }
    std::ofstream file("uploads/" + filename, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "File not open: uploads/test.txt" << std::endl;
        return;
    }

    if (extra_data > 0) {
        this->all_bytes_read += extra_data;
        std::vector<char> extra_vector(extra_data);
        filename_size_stream.read(extra_vector.data(), extra_data);
        std::cout << "extra data: " << extra_vector.size() << std::endl;
        for (const auto &c: extra_vector) {
            file << c;
        }
    }

    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket udp_socket(io_service);
    boost::asio::ip::udp::endpoint end(boost::asio::ip::address::from_string("127.0.0.1"), 1337);
    udp_socket.open(end.protocol());
    // Data
    size_t bytesReceived;
    auto start = timer::get_time();
    while (true) {
        try {
            if (this->all_bytes_read >= this->file_size) {
                std::cout << "File " + filename + " successfully received" << std::endl;
                udp_socket.send_to(boost::asio::buffer(filename + ": done"), end);
                break;
            }
            bytesReceived =
                    boost::asio::read(socket, boost::asio::buffer(this->buffer), boost::asio::transfer_at_least(1)) -
                    time_size;
            auto end_receive = timer::get_time();
            this->all_bytes_read += bytesReceived;
            try {
                this->send_time = std::stoll(std::string(this->buffer.begin(), this->buffer.begin() + time_size));
            } catch (const std::invalid_argument& ex) {
                std::cerr << bytesReceived << std::endl;
                std::cerr << std::string(this->buffer.begin(), this->buffer.begin() + time_size) << std::endl;
                throw ex;
            }
            long double time_for_receive = (end_receive - this->send_time) / 1000000.0;
            long double all_time = (end_receive - start) / 1000000.0;

            long double current_speed = (bytesReceived / 1024.0 / 1024.0) / time_for_receive;
            long double average_speed = (this->all_bytes_read / 1024.0 / 1024.0) / all_time;
            std::cout << bytesReceived << ' ' << end_receive - this->send_time << ", cur: " << current_speed << " MB/s avg: " << average_speed << std::endl;

            //udp_socket.send_to(boost::asio::buffer(
                 //   filename + ": " + std::to_string(current_speed) + " (average " + std::to_string(average_speed) + " MB/s)"), end);
            //file.write(buffer.data() + time_size, bytesReceived);
        } catch (boost::system::system_error &e) {
            boost::asio::write(socket, boost::asio::buffer(std::string(e.what())));
            break;
        }
    }

    boost::asio::write(socket, boost::asio::buffer("ok"));
    socket.close();
    file.close();
    std::cout << "bye" << std::endl << std::endl;
}

tcp_handler::tcp_handler(size_t buffer_size) {
    this->buffer.resize(buffer_size);
    this->all_bytes_read = 0;

}



