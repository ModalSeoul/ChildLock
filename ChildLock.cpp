#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include <iostream>
#include <Windows.h>

UserProfile ZUser;
ProcessCheck ZProcess;

int main()
{
	ZProcess.SetSnapshot();
	while (1) {
		ZProcess.CheckHandleCount();
		Sleep(500);
	}
	ZProcess.EnumerateSnapshot();
	std::cin.ignore();
	return 0;
}

