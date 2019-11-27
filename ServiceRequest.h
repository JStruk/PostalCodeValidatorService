#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>

#include "ResponseMessage.h"
#include "client.h"

using namespace std;

class ServiceRequest {

public:
	//first line
	string teamName;
	string teamID;

	//second line
	string serviceName;

	//third line
	string ARG1;
	string arg1Name;
	string arg1DataType;
	string arg1Value;

	//fourth line
	string ARG2;
	string arg2Name;
	string arg2DataType;
	string arg2Value;

	//For parsing purposes - if error occurs when parsing, this flag will go true and a ResponseMessage object built
	bool errorOccured = false;
	ResponseMessage responseMessage;

	ServiceRequest(string _teamname, string _teamid, string serviceName,
		string _arg1, string _arg1name, string _arg1datatype, string _arg1val,
		string _arg2, string _arg2name, string _arg2datatype, string _arg2val);

	ServiceRequest(bool errorOcc, ResponseMessage rMessage) {
		errorOccured = errorOcc;
		responseMessage = rMessage;
	}
	
	void PrintRequest();

	ResponseMessage process();

	void buildReturnMsg();

	int Verify(string registryIP, string registryPort, string teamName, string teamID);

	string BuildVerifyTeamMsg(string ourTeamName, string ourTeamID);
};


/*
DRC|EXEC-SERVICE|<team name>|<teamID>|
	SRV||<service name>||<num args>|||
	ARG|<arg position>|<arg name>|<arg data type>||<arg value>|


*/