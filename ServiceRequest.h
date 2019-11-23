#pragma once

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class ServiceRequest {

public:
	//first line
	string teamName;
	string teamID;

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

	ServiceRequest(string _teamname, string _teamid,
		string _arg1, string _arg1name, string _arg1datatype, string _arg1val,
		string _arg2, string _arg2name, string _arg2datatype, string _arg2val);
	
	void PrintRequest();

	void process();

	void buildReturnMsg();

	void verifyTeam();
};


/*
DRC|EXEC-SERVICE|<team name>|<teamID>|
	SRV||<service name>||<num args>|||
	ARG|<arg position>|<arg name>|<arg data type>||<arg value>|


*/