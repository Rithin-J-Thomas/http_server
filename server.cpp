#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cerrno>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

#define MYPORT "8080"
#define BACKLOG 5 // //BACKLOG is the number of connections allowed on the incoming queue.

int main()
{

	std::cout << "Server Started\n";
	struct sockaddr_storage clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	char clientDataBuff[1024];

	const char *response =
	    "HTTP/1.1 200 OK\r\n"
	    "Content-Type: text/plain\r\n"
	    "Content-Length: 24\r\n"
	    "\r\n"
	    "Hello World From Sever!";

	int serverSock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hint{}, *res;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	int addrInfoStatus = getaddrinfo(NULL, MYPORT, &hint, &res);
	// //std::cout<<"addrInfoStatus :\t"<<addrInfoStatus;
	// //std::cout<<gai_strerror(addrInfoStatus);

	int serverBind = bind(serverSock_fd, res->ai_addr, res->ai_addrlen);
	// //std::cout<<"\nBind ="<<serverBind<<"\n";

	int listenStatus = listen(serverSock_fd, BACKLOG);
	while (true)
	{
		int client_fd = accept(serverSock_fd,
				       (struct sockaddr *)&clientAddr,
				       &clientAddrLen);

		int clientMessageRecv = recv(client_fd, clientDataBuff, sizeof(clientDataBuff), 0);

		clientDataBuff[clientMessageRecv] = '\0';

		std::cout << clientDataBuff << '\n';

		send(client_fd, response, strlen(response), 0);
		std::cout << "Sending HTTP response...\n";

		close(client_fd);

	}
	freeaddrinfo(res);

	return 0;
}
