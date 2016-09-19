#include "ProcessCheck.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <Psapi.h>
#include <fstream>

void printError(TCHAR* msg);


void ProcessCheck::SetSnapshot() {
	// Create quick 'snapshot' of process list
	Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// Grabbing the size of processes
	pe32.dwSize = sizeof(PROCESSENTRY32);
}

// Yes or no on this formatting? I'm unsure :|
DWORD ProcessCheck::GetProcessId(
	LPCTSTR pName
) {
	// Check CreateToolhelp call success
	if (Snapshot == INVALID_HANDLE_VALUE)
		SetSnapshot();

	if (!Process32First(Snapshot, &pe32)) {
		CloseHandle(Snapshot);
		return 0;
	}

	do {
#ifdef UNICODE
		// Storing pId in header declared DWORD & returning
		if (!lstrcmpiW(pe32.szExeFile, pName)) {
			pId = pe32.th32ProcessID;
			return pId;
	}
#else
		if (!lstrcmpiA(pe32.szExeFile, pName)) {
			pId = pe32.th32ProcessID;
			EnumerateModules(pId);
			return pId;
		}
#endif
	} while (Process32Next(Snapshot, &pe32));

	// After we have the snapshot, we close the handle.
	if (Snapshot)
		CloseHandle(Snapshot);

	return 0;
}

bool ProcessCheck::IterateVector() {
	for (auto& proc : ToCheck) {
		DWORD tempCheck = GetProcessId(TEXT(proc));
		if (tempCheck) {
			// TODO: This dude's running a process we dun like
			return true;
		}
	}
	// Only hit if return above isn't hit
	return false;
}

bool ProcessCheck::EnumerateSnapshot() {
	if (!Process32First(Snapshot, &pe32)) {
		std::cout << "Failed, line 61(debug str)" << std::endl;
		std::cout << GetLastError() << std::endl;
		return false; // Previously closing handle
	}

	do {
		GetProcessName(pe32.th32ProcessID);
		//_tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
		//_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
		//_tprintf(TEXT("\n  Parent process ID = %0x%08X"), pe32.th32ParentProcessID);
		//_tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
	} while (Process32Next(Snapshot, &pe32));
	return true;
}


// This returns this(http://i.imgur.com/qqfaDdk.png)
bool ProcessCheck::EnumerateModules(DWORD pId) {
	ModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);

	if (ModuleSnap == INVALID_HANDLE_VALUE) {
		printError(TEXT("CreateToolhelp32Snapshot (of modules)"));
		return false;
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(ModuleSnap, &me32)) {
		printError(TEXT("Module32First"));  // show cause of failure
		return false;
	}

	do {
		_tprintf(TEXT("\n\n	  MODULE NAME:	%s"), me32.szModule);
		_tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
		_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
		_tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		_tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		_tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
		_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);
	} while (Module32Next(ModuleSnap, &me32));
	return true;
}

void ProcessCheck::CheckHandleCount() {
	DWORD szBuffer = NULL;
	GetProcessHandleCount(GetCurrentProcess(), &szBuffer);
	std::cout << "\nPreviously: " << check.PCount << "\nNow: " << szBuffer;

	if (!szBuffer == NULL)
		if (!check.PCount == szBuffer) {
			
			check.PCount = szBuffer;	// Update PCount 
			SetSnapshot();				// Reset process snapshot
			do {
				check.NSnapshot.push_back((char*)pe32.th32ProcessID);
			} while (Process32Next(Snapshot, &pe32));
		}
}

TCHAR* ProcessCheck::GetProcessName(DWORD pId) {
	TCHAR szName[MAX_PATH] = TEXT("<unrecognized>");
	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, pId);

	if (NULL != hProc) {
		HMODULE hMod;
		DWORD cbNeeded;
		if (EnumProcessModules(hProc, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProc, hMod,
				szName, sizeof(szName) / sizeof(TCHAR));
		}
	}
	return szName;
}

void printError(TCHAR* msg) {
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}

