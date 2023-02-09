#include "Arduino.h"

Arduino::Arduino(const uint32_t PortNumber)
	:bConnect(false), delayTime(20)
{
	//this->hSerial = CreateFileA()
}

Arduino::~Arduino()
{
	//only disconnect when connected
	if (true == this->bConnect)
	{
		this->bConnect = false;
		CloseHandle(this->hSerial);
	}
}

bool Arduino::IsConnected()
{
	return bConnect;
}

void Arduino::Delay()
{
	Sleep(delayTime);
	return;
}

std::string Arduino::ReadData()
{
	return std::string("");
}
