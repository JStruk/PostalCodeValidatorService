/* FILE         : server.h
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : Header file for the server class
*
*/
//Some of this code from here -> https://docs.microsoft.com/en-us/windows/win32/winsock/complete-server-code


#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread> 
#include <iostream>
#include <algorithm>
#include <string>

#include "ServiceRequest.h"
#include "hostInfo.h"
#include "ResponseMessage.h"
#include "ServiceRequest.h"
#include "Logger.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma warning (disable:4996)
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;

class Server {

public:

	/*
	Data Members
	*/
	HostInfo info;
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	string registryIP;
	string registryPort;
	string ourTeamName;
	string ourTeamID;

	Logger logger;
	
	/*
	Methods
	*/
	HostInfo initServer(string _ourTeamName, string _ourTeamID);
	void setRegistryInfo(string registryIP, string registryPort);
	HostInfo getIP();
	void listenForClients();
	void processClientRequest(SOCKET clientsocket);
	ServiceRequest parseRequest(string msg);

};