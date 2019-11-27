/* FILE         : client.h
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : Header file for the client class. Contains class definition, dependencies and constants
*
*/

/*  NAME    : Client
*   PURPOSE : A TCP/IP client that may be used to connect to a server (registry), send a message, and get a response.
				This client is intended for a single use. I.e. init the client and call SendMessagetoRegistry one time only
*/

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

#include "Logger.h"

using namespace std;
using namespace actions;

class Client {

public:

	string serverName;
	string port;
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	const char* sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	Logger logger;

	void initClient(string ip, string port);
	string sendMsgToRegistry(string msg);
};

