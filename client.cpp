#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> // for write()
#include <cstring>

#define MYPORT "8080"

int main()
{
	char msg[] = "Hello world from client side!!!!";
	int len, bytes_sent;
	len = strlen(msg);

	int clientSock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hint{}, *res;
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = AI_PASSIVE;

	int addrInfoStatus = getaddrinfo("127.0.0.1", MYPORT, &hint, &res);
	int connectStatus = connect(clientSock_fd, res->ai_addr, res->ai_addrlen);

	int sentStatus =  send(clientSock_fd, msg, len, 0);

	

	return 0;
}
//perror("listen Status ");