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


// TODO BEFORE PATCH
/*
1 JACK OFF
2 MD5 EACH RUNNING PROCESS
3 WRITE A HANDLE LOOP
4 FUCK
*/
int main()
{
	cout << GetUniqueIdentifier() << endl;
	ZProcess.SetSnapshot();
	ZProcess.EnumerateSnapshot();
	cin.ignore();
	return 0;
}
