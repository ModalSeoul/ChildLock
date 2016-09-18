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
	ZProcess.EnumerateSnapshot();
	std::cin.ignore();
	return 0;
}

