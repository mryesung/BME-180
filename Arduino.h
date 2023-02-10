#pragma once

#define DELAYTIME 20

#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <string>

class Arduino
{
public:
	//input variable port number: ex) COM3
	//get 3 as the input and creating the hSerial object will be done automatically in the constructor
	Arduino(const uint32_t PortNumber);
	//common destructor
	//close the hSerial handle i.e. remove the object
	~Arduino();
	//return whether the Arduino is connected to the program or not
	bool IsConnected();
	//read data printed in the arduino serial monitor and return it as a string type
	std::string ReadData();

private:
	//HANDLE is a void pointer type
	HANDLE hSerial;
	bool bConnect;
};