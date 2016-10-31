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

#include <opencv2/opencv.hpp>
#include <stdio.h>

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int, char**)
{

    /** Init videocam **/
    Mat frame, dst, small;
    Size size(8,8);
    Size big(320, 320);

    VideoCapture cap;
    cap.open(0);

    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera\n";
        return -1;
    }

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

    //--- GRAB AND WRITE LOOP
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);
        // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

	resize(frame,small,size);//resize image
	cv::cvtColor(small, small, cv::COLOR_BGR2GRAY);
	resize(small,dst, big);//resize image
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", dst);

	for (int r = 0; r < small.rows; r++) {

		for (int c = 0; c < small.cols; c++) {
		    unsigned char intensity = small.at<uchar>(r, c);
		    if (intensity == 0) intensity++;
		    if (intensity == 13) intensity++;
		    intensity = intensity / 16;
		    buf[r * 8 + c] = intensity;
		}
	}
	serialport_write(fd, buf);
	serialport_read_until(fd, buf, eolchar, buf_max, timeout);

        if (waitKey(5) >= 0)
            break;
    }

    serialport_close(fd);

    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}




