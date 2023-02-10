#include "Arduino.h"
#include <atlstr.h>

Arduino::Arduino(const uint32_t PortNumber)
	:bConnect(false), hSerial(nullptr)
{
	/*this->hSerial = CreateFile("\\\\.\\COM" + CString(PortNumber),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);*/

	
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

std::string Arduino::ReadData()
{
	return std::string("");
}
