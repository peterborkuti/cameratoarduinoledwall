//============================================================================
// Name        : todd_serial_02.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstring>
#include <string>
#include "../lib/arduino-serial-lib.h"

using namespace std;

int main() {
    const int buf_max = 256;

    string str ("/dev/ttyUSB0");
    int fd = -1;
    char * serialport = new char[buf_max];
    int baudrate = 9600;  // default
    char eolchar = '\n';
    int timeout = 5000;

    strcpy(serialport, str.c_str());
    fd = serialport_init(serialport, baudrate);
    if( fd==-1 ) {
    	 cerr << "can not open port:" << "" << endl;
    }
    serialport_flush(fd);
    char * buf = new char[buf_max];  //
    while(1) {
		serialport_read_until(fd, buf, eolchar, buf_max, timeout);
		std::string s(buf);
		cout << s;
		cout.flush();
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
