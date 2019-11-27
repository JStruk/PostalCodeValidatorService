
#include "serviceUtils.h"
#include "constants.h"

//return -1 - unable to register team
//return teamID - team registered
string ServiceUtils::registerTeam(string IP, string port) {

	char startOfMsg = '\013\0';
	char endOfMsg = '\034\0';
	char endOfSegment = '\r\0';
	char newLine = '\n';

	string msg("");

	msg += startOfMsg;

	msg += DRC_TAG;
	msg += "|";
	msg += "REG-TEAM";
	msg += "|";
	msg += "|";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	msg += "INF";
	msg += "|";
	msg += "BOSS";
	msg += "|";
	msg += "|";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	msg += endOfMsg;
	msg += newLine;

	//cout << "Registering team with: " << msg << endl << endl;

	//cout << msg << endl;

	Client c = Client();
	c.initClient(IP, port);
	string response = c.sendMsgToRegistry(msg);
	
	string delim = "|";

	auto start = 0U;
	auto end = response.find(delim);
	int count = 0;

	string soa = response.substr(start, end - start);
	
	start = end + delim.length();
	end = response.find(delim, start);
	string ok = response.substr(start, end - start);

	if (ok != SOA_OK) {
		return "Error! Couldn't Register Team";
	}

	start = end + delim.length();
	end = response.find(delim, start);
	string teamID = response.substr(start, end - start);

	return teamID;
}

int ServiceUtils::registerService(string registryIP, string registryport, string serviceIP, string servicePort, string teamName, string teamID) {
	char startOfMsg = '\013\0';
	char endOfMsg = '\034\0';
	char endOfSegment = '\r\0';
	char newLine = '\n';

	//DRC line
	string msg("");

	msg += startOfMsg;

	msg += "DRC|PUB-SERVICE|";
	msg += teamName;
	msg += "|";
	msg += teamID;
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//SRV line
	msg += SRV_TAG;
	msg += "|";
	msg += TAG_NAME;
	msg += "|";
	msg += SERVICE_NAME;
	msg += "|";
	msg += SECURITY_LEVEL;
	msg += "|";
	msg += NUM_ARGS;
	msg += "|";
	msg += NUM_RSP;
	msg += "|";
	msg += DESCRIPTION;
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//ARG1 line - POSTAL_CODE
	msg += ARG_TAG;
	msg += "|";
	msg += "1";
	msg += "|";
	msg += "postalCode";
	msg += "|";
	msg += "string";
	msg += "|";
	msg += "mandatory";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//ARG2 line - REGION
	msg += ARG_TAG;
	msg += "|";
	msg += "2";
	msg += "|";
	msg += "REGION";
	msg += "|";
	msg += "string";
	msg += "|";
	msg += "mandatory";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//RSP1 line - Postal-Code Valid
	msg += RSP_TAG;
	msg += "|";
	msg += "1";
	msg += "|";
	msg += "isPostalCodeValid";
	msg += "|";
	msg += "string";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//RSP2 line - Postal-Code Valid
	msg += RSP_TAG;
	msg += "|";
	msg += "2";
	msg += "|";
	msg += "specialNotes";
	msg += "|";
	msg += "string";
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	//MCH line
	msg += MCH_TAG;
	msg += "|";
	msg += serviceIP;
	msg += "|";
	msg += servicePort;
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	msg += endOfMsg;
	msg += newLine;

	Client c = Client();
	c.initClient(registryIP, registryport);
	string response = c.sendMsgToRegistry(msg);

	string delim = "|";

	auto start = 0U;
	auto end = response.find(delim);
	int count = 0;

	string soa = response.substr(start, end - start);

	start = end + delim.length();
	end = response.find(delim, start);
	string ok = response.substr(start, end - start);

	if (ok != SOA_OK) {

		start = end + delim.length();
		end = response.find(delim, start);
		string errorCode = response.substr(start, end - start);

		//cout << "Error code: " << errorCode << endl;

		return -1;
	}

	return 0;
}