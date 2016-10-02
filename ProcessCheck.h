#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <iostream>
#include <vector>

#ifndef PROCESSCHECKS_H
#define PROCESSCHECKS_H

class ProcessCheck
{
protected:
	HANDLE ProcessHandle = NULL;
	DWORD pId = NULL;
	HANDLE Snapshot = NULL;
	HANDLE ModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	PROCESSENTRY32 pe32 = { 0 };

	std::vector<std::string> PIDPaths;

	struct HandleCheck
	{
		std::vector<char*> PSnapshot;
		std::vector<char*> NSnapshot;
		int PCount;
	};
	// Known third party applications
	std::vector<LPCTSTR> ToCheck
		= { "explorer.exe", "freestyle gunz.exe", "sb.exe", "thebestrat.exe", "hitbox.exe" };

public:
	ProcessCheck::HandleCheck check;
	DWORD GetProcessId(LPCTSTR);
	bool EnumerateModules(DWORD);
	bool EnumerateSnapshot();
	bool IterateVector();
	void CheckHandleCount();
	void SetSnapshot();
	void GetProcessPath(DWORD);
	TCHAR* GetProcessName(DWORD);
};
#endif