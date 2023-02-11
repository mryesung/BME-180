#include "Arduino.h"
#include <iostream>
#include <Windows.h>

Arduino::Arduino(CString PortName)
	:bConnect(false), hSerial(nullptr)
{
	/*
	HANDLE CreateFileA(
		[in]           LPCSTR                lpFileName,
		[in]           DWORD                 dwDesiredAccess,
		[in]           DWORD                 dwShareMode,
		[in, optional] LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		[in]           DWORD                 dwCreationDisposition,
		[in]           DWORD                 dwFlagsAndAttributes,
		[in, optional] HANDLE                hTemplateFile
	);
	lpFileName: name of file or device to be created or opened
	dwDesiredAccess: read, write, both, or 0 to indicate neither
	dwShareMode: requested sharing mode of the file or device, when 0 the file or device
		cannot be opened again until the handle is closed
	lpSecurityAttributes: if this parameter is NULL, the handle returned cannot be inherited
		by any child processes the application may create
	dwCreationDisposition: action to take on a file or device that exists or does not exist
	->Open_Existing: Opens a file or device, only if it exists.
		If the specified file or device does not exist, the function fails and the last-error code is set 
		to ERROR_FILE_NOT_FOUND (2).
	dwFlagsAndAttributes: All other file attributes override FILE_ATTRIBUTE_NORMAL.
	hTemplateFile: Valid handle to a template file with the GENERIC_READ access right.
		when opening an existing file, CreateFile ignores this parameter
	*/
	
	//connect to the port
	this->hSerial = CreateFile(L"//./" + PortName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	//check if connected
	if (INVALID_HANDLE_VALUE == this->hSerial)
		std::cout << "Error occurred during connection.";
	else
	{
		DCB dcbParameter = { 0 };

		if (!GetCommState(this->hSerial, &dcbParameter))
			std::cout << "Error while getting parameters.";
		else
		{
			//set parameter
			dcbParameter.BaudRate = CBR_9600;
			dcbParameter.ByteSize = 8;
			dcbParameter.StopBits = ONESTOPBIT;
			dcbParameter.Parity = NOPARITY;
			dcbParameter.fDtrControl = DTR_CONTROL_ENABLE;
			if (!SetCommState(this->hSerial, &dcbParameter))
			{
				std::cout << "Error while setting parameters.";
			}
			else
			{
				//no error occurred for the overall process
				this->bConnect = true;

				//Clean the buffer
				PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);

				//wait 2s for the arduino to reset
				//reset was occurred by DTR_CONTROL_ENABLE
				Sleep(2000);
			}
		}
	}
	
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
	return this->bConnect;
}

const std::string Arduino::ReadData()
{
	return std::string("");
}
