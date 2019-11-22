/*
DRC|PUB-SERVICE|BOSS|1186|
SRV|PAYROLL|PAYSTUBMAKER|3|5|1|Returns the pay for an employee on their pay stub|
ARG|1|employeeType|string|mandatory|
ARG|2|totalHoursWorked|double|mandatory|
ARG|3|RateOfPay|double|mandatory|
ARG|4|piecesMade|int|optional|
ARG|5|numWeeks|int|optional|
RSP|1|totalPayValue|float|
MCH|<ServiceIP>|<ServicePort>|
*/

#include "serviceUtils.h"
#include "constants.h"


	void ServiceUtils::registerService(string IP, int port) {
		//DRC line
		string msg = "DRC|PUB-SERVICE|BOSS|1186|";

		//SRV line
		msg += "\n";
		msg += SRV_TAG;
		msg +="|";
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
		msg += "|\n";

		//ARG1 line - POSTAL_CODE
		msg += ARG_TAG;
		msg += "|";
		msg += "1";
		msg += "|";
		msg += "POSTAL_CODE";
		msg += "|";
		msg += "string";
		msg += "|";
		msg += "mandatory";
		msg += "|\n";

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
		msg += "|\n";

		//RSP1 line - Postal-Code Valid
		msg += RSP_TAG;
		msg += "|";
		msg += "1";
		msg += "|";
		msg += "POSTAL_CODE_VALID";
		msg += "|";
		msg += "string";
		msg += "|\n";

		//RSP2 line - Postal-Code Valid
		msg += RSP_TAG;
		msg += "|";
		msg += "2";
		msg += "|";
		msg += "SPECIAL_NOTES";
		msg += "|";
		msg += "string";
		msg += "|\n";

		//MCH line
		msg += MCH_TAG;
		msg += "|";
		msg += IP;
		msg += "|";
		msg += to_string(port);
		msg += "|\n";

		cout << "\n" << msg;
		
	}

/*
DRC|PUB-SERVICE|BOSS|1186|
SRV|POSTAL|POSTAL_CODE_VALIDATOR|2|2|2|Validates a postal code based on their region|
ARG|1|POSTAL_CODE|string|mandatory|
ARG|2|REGION_CODE|string|mandatory|
RSP|1|IS_PCODE_VALID|string|
RSP|1|POSTAL-CODE_VALID|string|
RSP|2|SPECIAL-NOTES|string|
MCH|<ServiceIP>|<ServicePort>|*/