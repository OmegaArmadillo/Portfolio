#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_PORT "80"
#define DEFAULT_BUFLEN 512

struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket = INVALID_SOCKET;





void findImages(int bufferLength, char *bufferPointer)
{


	for(int i = 0; i < bufferLength-1; i++)
	{
		if(*(bufferPointer) == '<' && *(bufferPointer + 1) == 'i' && *(bufferPointer + 2) == 'm' && *(bufferPointer + 3) == 'g')
		{

			printf("found an image \n");
			while(*bufferPointer != '>')
			{
				printf("%c", *bufferPointer);
				bufferPointer++;
				i++;
			}
			
			printf(">\n");	
	
		}	
		
		bufferPointer++;
	}


}



void createSocket(char *address, char *socketPointer)
{
	
	strcpy(socketPointer, "GET / HTTP/1.1\r\nHost: ");
	strcat(socketPointer, address);
	strcat(socketPointer, "\r\nConnection: close\r\n\r\n");	
	
	
}



void askForAddress(char *addressPointer)
{
	
	printf("What website do you want to connect to?  ");
    scanf("%s", addressPointer);	
}




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
	char address[50];
	char *addressPointer;
	addressPointer = address;

	askForAddress(addressPointer);
	
			
	iResult = getaddrinfo(address, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	printf("getaddrinfo success\n");


	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct hostent *host;
	host = gethostbyname(address);

	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) 
	{
		printf("Connection Error\n");
		return 1;
	}

	
	char fullSocket[100];
	char *fullSocketPointer;
	fullSocketPointer = fullSocket;
	
	
	createSocket(addressPointer,fullSocketPointer);
	
			
	send(Socket, fullSocket, strlen(fullSocket), 0);
	char buffer[10000];
	

	
	FILE *fileOut;
	fileOut = fopen("out.txt", "w");

	int nDataLength;
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		// process the information
		
		fprintf(fileOut, "%s", buffer);
	}
	printf("\nReceive complete\n");
		
	
	char *bufferPointer;
	bufferPointer = buffer;
		
	
	findImages(10000, bufferPointer);

	
	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	getchar();

	return 0;
}



