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
		if (isalpha(toReturn[i]) || !isalnum(toReturn[i]) || toReturn[i] == ' ')
		{
			toReturn.erase(i, 1);
			len--;
		}
		else
			i++;
	}
	return toReturn;
}

int test(char i)
{
	return (int)i;
}

int main()
{
	cout << GetUniqueIdentifier() << endl;
	cin.ignore();
	return 0;
}
