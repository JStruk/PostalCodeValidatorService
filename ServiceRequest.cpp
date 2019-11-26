
#include "ServiceRequest.h"

using namespace std;

//wombo constructor
ServiceRequest::ServiceRequest(string _teamname, string _teamid, string _serviceName,
	string _arg1, string _arg1name, string _arg1datatype, string _arg1val,
	string _arg2, string _arg2name, string _arg2datatype, string _arg2val) {

	//first line
	teamName = _teamname;
	teamID = _teamid;

	//second line
	serviceName = _serviceName;

	//third line
	ARG1 = _arg1;
	arg1Name = _arg1name;
	arg1DataType = _arg1datatype;
	arg1Value = _arg1val;

	//fourth line
	ARG2 = _arg2;
	arg2Name = _arg2name;
	arg2DataType = _arg2datatype;
	arg2Value = _arg2val;

	errorOccured = false;
}

void ServiceRequest::PrintRequest() {
	cout << "Team Name: " << teamName << endl;
	cout << "Team ID: " << teamID << endl;
	cout << "ARG1: " << ARG1 << endl;
	cout << "Name: " << arg1Name << endl;
	cout << "Type: " << arg1DataType << endl;
	cout << "Value: " << arg1Value << endl;
	cout << "ARG2: " << ARG2 << endl;
	cout << "Name: " << arg2Name << endl;
	cout << "Type: " << arg2DataType << endl;
	cout << "Value: " << arg2Value << endl;


}

ResponseMessage ServiceRequest::process() {
	//cout << "Processing Postal Code: " + arg1Value << " in region: " << arg2Value << endl;
	string postalCode = arg1Value;
	string regionCode = arg2Value;

	bool valid = false;
	string specialNotes;

	ResponseMessage r;

	//Postal Codes cannot contain the following letters: D, F, I, O, Q, U
	if (postalCode.find("D") != std::string::npos || postalCode.find("F") != std::string::npos || postalCode.find("I") != std::string::npos
		|| postalCode.find("O") != std::string::npos || postalCode.find("Q") != std::string::npos || postalCode.find("U") != std::string::npos) {

		r = ResponseMessage(false, "Postal Code cannot contain D, F, I, O, Q or U");
		return r;
	}

	if (regionCode == "NL") {
		string beginsWith[] = { "A0", "A1", "A2", "A5", "A8" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "A3", "A4", "A6", "A7", "A9" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna Be Newfoundland");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "A0") {
				r = ResponseMessage(true, "Rural Newfoundland");
				return r;
			}
			r = ResponseMessage(true, "Valid Newfoundland postal code");
			return r;
		}

	}
	else if (regionCode == "NS") {
		string beginsWith[] = { "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "B7", "B8" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna Be Nova Scotia");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "B0") {
				r = ResponseMessage(true, "Rural Nova Scotia");
				return r;
			}
			r = ResponseMessage(true, "Valid Nova Scotia postal code");
			return r;
		}
	}
	else if (regionCode == "NB") {
		string beginsWith[] = { "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			if (postalCode.substr(0, 2) == "E0") {
				r = ResponseMessage(true, "Wanna Be Rural New Brunswick");
				return r;
			}
			r = ResponseMessage(false, "Invalid Postal Code");
			return r;
		}
		else {
			r = ResponseMessage(true, "Valid New Brunswick postal code");
			return r;
		}
	}
	else if (regionCode == "PE") {
		string beginsWith[] = { "C0", "C1" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna Be PEI");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "C0") {
				r = ResponseMessage(true, "Rural PEI");
				return r;
			}
			r = ResponseMessage(true, "Valid PEI postal code");
			return r;
		}

	}
	else if (regionCode == "QC") {
		string beginsWith[] = { "G0", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9",
		"H0", "H1", "H2", "H3", "H4", "H5", "H7", "H8", "H9" ,
		"J0", "J1", "J2", "J3", "J4", "J5", "J6", "J7", "J8", "J9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "H6" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(true, "Wanna be Quebec");
			return r;
		}
		else {
			if (postalCode == "H0H0H0") {
				r = ResponseMessage(true, "Hi Santa Claus");
				return r;
			}
			else if (postalCode.substr(0, 2) == "G0" || postalCode.substr(0, 2) == "H0" || postalCode.substr(0, 2) == "J0") {
				r = ResponseMessage(true, "Rural Quebec");
				return r;
			}
			else if (postalCode.substr(0, 3) == "G1A") {
				r = ResponseMessage(true, "Provincial Government");
				return r;
			}

			else if (postalCode.substr(0, 1) == "G") {
				r = ResponseMessage(true, "Eastern Quebec");
				return r;
			}
			else if (postalCode.substr(0, 1) == "H") {
				r = ResponseMessage(true, "Montreal Area");
				return r;
			}
			else if (postalCode.substr(0, 1) == "J") {
				r = ResponseMessage(true, "Western / Northern Quebec");
				return r;
			}
			r = ResponseMessage(true, "Valid Quebec Postal Code");
			return r;
		}
	}
	else if (regionCode == "ON") {
		string beginsWith[] = { "K0", "K1", "K2", "K4", "K6", "K7", "K8", "K9",
		"L0", "L1", "L2", "L3", "L4", "L5", "L6", "L7", "L8", "L9" ,
		"M1", "M2", "M3", "M5", "M6", "M7", "M8", "M9",
		"N0", "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8", "N9",
		"P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "K3", "K5", "M0", "M4", "M6" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(true, "Wanna be Ontario");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "K0" || postalCode.substr(0, 2) == "L0" || postalCode.substr(0, 2) == "N0" || postalCode.substr(0, 2) == "P0") {
				r = ResponseMessage(true, "Rural Ontario");
				return r;
			}
			else if (postalCode.substr(0, 3) == "K1A") {
				r = ResponseMessage(true, "Government of Canada");
				return r;
			}
			else if (postalCode.substr(0, 3) == "M7A") {
				r = ResponseMessage(true, "Queen's Park");
				return r;
			}
			else if (postalCode == "K") {
				r = ResponseMessage(true, "Eastern Ontario");
				return r;
			}
			else if (postalCode.substr(0, 1) == "L") {
				r = ResponseMessage(true, "Central Ontario");
				return r;
			}
			else if (postalCode.substr(0, 1) == "M") {
				r = ResponseMessage(true, "Toronto Area");
				return r;
			}
			else if (postalCode.substr(0, 1) == "N") {
				r = ResponseMessage(true, "Western Ontario");
				return r;
			}
			else if (postalCode.substr(0, 1) == "P") {
				r = ResponseMessage(true, "Northern Ontario");
				return r;
			}
			r = ResponseMessage(true, "Valid Ontario Postal Code");
			return r;
		}
	}
	else if (regionCode == "MB") {
		string beginsWith[] = { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			r = ResponseMessage(false, "Invalid Postal Code");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "R2" || postalCode.substr(0, 2) == "R3") {
				r = ResponseMessage(true, "Winnipeg Area");
				return r;
			}
			else if (postalCode.substr(0, 2) == "R0") {
				r = ResponseMessage(true, "Rural Manitoba");
				return r;
			}
			r = ResponseMessage(true, "Valid Manitoba postal code");
			return r;
		}
	}
	else if (regionCode == "SK") {
		string beginsWith[] = { "S0", "S2", "S3", "S4", "S6", "S7", "S9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "S1", "S5", "S8" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna be Saskatchewan");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "S0") {
				r = ResponseMessage(true, "Rural Saskatchewan");
				return r;
			}
			else if (postalCode.substr(0, 2) == "S7") {
				r = ResponseMessage(true, "Saskatoon Area");
				return r;
			}
			r = ResponseMessage(true, "Valid Saskatchewan postal code");
			return r;
		}
	}
	else if (regionCode == "AB") {
		string beginsWith[] = { "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7", "T8", "T9" };
		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			r = ResponseMessage(false, "Invalid Postal Code");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "T0") {
				r = ResponseMessage(true, "Rural Alberta");
				return r;
			}
			else if (postalCode.substr(0, 2) == "T5" || postalCode.substr(0, 2) == "T6") {
				r = ResponseMessage(true, "Edmonton Area");
				return r;
			}
			else if (postalCode.substr(0, 2) == "T2" || postalCode.substr(0, 2) == "T3") {
				r = ResponseMessage(true, "Calgary Area");
				return r;
			}
			r = ResponseMessage(true, "Valid Alberta postal code");
			return r;
		}
	}
	else if (regionCode == "BC") {
		string beginsWith[] = { "V0", "V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 2));

		if (found == end(beginsWith))
		{
			r = ResponseMessage(false, "Invalid Postal Code");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "T0") {
				r = ResponseMessage(true, "Rural British Columbia");
				return r;
			}
		}
	}
	else if (regionCode == "YT") {
		string beginsWith[] = { "Y0A", "Y0B", "Y1A" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 3));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "Y2", "Y3", "Y4", "Y5", "Y6", "Y7", "Y8", "Y9" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna be Yukon");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "Y0") {
				r = ResponseMessage(true, "Remote Yukon Areas");
				return r;
			}
			else if (postalCode.substr(0, 3) == "Y1A") {
				r = ResponseMessage(true, "Whitehorse");
				return r;
			}
			r = ResponseMessage(true, "Valid Yukon postal code");
			return r;
		}
	}
	else if (regionCode == "NT") {
		string beginsWith[] = { "X0E", "X0F", "X1A" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 3));

		if (found == end(beginsWith))
		{
			string wannabe[] = { "X2", "X3", "X4", "X5", "X6", "X7", "X8", "X9" };
			string* found2 = find(wannabe, end(wannabe), postalCode.substr(0, 2));
			if (found2 == end(wannabe)) {
				r = ResponseMessage(false, "Postal Code doesn't start with required values for given region");
				return r;
			}
			r = ResponseMessage(false, "Wanna be NWT");
			return r;
		}
		else {
			if (postalCode.substr(0, 2) == "X0") {
				r = ResponseMessage(true, "Remote NWT Areas");
				return r;
			}
			else if (postalCode.substr(0, 3) == "X1A") {
				r = ResponseMessage(true, "Yellowknife");
				return r;
			}
			r = ResponseMessage(true, "Valid NWT postal code");
			return r;
		}
	}
	else if (regionCode == "NU") {
		string beginsWith[] = { "X0A", "X0B", "X0C" };

		string* found = find(beginsWith, end(beginsWith), postalCode.substr(0, 3));

		if (found == end(beginsWith))
		{
			r = ResponseMessage(false, "Invalid Nunavut Postal Code");
			return r;
		}
		else {
			r = ResponseMessage(true, "Everything is remote in Nunavut");
			return r;
		}
	}
	return r;
}


void ServiceRequest::buildReturnMsg() {

}

int ServiceRequest::Verify(string rIP, string rPort, string ourTeamName, string ourTeamID) {
	// 0. Valid
	// 1. Invalid team
	// 2. invalid data type
	// 3. invalid arg position
	// 4. invalid argument

	//Verify team
	Client c = Client();
	c.initClient(rIP, rPort);
	string response = c.sendMsgToRegistry(BuildVerifyTeamMsg(ourTeamName, ourTeamID));

	string delim = "|";

	auto start = 0U;
	auto end = response.find(delim);
	int count = 0;

	string soa = response.substr(start, end - start);

	start = end + delim.length();
	end = response.find(delim, start);
	string ok = response.substr(start, end - start);

	if (ok != SOA_OK) {
		return 1;
	}


	//Verify data types - make sure arg1Datatype and arg2Datatype are both strings

	//arg1 needs to be a string and in the form "ANANAN"
	//Region must be: NL, NS, NB, PE, QC, ON, MB, SK, AB, BC, YT, NT, NU

	if (arg1DataType != "string") {
		return 2;
	}

	//Verify postal code with regex
	int pcode_valid = 1;

	//regex for postal code
	regex b(R"([A-Za-z]\d[A-Za-z]\d[A-Za-z]\d)");

	if (!std::regex_match(arg1Value, b)) {
		//cout << "Invalid Postal Code" << endl;
		return 4;
	}

	//cout << endl << "Verifying Arg2 Datatype: \n " << "Expected: string\n" << "Actual: " << arg2DataType << endl;

	if (arg2DataType != "string") {
		return 2;
	}

	//Verify region code is one of the allowable values
	string regionCodes[] = { "NL", "NS", "NB", "PE", "QC", "ON", "MB", "SK", "AB", "BC", "YT", "NT", "NU" };
	string* found = std::find(regionCodes, std::end(regionCodes), arg2Value);
	if (found == std::end(regionCodes))
	{
		return 4;
	}

	return 0;

}

string ServiceRequest::BuildVerifyTeamMsg(string ourTeamName, string ourTeamID) {

	char startOfMsg = '\013\0';
	char endOfMsg = '\034\0';
	char endOfSegment = '\r\0';
	char newLine = '\n';

	string msg = "";

	msg += startOfMsg;

	msg += DRC_TAG;
	msg += "|";
	msg += QUERY_TEAM_TAG;
	msg += "|";
	msg += ourTeamName;
	msg += "|";
	msg += ourTeamID;
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	msg += INF_TAG;
	msg += "|";
	msg += teamName;
	msg += "|";
	msg += teamID;
	msg += "|";
	msg += serviceName;
	msg += "|";
	msg += endOfSegment;
	msg += newLine;

	msg += endOfMsg;
	msg += newLine;

	return msg;

}
