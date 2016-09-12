#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

#ifndef USERPROFILE_H
#define USERPROFILE_H

////////////////////////////////////////////
// UserProfile.h
// Purpose:
//		Checks current Windows profile
//		against list of known cheat devs.
////////////////////////////////////////////

// TODO: Implement Caesar Cipher encryption
class UserProfile {
protected:
	// To be replaced by SQL table to store children
	vector<char*> CHILDREN = {
		"Angeles Tagle",
		"Mike",
		"Modal"
	};
	// Compare to 0, 1, 2 values from SQL table
	enum h_Severity {
		INSPECTION,
		USER,
		DEVELOPER
	};
public:
	bool CheckChild();
	bool IsChild(TCHAR*);
	void SendToServer(TCHAR*);
};
#endif