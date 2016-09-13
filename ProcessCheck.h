#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>

#ifndef PROCESSCHECKS_H
#define PROCESSCHECKS_H

class ProcessCheck {
protected:
	HANDLE ProcessHandle = NULL;
	DWORD pId = NULL;

public:
	DWORD GetProcessId(LPCTSTR);

};
#endif