#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int sfd;

void* receive_messages(void*) {
    char buffer[BUFFER_SIZE];
    while (true) {
        int bytes = recv(sfd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) {
            std::cout << "discnd from server\n";
            break;
        }
        buffer[bytes] = '\0';
        std::cout << buffer;
        std::cout.flush();
    }
    return nullptr;
}

int main() {
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sfd, (sockaddr*)&server_addr, sizeof(server_addr));

    std::string name;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    name += "\n";
    send(sfd, name.c_str(), name.size(), 0);

    pthread_t recv_thread;
    pthread_create(&recv_thread, nullptr, receive_messages, nullptr);
    pthread_detach(recv_thread);

    std::string msg;

    while (true) {
        std::getline(std::cin, msg);
        if (msg.empty())
			 continue;

        msg += "\n";
        send(sfd, msg.c_str(), msg.size(), 0);
        if (msg == "/exit\n") 
			break;

    }

    close(sfd);
    return 0;
}
