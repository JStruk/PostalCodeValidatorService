/* FILE         : ServiceUtils.h
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : header file for the service utils class
*
*/
#pragma once

#include <iostream>
#include <string>
#include "client.h"

using namespace std;

class ServiceUtils {
public:
	string registerTeam(string IP, string port);
	int registerService(string IP, string port, string serviceIP, string servicePort, string teamName, string teamID);
};

