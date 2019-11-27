/* FILE         : PostalCodeValidator.cpp
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : This file contains the 'main' function. Program execution begins and ends there.
				  Reads parameters from config needed to spin up the server and contact the registry. Created instances
				  of Server class to start the server and begin listen for service requests
*
*/

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

	//Start accepting clients / requests
	server.listenForClients();
	
}
