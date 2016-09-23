#include "UserProfile.h"
#include <iostream>
#include <Windows.h>
#include <Lmcons.h>
#include <tchar.h>

using namespace std;

//void UserProfile::SendToServer(TCHAR* uName)
//{
//	// TODO: Jeff/Silent/Carter - Implement ZPOST
//	// call to send user's information to server.
//}
//
//bool UserProfile::IsChild(TCHAR* uName)
//{
//	for (auto const& name : CHILDREN)
//	{
//		if (_tcscmp(name, uName) == 0)
//		{
//			cout << "Child found " << name << endl;
//			return true;
//		}
//	}
//	// Only hit if loop finds no match
//	return false;
//}
//
//bool UserProfile::CheckChild()
//{
//	TCHAR uName[UNLEN + 1];
//	DWORD szBuffer = UNLEN + 1;
//	if (GetUserName((TCHAR*)uName, &szBuffer))
//	{
//		if (IsChild(uName))
//		{
//			SendToServer(uName);
//			return true;
//		}
//	}
//	return false;
//}