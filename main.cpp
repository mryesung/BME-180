#include <iostream>
#include "Arduino.h"

int main()
{
	//std::cout << "Insert your COM Port : ";

	Arduino* a1 = new Arduino("COM4");

	if (a1->IsConnected())
		std::cout << "is connected" << std::endl;

	delete a1;

	return 0;
}