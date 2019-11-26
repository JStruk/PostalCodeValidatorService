#pragma once

#include <iostream>
#include <string>
#include "client.h"

using namespace std;

class ServiceUtils {
public:
	string registerTeam(string IP, string port);
	int registerService(string IP, string port, string teamName, string teamID);
};

