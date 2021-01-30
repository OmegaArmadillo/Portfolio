#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "80"
#define DEFAULT_BUFLEN 512

struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket = INVALID_SOCKET;

int main() 
{
	WSADATA wsaData;
	int iResult;

	int recvbuflen = DEFAULT_BUFLEN;
	const char *sendbuf = "test";
	char recvbuf[DEFAULT_BUFLEN];

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	printf("WSAStartup success\n");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	char address[] = "www.cplusplus.com";
	iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	printf("getaddrinfo success\n");


	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname("www.cplusplus.com");

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) 
	{
		printf("Connection Error\n");
		return 1;
	}

	send(Socket, "GET / HTTP/1.1\r\nHost: www.cplusplus.com\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: www.cplusplus.com\r\nConnection: close\r\n\r\n"), 0);
	char buffer[10000];

		FILE *fileOut;
	fileOut = fopen("out.txt", "w");
	
	
	int nDataLength;
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		// process the information
		fprintf(fileOut, "%s", buffer);
	}
	printf("\nReceive complete\n");

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	getchar();

	return 0;
}
