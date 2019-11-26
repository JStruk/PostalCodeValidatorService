#pragma once

#include <stdio.h>

#define TAG_NAME "POSTAL"
#define SECURITY_LEVEL "2"
#define SECURITY_LVL_STRING "3"
#define SERVICE_NAME "PostalCodeValidator"
#define DRC_TAG "DRC"
#define INF_TAG "INF"
#define SRV_TAG "SRV"
#define ARG_TAG "ARG"
#define RSP_TAG "RSP"
#define MCH_TAG "MCH"
#define PUB_TAG "PUB"
#define QUERY_TEAM_TAG "QUERY-TEAM"
#define SOA_OK "OK"
#define SOA_NOT_OK "NOT-OK"
#define PUBLISH_SERVICE_TAG "PUB-SERVICE"
#define NUM_ARGS "2"
#define NUM_RSP "2"
#define DESCRIPTION "Given a postal code and region, determins if the postal code is valid"
#define RSP_NAME "totalPayValue"
#define SERVICE_IP "<ServiceIP>"
#define SERVICE_PORT "<ServicePort>"

#define VALID_POSTAL_CODE "VALID"
#define INVALID_POSTAL_CODE "NOT-VALID"

namespace actions {
	enum Action {
		STARTING_SERVICE,
		CALLING_REGISTRY,
		REGISTRY_RESPONSE,
		RECEIVING_REQUEST,
		RESPONDING_REQUEST
	};
}
