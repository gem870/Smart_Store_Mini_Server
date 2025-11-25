#include <asio.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main() {
    try {
        asio::io_context ioc;

        // Listen on port 5000
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 5000));

        std::cout << "Server listening on port 5000..." << std::endl;

        for (;;) {
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            // Read incoming data
            char data[1024];
            asio::error_code ec;
            size_t len = socket.read_some(asio::buffer(data), ec);

            if (!ec) {
                std::string message(data, len);
                std::cout << "Received: " << message << std::endl;

                // Confirm back to client
                std::string reply = "Message received OK";
                asio::write(socket, asio::buffer(reply), ec);
            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }

            socket.close();
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}