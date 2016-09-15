#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include <iostream>
#include <Windows.h>

UserProfile c_UserProfile;
ProcessCheck c_ProcessCheck;

int main()
{
	c_UserProfile.CheckChild();
	DWORD IsRunning = c_ProcessCheck.GetProcessId(TEXT("Launcher.exe"));
	c_ProcessCheck.EnumerateSnapshot();
	c_ProcessCheck.IterateVector();
	if (IsRunning)
		cout << "Badboy found: " << IsRunning << endl;
	int n;
	std::cin >> n;
	return 0;
}

