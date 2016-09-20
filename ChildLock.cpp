#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include "FelonAlert.h"
#include "Caesar.h"
#include <iostream>
#include <Windows.h>

UserProfile ZUser;
ProcessCheck ZProcess;
Felon ZFelon;
Caesar ZCaesar;

int main()
{
	std::string welp = ZCaesar.encrypt(ZFelon.CallWMIC("wmic bios get serialnumber"));
	std::cout << ZCaesar.encrypt(welp) << std::endl;
	//std::cout << ZFelon.CallWMIC("wmic bios get version") << std::endl;
	//std::cout << ZFelon.CallWMIC("wmic bios get caption") << std::endl;
	//std::cout << ZFelon.CallWMIC("wmic bios get description") << std::endl;
	std::cin.ignore();
	return 0;
}

