#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include "FelonAlert.h"
#include "Caesar.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <thread>

// Class declerations
UserProfile ZUser;
ProcessCheck ZProcess;
Felon ZFelon;
Caesar ZCaesar;

using namespace std;

// TODO: Figure out a decent way to deallocate cleanly
string GetUniqueIdentifier()
{
	string MBID = ZFelon.CallWMIC("wmic baseboard get serialnumber");
	string encryptMBID = ZCaesar.encrypt(MBID);
	string toReturn = encryptMBID;

	// Cleaning up string
	size_t len = toReturn.length();
	int i = 0;
	while (i < len)
	{
		if (toReturn[i] == ' ')
		{
			cout << toReturn[i] << endl;
			toReturn.erase(i, 1);
			len--;
		}
		else {
			i++;
		}
	}
	return toReturn;
}

DWORD IntegLoop()
{
	for (;;) {
		cout << GetUniqueIdentifier() << endl;
		ZProcess.SetSnapshot();
		ZProcess.EnumerateSnapshot();
		ZProcess.IterateVector();
		ZUser.CheckChild();
		cout << "Integrity loop finished. Running again in 10 minutes." << endl;
		Sleep(600000);
	}
	return NULL;
}

int main()
{
	thread t(IntegLoop);
	t.join();
	cin.ignore();
	return 0;
}
