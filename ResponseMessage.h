#pragma once
#include <string>
#include "constants.h"

using namespace std;

class ResponseMessage {

public:

	bool hasBeenSetup = false;

	string message;
	bool valid;
	bool isPostalCodeValidForRules;
	string specialNotes;

	string errorCode;
	string errorMessage;

	ResponseMessage() {
		hasBeenSetup = false;
	}

	ResponseMessage(bool _isPCodeValid, string _specialNotes) {
		hasBeenSetup = true;
		valid = true;

		isPostalCodeValidForRules = _isPCodeValid;
		specialNotes = _specialNotes;
	}

	ResponseMessage(bool _valid, string _errorCode, string _errorMessage) {
		hasBeenSetup = true;

		valid = _valid;
		errorCode = _errorCode;
		errorMessage = _errorMessage;
	}

	//Function definition is here because when I had it in ResponseMessage.cpp I kept getting linker error LNK2019 - Unresolved external symbol?
	//Only if return type was string ^, if return type was void this definition could be in the .cpp file with no errors

	string constructResponseMessage() {
		string msg = "";

		msg += PUB_TAG;
		msg += "|";

		if (valid) {
			msg += SOA_OK;
			msg += "|";
			msg += "|";
			msg += "|";
			msg += "2"; //number of segments to follow - 2 responses
			msg += "|\n";
		}
		else {
			msg += SOA_NOT_OK;
			msg += "|";
			msg += errorCode;
			msg += "|";
			msg += errorMessage;
			msg += "|";
			msg += "|\n";

			//done building NOT-OK message
			return msg;
		}


		//Keep going since request was valid and processed - build response lines
		msg += RSP_TAG;
		msg += "|";
		msg += "1";
		msg += "|";
		msg += "Postal-Code-Valid";
		msg += "|";
		msg += "string";
		msg += "|";

		if (isPostalCodeValidForRules) {
			msg += VALID_POSTAL_CODE;
			msg += "|\n";
		}
		else {
			msg += INVALID_POSTAL_CODE;
			msg += "|\n";
		}

		msg += RSP_TAG;
		msg += "2";
		msg += "|";
		msg += "Special-Notes";
		msg += "|";
		msg += "string";
		msg += "|";
		msg += specialNotes;
		msg += "|\n";

		return msg;
	}
};