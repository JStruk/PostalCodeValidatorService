
#include "server.h"

//Some of this code from here -> https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code

void Server::processClientRequest(SOCKET clientsocket) {

	int iResult;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	memset(recvbuf, '\0', DEFAULT_BUFLEN);
	int recvbuflen = DEFAULT_BUFLEN;

	string msgParser[23];
	//string msg;

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(clientsocket, recvbuf, recvbuflen, 0);
		string msg(recvbuf);
		if (iResult > 0) {
			//Received message from the client
			//1. Parse message (HL7) and store in variables? class?
			//2. If valid execute service message, verify team
			//3. Process request
			//4. Construct response
			//cout << "Received: " << msg << endl;

			string s = string(msg);
			//remove any spaces from the message before parsing
			s.erase(remove(s.begin(), s.end(), ' '), s.end());

			string delim = "|";

			auto start = 0U;
			auto end = s.find(delim);
			int count = 0;

			string drc = s.substr(start, end - start);

			if (drc != "DRC") {
				//Invalid message
				cout << "Invalid Request";
				break;
			}

			start = end + delim.length();
			end = s.find(delim, start);
			string exec = s.substr(start, end - start);

			if (exec != "EXEC-SERVICE") {
				cout << "Invalid Request";
				break;
			}

			start = end + delim.length();
			end = s.find(delim, start);
			string teamName = s.substr(start, end - start);
			
			start = end + delim.length();
			end = s.find(delim, start);
			string teamID = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string srv = s.substr(start, end - start);
			
			if (srv != "SRV") {
				cout << "invalid Request";
				break;
			}

			start = end + delim.length();
			end = s.find(delim, start);
			string ph = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string serviceName = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string ph2 = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string numArgs = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string ph3 = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string ph4 = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg = s.substr(start, end - start);

			if (arg != "ARG") {
				cout << "Invalid Request" << endl;
				break;
			}

			start = end + delim.length();
			end = s.find(delim, start);
			string arg1pos = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg1name = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg1Datatype = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string ph5 = s.substr(start, end - start);
			
			start = end + delim.length();
			end = s.find(delim, start);
			string arg1Val = s.substr(start, end - start);

			//
			start = end + delim.length();
			end = s.find(delim, start);
			string arg2 = s.substr(start, end - start);

			if (arg2 != "ARG") {
				cout << "Invalid Request" << endl;
				break;
			}

			start = end + delim.length();
			end = s.find(delim, start);
			string arg2pos = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg2name = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg2Datatype = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string ph6 = s.substr(start, end - start);

			start = end + delim.length();
			end = s.find(delim, start);
			string arg2Val = s.substr(start, end - start);

			ServiceRequest serviceRequest = ServiceRequest(teamName, teamID, arg, arg1name, arg1Datatype, arg1Val,
				arg2, arg2name, arg2Datatype, arg2Val);

			//serviceRequest.PrintRequest();

			//2. Verify Team
			serviceRequest.verifyTeam();

			serviceRequest.process();
			//cout << s.substr(start, end);
			//cout << count << endl;

			// Response Message to sender
			/*
			Pass:
			PUB|OK|||<num segments>|
			RSP|<resp position>|<resp name>|<resp data type>|<resp value>|

			Fail:
			PUB|NOT-OK|errorCode|errorMessage||
			*/
			/*iSendResult = send(clientsocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(clientsocket);
				WSACleanup();
				//return 1;
				// ****HANDLE ERROR HERE
			}
			printf("Response Sent: %s\n", recvbuf);*/
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

void test() {

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
