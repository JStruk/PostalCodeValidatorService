/* FILE         : Logger.h
* PROJECT       : SOA_A1
* PROGRAMMER    : Justin Struk
* FIRST VERSION : 2019-11-28
* DESCRIPTION   : header file for the logger class
*
*/
#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

#include "constants.h"

using namespace std;
using namespace actions;

#pragma warning (disable:4996)

class Logger {

public:

	ofstream logfile;

	void LogMessage(Action action, string msg);
	void logThis(string line);
};