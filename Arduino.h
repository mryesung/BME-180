#pragma once
#include <Windows.h>
#include <iostream>
#include <stdlib.h>

class Arduino
{
public:
	Arduino(const uint32_t PortNumber);
	~Arduino();
	bool IsConnected();
	//delay to match the sampling frequency with arduino
	void Delay();
	std::string ReadData();

private:
	HANDLE hSerial;
	bool bConnect;
	const uint32_t delayTime; //unit : ms
};