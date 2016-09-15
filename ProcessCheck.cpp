#include "ProcessCheck.h"
#include <Windows.h>

// Yes or no on this formatting? I'm unsure :/
DWORD ProcessCheck::GetProcessId(
	LPCTSTR pName
) {
	// Create quick 'snapshot' of process list
	Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	// Check CreateToolhelp call success
	if (Snapshot == INVALID_HANDLE_VALUE)
		return 0;
	
	// Grabbing the size of processes
	pe32.dwSize = sizeof(PROCESSENTRY32);

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
			std::cout << "\nJUAN MAIK JUAN WATER U DOIN\n" << std::endl;
			//ShellExecute(0, 0, "https://www.youtube.com/watch?v=PD6AfcoG4o8", 0, 0, SW_SHOW);
			return true;
		}
	}
	// Only hit if return below ShellExecute isn't hit
	return false;
}

bool ProcessCheck::EnumerateSnapshot() {
	if (!Process32First(Snapshot, &pe32)) {
		std::cout << "Failed, line 61(debug str)" << std::endl;
		CloseHandle(Snapshot);
	}

	//do {
	//	_tprintf(TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID);
	//	_tprintf(TEXT("\n  Thread count      = %d"), pe32.cntThreads);
	//	_tprintf(TEXT("\n  Parent process ID = %0x%08X"), pe32.th32ParentProcessID);
	//	_tprintf(TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase);
	//} while (Process32Next(Snapshot, &pe32));
	return true;
}

bool ProcessCheck::EnumerateModules(DWORD pId) {
	ModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pId);
	if (ModuleSnap == INVALID_HANDLE_VALUE) {
		std::cout << "line 76" << std::endl;
		return false;
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(ModuleSnap, &me32)) {
		std::cout << "line 81" << std::endl;
		return false;
	}

	do {
		_tprintf(TEXT("\n\n		MODULE NAME:	%s"), me32.szModule);
		_tprintf(TEXT("\n     Executable     = %s"), me32.szExePath);
		_tprintf(TEXT("\n     Process ID     = 0x%08X"), me32.th32ProcessID);
		_tprintf(TEXT("\n     Ref count (g)  = 0x%04X"), me32.GlblcntUsage);
		_tprintf(TEXT("\n     Ref count (p)  = 0x%04X"), me32.ProccntUsage);
		_tprintf(TEXT("\n     Base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
		_tprintf(TEXT("\n     Base size      = %d"), me32.modBaseSize);
	} while (Module32Next(ModuleSnap, &me32));
	return true;
}