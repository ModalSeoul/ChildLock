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

string split(string str, string split)
{
	string builtStr = "";
	for (auto i : str)
	{
		if (i == split[0] && i == split[1])
		{
			// It's 2 in the morning and this seems like a good idea
			// - It is not a good idea but fuck I'm tired
			for (int j = 0; i < sizeof(str); i++)
			{
				builtStr += str[i];
			}
		}

	}
	return builtStr;
}

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

int test(char i)
{
	return (int)i;
}

int main()
{
	// FUCK I'M GOING TO BED I AM SO TIRED
	cout << ZFelon.CallWMIC("wmic baseboard get serialnumber") << endl;
	cout << GetUniqueIdentifier() << endl;

	cin.ignore();
	return 0;
}
