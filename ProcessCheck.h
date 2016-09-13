#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

#ifndef PROCESSCHECKS_H
#define PROCESSCHECKS_H

class ProcessCheck {
protected:
	HANDLE ProcessHandle = NULL;
	DWORD pId = NULL;

	// Known third party applications
	std::vector<LPCTSTR> ToCheck = {
		"explorer.exe",
		"freestyle gunz.exe",
		"sb.exe",
		"thebestrat.exe",
		"hitbox.exe"
	};

public:
	DWORD GetProcessId(LPCTSTR);
	bool IterateVector();

};
#endif