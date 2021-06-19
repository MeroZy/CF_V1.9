#include "addrr.h"
#ifndef _BYPASS_H_
#define _BYPASS_H_

bool isbypass = false;
#define WeaponMgr 0x1C3A270
bool Ready2Hoook()
{
	if (GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("ClientFx.fxd") != NULL)
		return true;
	return false;
}

typedef struct _WEAPON
{
	unsigned char Data[0x4E0C];
} WEAPON, *PWEAPON;

PWEAPON pOldWeapons[0x1000];

PWEAPON GetWeaponByIndex(int index)
{
	return pOldWeapons[index];
}

void CreateBackup(DWORD dwCShell, DWORD dwWeaponMgr)
{
	DWORD pWeaponMgr = *(DWORD*)(dwCShell + dwWeaponMgr);
	for (int i = 0; i < 0x1000; i++)
	{
		DWORD dwWeapon = *(DWORD*)(pWeaponMgr + (4 * i));
		if (dwWeapon)
		{
			pOldWeapons[i] = new WEAPON;
			memcpy(pOldWeapons[i], (void*)(dwWeapon), sizeof(WEAPON));
		}
	}
}

bool isweaponhack = false;
bool isbackup = false;

//DWORD dwBypassWeaponHack = 0x7DC775;


void ChangeWeaponF(int weaponid, int targetid, DWORD WeaponMgr_)
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
	DWORD pWeaponMgr = *(DWORD*)(CShell + WeaponMgr);
	if (pWeaponMgr != NULL)
	{
		DWORD* weapon = (DWORD*)(pWeaponMgr + (4 * weaponid));
		DWORD* target = (DWORD*)(pWeaponMgr + (4 * targetid));
		if (weapon != NULL && target != NULL)
		{
			*weapon = *target;
		}
	}
}



bool isGameReadyHook()
{
	if (GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("ClientFx.fxd") != NULL)
		return true;
	return false;
}

void Bypassa()
{
	if (!isGameReadyHook()) return;
	//================Anti Send Error Report===============//
	DWORD crossfire = (DWORD)GetModuleHandleA(eCF);
	if (crossfire == NULL) return;
	if (!isbackup)
	{
		DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
		if (CShell != NULL)
		{
			//================Client 28_4===============//
			CreateBackup(CShell, WeaponMgr);//28_4 
			//================Client 28_3===============//
			DWORD dwBypassWeaponHack = (DWORD)(CShell + 0x7DC775);
			DWORD dwOldProtect;
			VirtualProtect((void*)(dwBypassWeaponHack), sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect);
			//memcpy((void*)(CShell + 0x760D6D),"\xE9\xF8\x01\x00\x00\x90",6) ;
			*(DWORD*)(dwBypassWeaponHack + 0x1) = (DWORD)GetWeaponByIndex - dwBypassWeaponHack - 5;
			VirtualProtect((void*)(dwBypassWeaponHack), sizeof(DWORD), dwOldProtect, NULL);

			//================Client 31_0===============//
			memcpy((void*)(CShell + 0x7DE581), "\xE9\xDC\x03\x00\x00\x90", 6);  //0x7DE581 or 0x7DE962          aob : 0F 84 ?? ?? ?? ?? B8 ?? ?? ?? ?? 68
			memcpy((void*)(CShell + 0x7DE16F), "\x80\x47\x19\x00", 4); //aob : 80 47 19 01

			if (!isweaponhack)
			{
				ChangeWeaponF(M4A1, M4A1SGSpirit, WeaponMgr);
				ChangeWeaponF(AK47, AK47KnifeBornBeast, WeaponMgr);
				ChangeWeaponF(DesertEagle, DesertEagleElDorado, WeaponMgr);
				//ChangeWeaponF(KNIFE,KukriBeast,WeaponMgr);
				ChangeWeaponF(AWM, BarrettIronShark, WeaponMgr);
				//ChangeWeaponF(M16, 731, WeaponMgr);
				//ChangeWeaponF(M700, BarrettIronShark, WeaponMgr);
				//	ChangeWeaponF(AK47BlueCrystal, AK47KnifeIronBeast,WeaponMgr);
				isweaponhack = true;
			}
		}
		//================Fast Knife===============//
		isbackup = true;
	}
}


void StartHacks1(void)
{
	if (!Ready2Hoook()) return;
	DWORD CShell = (DWORD)GetModuleHandleW(L"CShell.dll");
	DWORD crossfire = (DWORD)GetModuleHandleW(L"crossfire.exe");
	if (crossfire == NULL) return;
	//================Fast Knife===============//
	DWORD dwFastKnife = *(DWORD*)(CShell + 0x1C3A270);// WeaponMgr
	for (int i = 0; i < 0x1000; i++)
	{
		DWORD dwFastKnifePtr = *(DWORD*)(dwFastKnife + (4 * i));
		if (dwFastKnifePtr != NULL)
		{
			for (int x = 0; x < 9; x++)
			{
				*(float*)(dwFastKnifePtr + (0x10D4 + (4 * x))) = 3.0f; // KnifeNormalAniRate
				*(float*)(dwFastKnifePtr + (0x1134 + (4 * x))) = 3.0f; // KnifeNormalAniRate2
			}
		}
	}
}

void WINAPIV DisconectFromServer()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [ESP + 0x4]
			XOR EAX, EAX
			CMP[ESP + 0x8], EAX
			JMP RET_JE
		RET_JNZ : MOVZX EDX, BYTE PTR DS : [ECX]
				  DEC[ESP + 0x8]
				  XOR EDX, EAX
				  AND EDX, 0x0FF
				  SHR EAX, 0x8
				  XOR EAX, DWORD PTR DS : [EDX * 4 + 0x779E88]
				  INC ECX
				  CMP[ESP + 0x8], 0x0
				  JNZ RET_JNZ
			  RET_JE : NOT EAX
	}
}

void DetourCreateE8(BYTE *src, DWORD dst, DWORD len)
{
	DWORD OldProtection, RealAddress;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &OldProtection);
	RealAddress = (DWORD)((dst + 1) - (DWORD)src) - 5;
	*src = 0xE8;
	*(DWORD *)(src + 0x01) = RealAddress;
	VirtualProtect(src, len, OldProtection, 0);
	return;
}

void check()
{
	DWORD Engine = (DWORD)GetModuleHandleA("crossfire.exe");
	memcpy((VOID*)(Engine + check1), "\xEB", 1);
	memcpy((VOID*)(Engine + check2), "\xEB", 1);
	memcpy((VOID*)(Engine + check3), "\xEB", 1);
	memcpy((VOID*)(Engine + check4), "\xEB", 1);
	memcpy((VOID*)(Engine + check5), "\xEB", 1);
	memcpy((VOID*)(Engine + check6), "\xEB", 1);
}

void CALLBypass()
{
	check();
	DWORD Engine = (DWORD)GetModuleHandleA("crossfire.exe");
	DetourCreateE8((PBYTE)(Engine + hackDetect_1), (DWORD)DisconectFromServer, 5);
	DetourCreateE8((PBYTE)(Engine + hackDetect_2), (DWORD)DisconectFromServer, 5);
	DetourCreateE8((PBYTE)(Engine + hackDetect_3), (DWORD)DisconectFromServer, 5);
	DetourCreateE8((PBYTE)(Engine + hackDetect_4), (DWORD)DisconectFromServer, 5);
	DetourCreateE8((PBYTE)(Engine + hackDetect_5), (DWORD)DisconectFromServer, 5);
	DetourCreateE8((PBYTE)(Engine + hackDetect_6), (DWORD)DisconectFromServer, 5);
}





#endif