#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include "FelonAlert.h"
#include "Caesar.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <fstream>

// Class declerations 
UserProfile ZUser;
ProcessCheck ZProcess;
Felon ZFelon;
Caesar ZCaesar;

using namespace std;

// TODO: Figure out a decent way to deallocate cleanly
string GetUniqueIdentifier() {
	// yo delete the pointrs or i'll delete your fucking life
	string MBID = ZFelon.CallWMIC("wmic baseboard get serialnumber");
	string BIOSID = ZFelon.CallWMIC("wmic bios get serialnumber");
	string encryptMBID = ZCaesar.encrypt(MBID);
	string encryptBIOSID = ZCaesar.encrypt(BIOSID);
	string toReturn = encryptMBID;
	toReturn += encryptBIOSID;
	for (int i = 0; i < sizeof(toReturn); i++) {
		if (!isalnum(toReturn[i]) || toReturn[i] == ' ')
			toReturn.erase(i, 1);
	}
	return toReturn;
}

int main()
{
	ofstream baseboard;
	baseboard.open("sig.txt");
	string tmpSig = GetUniqueIdentifier();
	baseboard << tmpSig;
	baseboard.close();
	cout << tmpSig << endl;
	cin.ignore();
	return 0;
}
