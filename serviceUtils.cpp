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
		string msg = "DRC|PUB-SERVICE|BOSS|1186|";

		msg += "\n";
		msg = msg + SRV_TAG;
		msg = msg + "|";

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