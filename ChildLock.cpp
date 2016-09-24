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
#include "Checksum.h"

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
		if (
			toReturn[i] == ' '
		) {
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

int main()
{
	//cout << ZFelon.CallWMIC("wmic baseboard get serialnumber") << endl;
	//cout << GetUniqueIdentifier() << endl;
	cout << GetFileChecksum("sig.txt") << endl;
	cin.ignore();
	return 0;
}
