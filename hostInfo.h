
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "constants.h"

using namespace std;

class HostInfo {
	
	
public:
	string IP;
	int port;

	HostInfo(string _IP, int _port) {
		IP = _IP;
		port = _port;
	}

	HostInfo() {
		IP = "127.0.0.1";
		port = 27015;
	}
};