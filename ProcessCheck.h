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
	HANDLE Snapshot = NULL;
	HANDLE ModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;
	PROCESSENTRY32 pe32 = { 0 };

	struct HandleCheck {
		std::vector<char*> PSnapshot;
		int PCount;
	};
	// Known third party applications
	std::vector<LPCTSTR> ToCheck = {
		"explorer.exe",
		"freestyle gunz.exe",
		"sb.exe",
		"thebestrat.exe",
		"hitbox.exe"
	};
	HANDLE selfHandle = GetCurrentProcess();

public:
	ProcessCheck::HandleCheck check;
	DWORD GetProcessId(LPCTSTR);
	bool EnumerateModules(DWORD);
	bool EnumerateSnapshot();
	bool IterateVector();
	void HandleCount();
	void PushSnapshot(DWORD);
	void SetSnapshot();
};
#endif