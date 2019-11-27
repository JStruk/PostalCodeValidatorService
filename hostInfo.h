/* FILE         : hostInfo.h
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : header file for the HostInfo class.
*
*/

/*  NAME    : HostInfo
*   PURPOSE : Contains information about the host server for this service (IP and PORT)
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "constants.h"

using namespace std;

class HostInfo {
	
	
public:
	string IP;
	string port;

	HostInfo(string _IP, string _port) {
		IP = _IP;
		port = _port;
	}

	HostInfo() {
		IP = "127.0.0.1";
		port = "27015";
	}
};