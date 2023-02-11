#pragma once

#define DELAYTIME 20

#include <string>
#include <atlstr.h>

class Arduino
{
public:
	//connect to the port and print error messages
	Arduino(CString PortName);
	//common destructor
	//close the hSerial handle i.e. remove the object
	~Arduino();
	//return whether the Arduino is connected to the program or not
	bool IsConnected();
	//read data printed in the arduino serial monitor and return it as a string type
	const std::string ReadData();

private:
	//HANDLE is a void pointer type
	HANDLE hSerial;
	bool bConnect;
};