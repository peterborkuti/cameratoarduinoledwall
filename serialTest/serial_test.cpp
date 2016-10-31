//============================================================================
// Name        : serial_test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Sends different serial messages to Arduino with patterns to
//               check on the 8x8 LED matrix
//============================================================================

#include <iostream>
#include <cstring>
#include <string>
#include "../lib/arduino-serial-lib.h"
#include <unistd.h>

using namespace std;

int main() {
    const int buf_max = 256;

    string str ("/dev/ttyUSB0");
    int fd = -1;
    char * serialport = new char[buf_max];
    int baudrate = 115200;  // default
    char eolchar = '\n';
    int timeout = 5000;

    strcpy(serialport, str.c_str());
    fd = serialport_init(serialport, baudrate);
    if( fd==-1 ) {
    	 cerr << "can not open port:" << "" << endl;
    }
    serialport_flush(fd);
    char * buf = new char[buf_max];
    buf[64] = '\n';
    buf[65] = 0;
    while(true) {
    for (int j = 0; j < 64; j++) {
	for (int i = 0; i < 64; i++) {
	    buf[i] = 1;
	}
	buf[j] = 17;
	serialport_write(fd, buf);
	serialport_read_until(fd, buf, eolchar, buf_max, timeout);
	//serialport_flush(fd);
	std::string s(buf);
	cout << s << endl;
	cout.flush();
    }
    }

    serialport_close(fd);
  return 0;
}
