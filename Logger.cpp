
#include "logger.h"

void Logger::LogMessage(Action action, string msg) {
	
	switch (action) {

		case actions::STARTING_SERVICE: {
			logThis("============================================================");
			logThis("Team	: BOSS (Justin S, Nate D, Spencer B, Harley B)");
			string tmp = "Tag-Name	: ";
			tmp += TAG_NAME;
			logThis(tmp);
			string tmp2 = "Service	: ";
			tmp2 += SERVICE_NAME;
			logThis(tmp2);
			logThis("============================================================");
			logThis("---");
			break;
		}
		case actions::CALLING_REGISTRY: {
			logThis("Calling SOA-Registry with message : ");

			istringstream f(msg);
			string line;
			while (getline(f, line)) {
				string tmp = "\t >> ";
				tmp += line;
				logThis(tmp);
			}

			break;
		}

		case actions::REGISTRY_RESPONSE: {
			logThis("\t >> Response from SOA-Registry : ");

			istringstream f(msg);
			string line;
			while (getline(f, line)) {
				string tmp = "\t\t >> ";
				tmp += line;
				logThis(tmp);
			}

			logThis("---");
			break;
		}


		case actions::RECEIVING_REQUEST: {
			logThis("Receiving service request : ");

			istringstream f(msg);
			string line;
			while (getline(f, line)) {
				string tmp = "\t >> ";
				tmp += line;
				logThis(tmp);
			}

			logThis("---");

			break;
		}



		case actions::RESPONDING_REQUEST: {
			logThis("Responding to service request : ");

			istringstream f(msg);
			string line;
			while (getline(f, line)) {
				string tmp = "\t >> ";
				tmp += line;
				logThis(tmp);
			}

			logThis("---");

			break;
		}
	};

	
}

void Logger::logThis(string line) {
	//get timestamp
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	string timestamp(buffer);

	//ofstream logfile("logs/postalServiceLogs.log");

	//open logfile
	logfile.open("logs/postalServiceLogs.log", ios::out | ios::app);

	if (!logfile) {
		cout << "couldn't open the logfile " << endl;
	}
	
	//Always write timestamp at the start of each line
	logfile << timestamp << " ";
	//cout << timestamp << " ";

	//write the current line
	line.erase(remove(line.begin(), line.end(), '\n'), line.end());
	line.erase(remove(line.begin(), line.end(), '\r'), line.end());
	logfile << line << endl;
	
	//cout << line << endl;

	//close logfile
	logfile.flush();
	logfile.close();
}