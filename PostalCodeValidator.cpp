// PostalCodeValidator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "serviceUtils.h"
#include "server.h"

using namespace std;

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma warning (disable:4996)

int main()
{
	
	string	registryIP;
	int		registryPort;
	HostInfo hostInfo;

    cout << "Please enter the Registry IP: \n";

	getline(cin, registryIP);

	cout << "Please enter the Registry Port: \n";

	cin >> registryPort;

	cout << endl << "Registry IP: " << registryIP << endl << "Registry Port: " << registryPort << endl;
	
	Server server = Server();

	hostInfo = server.initServer();

	ServiceUtils s = ServiceUtils();

	s.registerService(hostInfo.IP, hostInfo.port);

	server.listenForClients();
	
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
