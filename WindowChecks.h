#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>

#ifndef WINDOWCHECKS_H
#define WINDOWCHECKS_H

class WindowCheck {
protected:
	HANDLE ProcessHandle = NULL;
	DWORD pId = NULL;

public:
	DWORD GetProcessId(LPCTSTR);

};
#endif