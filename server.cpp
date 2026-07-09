#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cerrno>
#include <unistd.h>
#include <netdb.h>

#define MYPORT "8080"
#define BACKLOG 5 // //BACKLOG is the number of connections allowed on the incoming queue.

int main()
{

	struct sockaddr_storage clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	char clientDataBuff[1024];

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
	// perror("bind");

	int listenStatus = listen(serverSock_fd, BACKLOG);
	// perror("listen Status ");

	// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	int client_fd = accept(serverSock_fd,
			       (struct sockaddr *)&clientAddr,
			       &clientAddrLen);

	// int recv(int sockfd, void *buf, int len, int flags);

	int clientMessageRecv = recv(client_fd, clientDataBuff, sizeof(clientDataBuff), 0);
perror("listen Status ");
clientDataBuff[clientMessageRecv] = '\0';

std::cout << clientDataBuff << '\n';

	freeaddrinfo(res);
	return 0;
}
