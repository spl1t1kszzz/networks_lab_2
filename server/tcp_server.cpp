#include "tcp_server.hpp"
#include "tcp_handler.hpp"

tcp_server::tcp_server(int port, boost::asio::io_service &service, size_t buffer_size) : service(service) {
    this->port = port;
    this->buffer_size = buffer_size;
}


void tcp_server::receive_files() {
    tcp::acceptor acceptor(this->service, tcp::endpoint(tcp::v4(), this->port));
    acceptor.listen();

    for (;;) {
        tcp::socket clientSocket(this->service);
        acceptor.accept(clientSocket);
        boost::asio::io_service ioService;
        tcp_handler handler(this->buffer_size);
        std::thread(&tcp_handler::connection_handler, handler, std::move(clientSocket)).detach();
    }

}
