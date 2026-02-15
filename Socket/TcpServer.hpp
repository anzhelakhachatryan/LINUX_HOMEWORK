#pragma once

#include "Socket.hpp"
#include "ThreadPool.hpp"
#include <functional>

namespace SimpleNet {
using ClientHandler = std::function<void(Socket)>;

class TcpServer {
public:
	TcpServer(int port, size_t threads = std::thread::hardware_concurrency());
	void run(ClientHandler handler);

private:
	Socket listen_socket_;
	ThreadPool pool_;

};

}
