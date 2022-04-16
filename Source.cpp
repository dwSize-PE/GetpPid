#include <Windows.h>
#include <TlHelp32.h>
#include <string>

DWORD GetpPid(string ProcName) {
  DWORD Pid;
  HANDLE hSnap = CreateToolHelp32SnapShot(TH32CS_SNAPPROCESS, 0);
  
  if (hSnap != INVALID_HANDLE_VALUE) {
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    
    if (Process32First(hSnap, &pe)) {
      do {
        if (pe32.szExeFile == ProcName)
          Pid = pe32.th32ProcessID; //Pid do processo pai
         } while (Process32Next(hSnap, &pe32));
         
      if (Pid == pe32.th32ParentProcessID)
        Pid = pe32.thProcessID; //Pid do processo filho
    }
  CloseHandle(hSnap);
  return Pid;
 }
