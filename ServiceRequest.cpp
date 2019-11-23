
#include "ServiceRequest.h"
using namespace std;

//wombo constructor
ServiceRequest::ServiceRequest(string _teamname, string _teamid, 
	string _arg1, string _arg1name, string _arg1datatype, string _arg1val,
	string _arg2, string _arg2name, string _arg2datatype, string _arg2val) {

	//first line
	teamName = _teamname;
	teamID = _teamid;

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

void ServiceRequest::process() {
	cout << "Processing Postal Code: " + arg1Value << " in region: " << arg2Value << endl;
}

void ServiceRequest::buildReturnMsg() {

}

void ServiceRequest::verifyTeam() {

}
