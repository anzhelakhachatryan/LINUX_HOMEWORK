#include "TcpServer.hpp"
#include <memory>

namespace SimpleNet {

TcpServer::TcpServer(int port, size_t threads)
	: listen_socket_(), pool_(threads)
{
	listen_socket_.bind(port);
	listen_socket_.listen();
}

	void TcpServer::run(ClientHandler handler) {
		while(true) {
			auto client = std::make_shared<Socket>(listen_socket_.accept());

			pool_.enqueue(
			[handler, client ] () {
				handler(std::move(*client));
			});	
		}

	}

}
