#ifndef _LOG_OUT_H
#define _LOG_OUT_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;

class LogOut {
public:
	LogOut(string className) {
		this->className = className;
	}

	void info(string msg) {
		time_t t = time(NULL);
		string ts(ctime(&t));
		ts.erase(ts.length()-1, 1);
		cout << "[" << ts <<"][INFO][" << className << "] " << msg << endl;
	}

private:
	string className;
};

#endif