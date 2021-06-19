#include <Windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <conio.h>
#include <stdio.h>
#include "ShObjIdl.h""
#include <urlmon.h>
#include <iostream>
#include<tchar.h>
#include <process.h>
#include <tlhelp32.h>
using std::endl;
using std::cout;
#pragma comment(lib, "urlmon")
#pragma comment(lib,"wininet.lib")
using namespace std;

//  Forward declarations:
#include <strsafe.h>

#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")

void DelMe()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}





void killProcessByName(const char *filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, filename) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}
BOOL TerminateMyProcess(DWORD dwProcessId, UINT uExitCode)
{
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == NULL)
		return FALSE;

	BOOL result = TerminateProcess(hProcess, uExitCode);

	CloseHandle(hProcess);

	return result;
}
#define WIN32_LEAN_AND_MEAN
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ


BOOL CreateRemoteThreadInject(DWORD ID, const char * dll);

BYTE progress = 0;

BOOL Compare(LPWSTR A, LPWSTR B, INT len)
{
	for (INT i = 0; i < len; i++)
	{
		if (A[i] != B[i])
			return false;
	}
	return true;
}

DWORD GetProcessId(IN PCHAR szExeName);

int main()

{
	
	killProcessByName("Taskmgr.exe");
	
	SetConsoleTitle("MeroZy - TheGeek Advanced Injector (CFW)");
	ITaskbarList *pTaskList = NULL;
HRESULT initRet = CoInitialize(NULL);
HRESULT createRet = CoCreateInstance( CLSID_TaskbarList,
                                      NULL,
                                      CLSCTX_INPROC_SERVER,
                                      IID_ITaskbarList,
                                      (LPVOID*)&pTaskList );

if(createRet == S_OK)
{

    pTaskList->DeleteTab(GetConsoleWindow());

    pTaskList->Release();
}

	printf("CrossFire West Hacks \n");
	printf("Credits : TheGeek - MeroZy \n");
	printf("This's Official TheGeek's & MeroZy's injector , Don't use other injector \n");
	\
 char dll[10];


 ////GetFullPathName("pQ5zrihFh6H52gjoxS5Q6Cup.dll", MAX_PATH, dll, NULL);


	GetFullPathName("D:\\kyfguiCuGb3sN7Vix8.dll", MAX_PATH, dll, NULL);


 // Show the .DLL Path.
 //printf("DLL : ");
 //printf(dll);
 //printf("\n\n\n");
    char buf[MAX_PATH] = {0}; 
 // Proecss Name
 DWORD ID = GetProcessId("crossfire.exe");

 if (!CreateRemoteThreadInject(ID, dll))
 {

  printf("Injection Failed Try It again !");

  Sleep(1000);
    killProcessByName("Taskmgr.exe");
  Sleep(1000);
    killProcessByName("Taskmgr.exe");
  Sleep(1000);
    killProcessByName("Taskmgr.exe");
	//DelMe();

  exit(1);


 }
 else
 {

  printf("Hack Injected , Enjoy Hack ! xD");
  Sleep(1000);
    killProcessByName("Taskmgr.exe");
  Sleep(1000);
    killProcessByName("Taskmgr.exe");
  Sleep(1000);
    killProcessByName("Taskmgr.exe");
	//DelMe();

  exit(1);


 }
 return 0;
}

DWORD GetProcessId(IN PCHAR szExeName)

{
 DWORD dwRet = 0;
 DWORD dwCount = 0;

 HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

 if (hSnapshot != INVALID_HANDLE_VALUE)
 {
  PROCESSENTRY32 pe = { 0 };
  pe.dwSize = sizeof(PROCESSENTRY32);

  BOOL bRet = Process32First(hSnapshot, &pe);

  while (bRet)
  {
   if (!_stricmp(pe.szExeFile, szExeName))
   {
    dwCount++;
    dwRet = pe.th32ProcessID;
   }
   bRet = Process32Next(hSnapshot, &pe);
  }

  if (dwCount > 1)
   dwRet = 0xFFFFFFFF;

  CloseHandle(hSnapshot);
 }

 return dwRet;
}


BOOL CreateRemoteThreadInject(DWORD ID, const char * dll)

{

 HANDLE Process;


 LPVOID Memory;


 LPVOID LoadLibrary;


 if (!ID)
  return false;


 Process = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, ID);


 LoadLibrary = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");


 Memory = (LPVOID)VirtualAllocEx(Process, NULL, strlen(dll), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);


 WriteProcessMemory(Process, (LPVOID)Memory, dll, strlen(dll), NULL);


 CreateRemoteThread(Process, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibrary, (LPVOID)Memory, NULL, NULL);


 CloseHandle(Process);

 VirtualFree((LPVOID)Memory, strlen(dll), NULL);

 return true;
}