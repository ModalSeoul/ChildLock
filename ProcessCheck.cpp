#include "ProcessCheck.h"
#include <Windows.h>

// Yes or no on this formatting? I'm unsure :/
DWORD ProcessCheck::GetProcessId(
	LPCTSTR pName
) {
	PROCESSENTRY32 pe32 = { 0 };
	HANDLE Snapshot = NULL;
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
		if (!lstrcmpiW(pe32.szExeFile, pName)) {3
			pId = pe32.th32ProcessID;
			return pId;
	}
#else
		if (!lstrcmpiA(pe32.szExeFile, pName)) {
			pId = pe32.th32ProcessID;
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
			std::cout << "JUAN MAIK JUAN WATER U DOIN" << std::endl;
			ShellExecute(0, 0, "https://www.youtube.com/watch?v=PD6AfcoG4o8", 0, 0, SW_SHOW);
		}
	}
	return true;
}