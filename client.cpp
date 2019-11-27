/* FILE         : client.cpp
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : Contains function logic for the client class
*
*/

#include "client.h"

void Client::initClient(string ip, string port) {
	//Initialize logger
	logger = Logger();

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		//return 1;
		//handle error here
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		//return 1;
		//handle error here
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			//return 1;
			//handle error here
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server here!\n");
		WSACleanup();
		
		//return 1;
		//handle error here
	}
}


string Client::sendMsgToRegistry(string msg) {
	string response;

	// Send an initial buffer
	if (msg.size() > DEFAULT_BUFLEN) {
		cout << "Message too long";
		//return 1;
	}
	iResult = send(ConnectSocket, msg.c_str(), (int)strlen(msg.c_str()), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		//return 1;
	}

	//cout << endl << "Sent to registry: " << endl << msg << endl << endl;

	logger.LogMessage(actions::CALLING_REGISTRY, msg);

	// shutdown the connection since no more data will be sent
	/*iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}*/

	// Receive until the peer closes the connection
	do {
		//cout << "Waiting for response from registry..." << endl;
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

		response = string(recvbuf);

		if (iResult > 0) {
			//cout << endl << "Response: " << response << endl << endl;
			logger.LogMessage(actions::REGISTRY_RESPONSE, response);
			break;
		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return response;
}
