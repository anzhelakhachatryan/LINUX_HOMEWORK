
#include "TcpServer.hpp"
#include "ThreadPool.hpp"
#include "Socket.hpp"
#include <iostream>
#include <string>

int main() {
    const int port = 8080;  
    const int thread_count = 4; 

    try {
      
        SimpleNet::TcpServer server(port);

        
        server.run([](SimpleNet::Socket client) {
            try {
               
                auto msg = client.receive();
                std::string text(msg.begin(), msg.end());
                std::cout << "Received: " << text << std::endl;

                client.send("Hello back!\n");
            } catch (const std::exception& e) {
                std::cerr << "Client error: " << e.what() << std::endl;
            }
        });

    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

