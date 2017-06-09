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
#include "../lib/cam-serial-lib.h"
#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <stdio.h>

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {

	CamSerial camSerial;

	/** Init videocam **/
	Mat frame;

	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	//--- GRAB AND WRITE LOOP
	for (;;) {
		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;

		camSerial.sendImage(frame);

	}

	// the camera will be deinitialized automatically in VideoCapture destructor

	camSerial.off();
	return 0;
}

