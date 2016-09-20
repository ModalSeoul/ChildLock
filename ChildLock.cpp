#include "stdafx.h"
#include "UserProfile.h"
#include "ProcessCheck.h"
#include "FelonAlert.h"
#include "Caesar.h"
#include <iostream>
#include <Windows.h>

// Class declerations 
UserProfile ZUser;
ProcessCheck ZProcess;
Felon ZFelon;
Caesar ZCaesar;

using namespace std;

// Makes my life easier
string StrAppend(
	string str,
	string append
) {
	return str + ":" + append + ":";
}

// TODO: Figure out a decent way to deallocate cleanly
string* GetUniqueIdentifier() {
	string toReturn = "";
	string *MBID = new string(ZFelon.CallWMIC("wmic baseboard get serialnumber"));
	string *BIOSID = new string(ZFelon.CallWMIC("wmic bios get serialnumber"));
	string encryptMBID = ZCaesar.encrypt(*MBID);
	string encryptBIOSID = ZCaesar.encrypt(*BIOSID);
	toReturn += encryptMBID;
	toReturn += encryptBIOSID;
	cout << toReturn << endl;
	return &toReturn;
}

int main()
{
	string *tmpSig = GetUniqueIdentifier();
	// Send signature to server for storage & analysis
	// delete
	cin.ignore();
	return 0;
}
