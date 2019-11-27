// PostalCodeValidator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include "stdafx.h"
#include "serviceUtils.h"
#include "server.h"
#include "IniFile.h"
#include "Logger.h"
#include "constants.h"

using namespace std;
using namespace actions;

#pragma warning (disable:4996)

int main()
{
	Logger logger = Logger();

	logger.LogMessage(actions::STARTING_SERVICE, "");

	string FileName = "config.ini";
	string	serviceIP;
	string	servicePort;
	string registryIP;
	string registryPort;
	HostInfo hostInfo;

	string teamName = "BOSS";

	//Parse config file 
	registryIP = CIniFile::GetValue("registryIP", "RegistryInfo", FileName);
	registryPort = CIniFile::GetValue("registryPort", "RegistryInfo", FileName);

	//stringstream port(_port);
	//port >> registryPort;

	//cout << endl << "Registry IP: " << registryIP << endl << "Registry Port: " << registryPort << endl;
	
	
	ServiceUtils s = ServiceUtils();

	//Register the team with the registry
	string teamID = s.registerTeam(registryIP, registryPort);
	//cout << "Team ID: " << teamID << endl;

	//Setup the server to listen for connections to the service
	Server server = Server();

	hostInfo = server.initServer(teamName, teamID);
	server.setRegistryInfo(registryIP, registryPort);

	//Register the service with the registry
	int didItRegister = s.registerService(registryIP, registryPort, hostInfo.IP, hostInfo.port, teamName, teamID);
	/*if (didItRegister == 0) {
		cout << "Service successfully registered. Will now listen for client connections..." << endl << endl;
	}*/

	

	//Start accepting clients / requests
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
