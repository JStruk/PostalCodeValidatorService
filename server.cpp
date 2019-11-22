
#include "server.h"

//Some of this code from here -> https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code

void Server::processClientRequest(SOCKET clientsocket) {

	int iResult;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(clientsocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(clientsocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(clientsocket);
				WSACleanup();
				//return 1;
				// ****HANDLE ERROR HERE 
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(clientsocket);
			WSACleanup();
			//return 1;
			// ****HANDLE ERROR HERE 
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(clientsocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(clientsocket);
		WSACleanup();
		//return 1;
		// ****HANDLE ERROR HERE 
	}
}

HostInfo Server::initServer() {
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		//return 1;
		//**HANDLE ERROR HERE
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		//return 1;
		//**HANDLE ERROR HERE
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//return 1;
		//**HANDLE ERROR HERE
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
		//**HANDLE ERROR HERE
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
		//**HANDLE ERROR HERE
	}

	//Infinite loop - accept multiple clients and launch them to a handling thread
	// Accept a client socket

	cout << endl << endl << "Service Info:" << endl;
	info = getIP();
	cout << endl << endl;

	return info;
}


// Got this method from -> https://tangentsoft.net/wskfaq/examples/ipaddr.html
HostInfo Server::getIP() {

	HostInfo info = HostInfo();

	char ac[80];
	if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
		cerr << "Error " << WSAGetLastError() <<
			" when getting local host name." << endl;
		//return 1;
		//***HANDLE ERROR HERE
	}
	cout << "Host name is " << ac << "." << endl;

	struct hostent* phe = gethostbyname(ac);
	if (phe == 0) {
		cerr << "Yow! Bad host lookup." << endl;
		//return 1;
		//***HANDLE ERROR HERE
	}

	for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
		cout << "Address " << i << ": " << inet_ntoa(addr) << endl << "Port is: " << DEFAULT_PORT << endl;
		info = HostInfo(inet_ntoa(addr), 27015);
	}
	return info;
}


void Server::listenForClients() {

	while (true) {
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			//return 1;
			// ****HANDLE ERROR HERE 
		}

		thread clientThread(&Server::processClientRequest, this, ClientSocket);
		clientThread.detach();
	}

	// No longer need server socket
	closesocket(ListenSocket);



	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	//return 0;
}
