cmake_minimum_required(VERSION 2.8)
project( ToddSerial )
find_package( OpenCV REQUIRED )
add_executable( ToddSerial ../lib/arduino-serial-lib.c todd_serial_02.cpp )
target_link_libraries( ToddSerial ${OpenCV_LIBS} )
