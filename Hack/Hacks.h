#include "address.h"
#include "XOR.h"

//==================Other================================
extern hMenuCore *hMenu;
extern bool mouse_enabled;
extern bool menu_move;

float ScreenCenterX = 0.0f;
float ScreenCenterY = 0.0f;

bool am_PlayerView = false;
bool display = true;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

//=======================================================
//========================addys==========================
#define as1WallArray       0x11BEFB8
#define as12ModelNode           0x1C3A19C
#define as12BasicPlayerInfo         0x1A9F098
#define as12PLAYERCLIENTBASE     0x11F7F34
#define as12PLAYERCLIENTBASEOFFSET   0x78
#define asp12CLTPlayerClient     0x14FAD90



//#define asModelNode    0x17EE234
#define as12DamageZone 0xF7B950 //106B8123   > 68 E06EDF10    PUSH FKCshell.10DF6EE0                   ;  ASCII "DamageZone"
#define as12DamagePerSec 0xF7B940 //106B81D4   . 68 D06EDF10    PUSH FKCshell.10DF6ED0                   ;  ASCII "DamagePerSec"
#define as12VisibleZoneIndex 0xF7B898 //106B67C8   > BF 286EDF10    MOV EDI,FKCshell.10DF6E28                ;  ASCII "VisibleZoneIndex"
#define as12Eatman 0xF7B8DC //106B63DF   > BF 6C6EDF10    MOV EDI,FKCshell.10DF6E6C                ;  ASCII "Eatman"
#define as12EatmanName 0xF7B8D0 //106B6440   . BF 606EDF10    MOV EDI,FKCshell.10DF6E60                ;  ASCII "EatmanName"
#define as12versioncode 0xF7B968 //106B7F22   . 68 F86EDF10    PUSH FKCshell.10DF6EF8                   ;  ASCII "versioncode"
#define as12Zoneman 0xF7B8E4 //106B6383   . BF 746EDF10    MOV EDI,FKCshell.10DF6E74                ;  ASCII "Zoneman"
#define as12ZonemanName 0xF7B8B8 //106B65BB   . BF 486EDF10    MOV EDI,FKCshell.10DF6E48                ;  ASCII "ZonemanName"
#define asFallDamage 0x17EE2E8
#define asFallDamageOffset 0x4
#define as12MaxDepth 0xF7B95C
#define as12Floor 0xF7B900
#define as12FloorNameMsgIndex 0xF7B8EC
#define as12PointIndex 0xF7B910
#define as12Normal 0xEC3A6C
#define as12DamagePerMeter 0xF3FF34
#define as12TargetZone 0xF83F28
#define as12USE_DAMAGE_ZONE_VER1 0xF7BA20
#define as12world 0xF7B97C

#define pWorld_Target 0xF84048
#define pDist 0xF7B908
#define pPointIndex 0xF7B910
#define pPolyList 0xF7B928
#define pPointList 0xF7B934
#define pName 0xF3ED80
#define pheader 0xF7B974
#define pPos 0xF3D558
#define pRot 0xF7B8CC
#define pZoneName 0xF7B8AC
#define pEditPoly 0xF7B91C

#define asGetPlayerByIndex(LTClientShell, dwID) (CPlayer*)(LTClientShell + (dwID * dwmCPlayerSize) + dwmCPlayerStart)
//=========================================================
//==========================Glow==========================
typedef void(WINAPI* oas12GlowESP)(bool value);
#define as12GLOWESP 0x092F20
//====================[ESP]====================
#define AAAAAAAAAaLTClientShell 0x14B04B0 //8B 0D ? ? ? ? ? ? ? ? 50 8D 44 24 ? ? 50 81 C1 ? ? ? ? ? ? ? ?
#define AAAAAAAAAAAAdwCPlayerStart 0x208 //0F B6 8E ?? ?? ?? ?? 69 C9 ?? ?? ?? ?? 8A 84 31 ?? ?? ?? ?? 5E C3
#define AAAAAAAAAAAAAAAMEOffset 0x214 //8A 84 31 ?? ?? ?? ?? 5E C3
#define AAAAAAAAAAAAdwCPlayerSize 0xD80 //69 C9 ?? ?? ?? ?? 8A 84 31 ?? ?? ?? ?? 5E C3
#define AAAAAAAAAAAAaLTModel 0x14AB79C //8B 0D ?? ?? ?? ?? 8B 44 24 0C 8B 11
#define aIntersectSegment 0x68A86D

#define PLAYERVIEW_POINTER 0x14FADC0 // CFNA/WEST
//AOB : ? ? ? ? ? ? ? ? 01 01 00 00 ? ? 00 00 00 00 00 00 00 00 00 20 43 // cshell.dll
class cCamera
{
public:
	char _0x0000[12];
	DWORD Mirror;							// 0xC ~ 0x10
	char _0x0010[84];
	DWORD PlayerView;						// 0x64 ~ 0x68
};




/*#define AAAAAAAAAaLTClientShell 0x14B04B0 //8B 0D ? ? ? ? ? ? ? ? 50 8D 44 24 ? ? 50 81 C1 ? ? ? ? ? ? ? ?
#define AAAAAAAAAAAAdwCPlayerStart 0x14AB79C //8B 0D ?? ?? ?? ?? 8B 44 24 0C 8B 11
#define AAAAAAAAAAAAAAAMEOffset 0x208 //0F B6 8E ?? ?? ?? ?? 69 C9 ?? ?? ?? ?? 8A 84 31 ?? ?? ?? ?? 5E C3
#define AAAAAAAAAAAAdwCPlayerSize 0xD80 //69 C9 ?? ?? ?? ?? 8A 84 31 ?? ?? ?? ?? 5E C3
#define AAAAAAAAAAAAaLTModel 0x214 //8A 84 31 ?? ?? ?? ?? 5E C3*/
//=========================================================
struct a12ModelNodes
{
	char _0x0000[212];
	float dimension[3];
};

//=====================[Mutant]===============
#define oGameUi 0x1F0
#define oNanoPVScreen 0x72E4
#define oMutant 0x170
#define aOpenMutantScreen 0x6A9DD2   //CPU //DisasmAddress   Hex dump          Command                                  Comments106AA5EB   . /74 35         JE SHORT 106AA622

void unlockallmutants()
{
	//Offset GameUi
	//AOB: 8B 81 ?? ?? ?? ?? 85 C0 74 50

	//Offset NanoPVScreen
	//AOB: 8B 8E ?? ?? ?? ?? 8B 01 8B 50 ?? FF D2 8B 8E ?? ?? ?? ?? 3B CB 74 05

	//Offset Mutant
	//AOB: 89 8C 87 ?? ?? ?? ?? 89 4C 24 10

	//Address OpenMutantScreen
	//AOB: 74 35 D9 05 ?? ?? ?? ?? C6 87 94 01 00 00 01
	bool Enabled;
	DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD pLTClientShell = *(DWORD*)(CShell + AAAAAAAAAaLTClientShell);
	DWORD pGameUI = *(DWORD*)(pLTClientShell + oGameUi);
	if (pGameUI)
	{
		DWORD pNanoPVScreen = *(DWORD*)(pGameUI + oNanoPVScreen);

		if (pNanoPVScreen)
		{
			if (Enabled)
			{
				for (int x = 0; x <= 6; x++)
				{
					*(DWORD*)(pNanoPVScreen + oMutant + (4 * x)) = 1;
				}

				memcpy((void*)(CShell + aOpenMutantScreen), "\x90\x90", 2);
			}
			else
			{
				memcpy((void*)(CShell + aOpenMutantScreen), "\x74\x35", 2);
			}

		}
	}


}
//=========================================





void hSettings()
{
	if( hMenuSettings[2] )
	{
		mouse_enabled = true;
	}
	else
	{
		mouse_enabled = false;
	}

	if( hMenuSettings[3] )
	{
		menu_move = true;
	}
	else
	{
		menu_move = false;
	}

	if( hMenuSettings[4] )
	{
		hMenu->DisableAllMenuItems();
		for (int i = 0; i <= ( ARRAYSIZE(hMenuItem) - 1 ); i++)
			hMenuItem[i] = 0;
		for (int i = 0; i <= ( ARRAYSIZE(hMenuFolder) - 1 ); i++)
			hMenuFolder[i] = 0;
		for (int i = 0; i <= ( ARRAYSIZE(hMenuSettings) - 1 ); i++)
			hMenuSettings[i] = 0;
	}

	if( hMenuSettings[5] )
	{
		ExitProcess(0);
	}
}
//=================================================================

void ValidateString(char* string, char original)
{
	memcpy(reinterpret_cast<void*>(string), reinterpret_cast<void*>(&original), 1);
}

void OverwriteString(char* target, char* source, uint32_t length)
{
	memcpy(reinterpret_cast<void*>(target), reinterpret_cast<void*>(source), length);
	memcpy(reinterpret_cast<void*>(target + length), reinterpret_cast<void*>("\x00"), 1);
}

void InvalidateString(char* string)
{
	ValidateString(string, 0);
}
void pFlyHackF(bool bEnable)
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
	DWORD pCLTPlayerClient = *(DWORD*)((CShell + 0x14FAD90) + 0x78);
	if (pCLTPlayerClient)
	{
		static bool bInit = false;
		static float old;
		if (!bInit && bEnable)
		{
			old = *(float*)(pCLTPlayerClient + 0xA60);
			bInit = true;
		}
		static bool bWasEnabled = false;
		if (bEnable)
		{
			*(float*)(pCLTPlayerClient + 0xA60) = -3.000f;
			bWasEnabled = true;
		}
		else if (bWasEnabled)
		{
			*(float*)(pCLTPlayerClient + 0xA60) = old;
			bWasEnabled = false;
		}
	}
}

//========================================
void hBuildHacks( LPDIRECT3DDEVICE9 pDevice )
{
	

	DWORD as12InGame = (DWORD)GetModuleHandleA("Object.dll");
	DWORD as12CShell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD as12_PlayerPointer = *(DWORD*)(as12CShell + asp12CLTPlayerClient + 0x78);
	DWORD cshell_base1 = (DWORD)GetModuleHandleA("CShell.dll");
	oas12GlowESP as12pSetGlowColor = (oas12GlowESP)((DWORD)as12CShell + as12GLOWESP);
	DWORD asp12HeadShotMgr = *(DWORD*)(as12CShell + as12ModelNode);
	DWORD as12_BasicPlayerInfo = *(DWORD*)(as12CShell + as12BasicPlayerInfo);
	//=========================
	
	

	/*int pView = 0;
	DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");
	cCamera* Camera = *(cCamera**)(CShell + PLAYERVIEW_POINTER);
	if (Camera != NULL)
	{
		if (hMenuItem[23] == 1)
		{
			if (GetAsyncKeyState('T') & 1)
			{
				pView = pView + 1;
			}
			if (pView == 1)
			{
				Camera->PlayerView = 3;	//Third Person View
				pView = pView + 1;
			}
		/*	if (pView == 3)
			{
				Camera->PlayerView = 2;	//Second Person View
				pView = pView + 1;
			}
			if (pView == 5)
			{
				Camera->PlayerView = 1;	//First Person View
				pView = 0;
			}
		}
	}*/
	//DWORD as12PlayerClient = *(DWORD*)(as12CShell + asp12CLTPlayerClient + 0x78);//39 ?? ?? 74 ?? 8B ?? ?? 8B 01 8B 90 ?? ?? ?? ?? FF D2
	/*DWORD asCShell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD aspLTModel = *(DWORD*)(asCShell + asLTModel);
	DWORD asInGame = (DWORD)GetModuleHandleA("Object.dll");
	DWORD aspPLAYERCLIENTBASE1 = *(DWORD*)(asCShell + asPLAYERCLIENTBASE);
	DWORD aspPLAYERCLIENTBASEOFFSET1 = *(DWORD*)(aspPLAYERCLIENTBASE1 + asPLAYERCLIENTBASEOFFSET);
	DWORD asZPlayerClient11 = *(DWORD*)(asCShell + aspCLTPlayerClient + 0x70);
	DWORD aspHeadShotMgr = *(DWORD*)(asCShell + asModelNode);
	DWORD asZPlayerClient1 = *(DWORD*)(asCShell + aspCLTPlayerClient + 0x70);
	DWORD ascshell_base = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD as_BasicPlayerInfo = *(DWORD*)(asCShell + asBasicPlayerInfo);
	DWORD as_PlayerPointer = *(DWORD*)(asCShell + aspCLTPlayerClient + 0x70);
	MemoryAdressen();*/
	/*bool as12PressingSpace1 = (bool)(GetAsyncKeyState('E'));
	bool as12PressedSpace1 = false;
	if (as12InGame)
	{
		if (hMenuItem[8] == 1 && as12_PlayerPointer != NULL)//wtw
		{
			if (as12PressingSpace1 && !as12PressedSpace1)
				for (int g = 0; g < 0xFFF; ++g)
				{
					if (*(float*)(as12_PlayerPointer + 160 * g / 40) == 56 * 7 / 7)
						*(float*)(as12_PlayerPointer + 160 * g / 40) = -56 * 7 / 7;
				}
		}
	}*/
	
	
	/*
	if (as12_PlayerPointer != NULL)
	{
		DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
		DWORD UnliBag = *(DWORD*)(*(DWORD*)(CShell + 0x1526357 + 0x1) + 0x18); // 11526357   . 0000            ADD BYTE PTR DS:[EAX],AL


		if (as12_PlayerPointer && GetAsyncKeyState('B') && hMenuItem[41] == 1)
		{
			*(DWORD*)(UnliBag + 0xC) = 0;
		}
	}
	*/
	/*if (as12InGame)
	{
		if (hMenuItem[9] == 1)
		{
			static uint32_t addresses[] =
			{
				0xF60C24, 0xF42C4C, 0xF42C40, 0xF42B78, 0xF60C1C,
				0xF42C30, 0xF42C20, 0xF42B68, 0xF60C10, 0xF42C10,
				0xF42C00, 0xF42B58, 0x275064, 0xF42B40, 0xF50E10,
				0xF50E08, 0xEDAF00
			};

			for (uint32_t i = 0; i < sizeof(addresses) / sizeof(uint32_t); i++)
			{
				InvalidateString(reinterpret_cast<char*>(cshell_base1 + addresses[i]));
			}

			// M-idle
			OverwriteString(reinterpret_cast<char*>(cshell_base1 + 0x297E44), "M-c-SBdown_d", 12);
		}
		if (hMenuItem[9] == 0)
		{
			static uint32_t addresses[] =
			{
				0xF60C24, 0xF42C4C, 0xF42C40, 0xF42B78, 0xF60C1C,
				0xF42C30, 0xF42C20, 0xF42B68, 0xF60C10, 0xF42C10,
				0xF42C00, 0xF42B58, 0x275064, 0xF42B40, 0xF50E10,
				0xF50E08, 0xEDAF00
			
				
			};

			for (uint32_t i = 0; i < sizeof(addresses) / sizeof(uint32_t); i++)
			{
				ValidateString(reinterpret_cast<char*>(cshell_base1 + addresses[i]), 'M');
			}

			// M-idle F57464
			OverwriteString(reinterpret_cast<char*>(cshell_base1 + 0x297E44), "M-idle", 6);
		}

	}*/
	if (as12InGame)
	{
		if (hMenuItem[41] == 1)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0x8) = 1.40f;
		}
		if (hMenuItem[41] == 2)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0x8) = 1.70f;
		}
		if (hMenuItem[41] == 3)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0x8) = 2.00f;
		}
		if (hMenuItem[41] == 4)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0x8) = 2.50f;
		}
		if (hMenuItem[41] == 0)
		{
			*(float*)(as12_BasicPlayerInfo + 0x8) = 0.90f;
		}
		//=========================Crouch======================
		if (hMenuItem[42] == 1)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0xC) = 1.40f;
		}
		if (hMenuItem[42] == 2)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0xC) = 1.70f;
		}
		if (hMenuItem[42] == 3)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0xC) = 2.00f;
		}
		if (hMenuItem[42] == 4)//speeeeda
		{
			*(float*)(as12_BasicPlayerInfo + 0xC) = 2.50f;
		}
		if (hMenuItem[42] == 0)
		{
			*(float*)(as12_BasicPlayerInfo + 0xC) = 0.90f;
		}
		if (hMenuItem[19] == 1)
		{
			as12pSetGlowColor(true);

		}
		if (hMenuItem[19] == 0)
		{
			as12pSetGlowColor(false);
		}
		
	}
	/*
Hey Guys, this is a tutorial on finding the BagHack address.
All credits go to ACEOFEAGLE

Code:
Scan C7 ?? ?? ?? ?? ?? 89 48 ?? 89 48 ?? A3
1074EEF4  |.  C700 88ACDF10 mov     dword ptr [eax], 10DFAC88

Scan the bytes of the address (in this case, 88 AC DF 10)

Ctrl + L (2X)
You'll get to this line:

11268FFC     \88ACDF10      dd      Dumped_1.10DFAC88

Add 0x18 bytes and do baghack normally
	*/
    DWORD pCShell = (DWORD)GetModuleHandleA("CShell");
	DWORD Bag = *(DWORD*)(pCShell + 0x1526370);
	if (as12InGame)
	{
		if (Bag)
		{
			if (hMenuItem[29] == 1)
			{
				if (GetAsyncKeyState('B'))
					*(DWORD*)(Bag + 0xC) = 0;
			}
		}
	}
	
	if (as12_PlayerPointer != NULL)
	{
		*(float*)(as12_PlayerPointer + 0x620) = 0.0f;
		*(float*)(as12_PlayerPointer + 0x530) = 0.0f;
		*(float*)(as12_PlayerPointer + 0x600) = 0.0f;
		/*(float*)(as12CShell + as12DamageZone + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12DamagePerSec + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12VisibleZoneIndex + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12Eatman + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12EatmanName + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12versioncode + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12Zoneman + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12ZonemanName + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12Floor + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12FloorNameMsgIndex + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12PointIndex + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + pEditPoly + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + pPolyList + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + pPointList + 0x4) = -99999999.0f && 'G';
		*(float*)(as12CShell + as12MaxDepth + 0x4) = -99999999.0f && 'G';*/
		/*(float*)(as12CShell + as12ZonemanName) = 0;
		*(float*)(as12CShell + as12VisibleZoneIndex) = 0;
		*(float*)(as12CShell + as12DamageZone) = 0;
		*(float*)(as12CShell + as12DamagePerSec) = 0;
		*(float*)(as12CShell + as12DamagePerMeter) = 0;
		*(float*)(as12CShell + as12Zoneman) = 0;
		*(float*)(as12CShell + as12Eatman) = 0;
		*(float*)(as12CShell + as12EatmanName) = 0;
		*(float*)(as12CShell + as12versioncode) = 0;
		*(float*)(as12CShell + as12TargetZone) = 0;
		*(float*)(as12CShell + as12Floor) = 0;
		*(float*)(as12CShell + as12world) = 0;
		*(float*)(as12CShell + as12Normal) = 0;
		*(float*)(as12CShell + as12MaxDepth) = 0;
		*(float*)(as12CShell + as12USE_DAMAGE_ZONE_VER1) = 0;
		*(float*)(as12CShell + as12FloorNameMsgIndex) = 0;


		*(float*)(as12CShell + pWorld_Target) = 0;
		*(float*)(as12CShell + pDist) = 0;
		*(float*)(as12CShell + pPointIndex) = 0;
		*(float*)(as12CShell + pPolyList) = 0;
		*(float*)(as12CShell + pPointList) = 0;
		*(float*)(as12CShell + pName) = 0;
		*(float*)(as12CShell + pheader) = 0;
		*(float*)(as12CShell + pPos) = 0;
		*(float*)(as12CShell + pRot) = 0;
		*(float*)(as12CShell + pZoneName) = 0;*/
		//*(float*)(as12_PlayerPointer + 0x5EC) = 0.0f;
	}
/*	if (as12_PlayerPointer != NULL)//fly
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			*(float*)(as12_PlayerPointer + 0xA4C) = -2.725f;
		}
		else
		{
			*(float*)(as12_PlayerPointer + 0xA4C) = 1;
		}
	}*/
	/*if (as12InGame)
	{
		if (hMenuItem[33] == 1 && as12_PlayerPointer != NULL)//fly
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				*(float*)(as12_PlayerPointer + 0xA4C) = -2.725f;
			}
			else
			{
				*(float*)(as12_PlayerPointer + 0xA4C) = 1;
			}
		}
	}*/
	if( hMenuItem[1] )//CrossHair
	{
		D3DVIEWPORT9 pViewport;
		pDevice->GetViewport(&pViewport);
		DWORD ScreenCenterX = pViewport.Width / 2;
		DWORD ScreenCenterY = pViewport.Height / 2;

		hMenu->hDrawRectangle(ScreenCenterX-15, ScreenCenterY-1, 11, 2, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0),pDevice);//Left line Border
		hMenu->hDrawBox(ScreenCenterX-14, ScreenCenterY, 10, 1,D3DXCOLOR(1.0, 0.0, 0.0, 1.0),pDevice);//Left line

		hMenu->hDrawRectangle(ScreenCenterX+4, ScreenCenterY-1, 11, 2, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0),pDevice);//Right line Border
		hMenu->hDrawBox(ScreenCenterX+5, ScreenCenterY, 10, 1,D3DXCOLOR(1.0, 0.0, 0.0, 1.0),pDevice);//Right line

		hMenu->hDrawRectangle(ScreenCenterX-1, ScreenCenterY-15, 2, 11, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0),pDevice);//Top line Border
		hMenu->hDrawBox(ScreenCenterX, ScreenCenterY-14, 1, 10,D3DXCOLOR(1.0, 0.0, 0.0, 1.0),pDevice);//Top line

		hMenu->hDrawRectangle(ScreenCenterX-1, ScreenCenterY+4, 2, 11, 1, D3DXCOLOR(0.0, 0.0, 0.0, 1.0),pDevice);//Bottom line Border
		hMenu->hDrawBox(ScreenCenterX, ScreenCenterY+5, 1, 10,D3DXCOLOR(1.0, 0.0, 0.0, 1.0),pDevice);//Bottom line

		hMenu->hDrawRectangle(ScreenCenterX-1,ScreenCenterY-1,2,2,1,D3DXCOLOR(0.0, 0.0, 0.0, 1.0),pDevice);//Point Border
		hMenu->hDrawBox(ScreenCenterX,ScreenCenterY,1,1,D3DXCOLOR(1.0, 0.0, 0.0, 1.0),pDevice);//Point
		
	}
	if (hMenuItem[21] = 1)
	{

	}
	else
	{

	}
	if (hMenuItem[18] == 1)
	{
		

			for (int i = 0; i < 3; i++)
			{
				a12ModelNodes* wNode1 = (a12ModelNodes*)(asp12HeadShotMgr + (i * 4));
				for (int g = 0; g < 3; g++)
					wNode1->dimension[g] = 160.0f;
			}

		
		

	}
	if (hMenuItem[18] == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			a12ModelNodes* wNode1 = (a12ModelNodes*)(asp12HeadShotMgr + (i * 4));
			for (int g = 0; g < 3; g++)
				wNode1->dimension[g] = 18.0f;
		}
	}
	
	
	/*if (hMenuItem[12] == 1 & 1)//wall
	{

		memcpy((PVOID)(as1WallArray + 0xA4), (PBYTE)"\x00\x00\x00\x00\x00\x00", 6);

	}
	else
	{

		memcpy((PVOID)(as1WallArray + 0xA4), (PBYTE)"\x90\x90\x90\x90\x90\x90", 6);
	}*/
	
	/*

	if (hMenuItem[12] == 1 & 1)//wall
	{

		memcpy((PVOID)(asWallArray + 0xA4), (PBYTE)"\x00\x00\x00\x00\x00\x00", 6);

	}
	else
	{

		memcpy((PVOID)(asWallArray + 0xA4), (PBYTE)"\x90\x90\x90\x90\x90\x90", 6);
	}
	if (asInGame)
	{
		if (hMenuItem[4] == 1)//speeeeda
		{
			*(float*)(as_BasicPlayerInfo + 0x8) = 1.40f;
		}
		if (hMenuItem[4] == 0)
		{
			*(float*)(as_BasicPlayerInfo + 0x8) = 0.90f;
		}
	}


	if (asInGame)
	{
		if (hMenuItem[29] == 1 && aspPLAYERCLIENTBASEOFFSET1 != NULL)//fly
		{
			if (GetAsyncKeyState(VK_SPACE))
			{
				*(float*)(aspPLAYERCLIENTBASEOFFSET1 + 0xA38) = -2.725f;
			}
			else
			{
				*(float*)(aspPLAYERCLIENTBASEOFFSET1 + 0xA38) = 1;
			}
		}
	}
		bool asPressingSpace1 = (bool)(GetAsyncKeyState('E'));
		bool asPressedSpace1 = false;
		if (asInGame)
		{
			if (hMenuItem[3] == 1 && as_PlayerPointer != NULL)//wtw
			{
				if (asPressingSpace1 && !asPressedSpace1)
					for (int k = 0; k < 0x1FF; ++k)
					{
						if (*(float*)(as_PlayerPointer + 32 * k / 8) == 56 * 3 / 3)
							*(float*)(as_PlayerPointer + 32 * k / 8) = -56 * 3 / 3;
					}
			}
		}
	
	if (hMenuItem[2] == 1)//spectator
	{
		CLTPlayerClient *pPlayer = (CLTPlayerClient *)(asCShell + aspCLTPlayerClient);

		if (pPlayer != NULL)
		{
			if (GetAsyncKeyState('T') & 1) am_PlayerView = !am_PlayerView;
			if (am_PlayerView)
			{
				pPlayer->pSpectator->Mode = 3;
				display = false;
			}
			else
			{
				if (!display)
				{
					pPlayer->pSpectator->Mode = 1;
					display = true;
				}
			}
		}
	}
	if (hMenuItem[28] == 1)
	{
		if (asInGame)
		{
			
			
			for (int i = 0; i < 3; i++)
			{
				aModelNodes* wNode1 = (aModelNodes*)(aspHeadShotMgr + (i * 4));
				for (int g = 0; g < 3; g++)
					wNode1->dimension[g] = 190.0f;
			}
		}

	}

	
	
	if (asZPlayerClient1 != NULL)
	{
		*(float*)(asZPlayerClient1 + 0x604) = 0.0f;
		*(float*)(asZPlayerClient1 + 0x5E4) = 0.0f;
		*(float*)(asZPlayerClient1 + 0x5F0) = 0.0f;
		*(float*)(asZPlayerClient1 + 0x5EC) = 0.0f;
	}
	
	if (ascshell_base)
	{
		if (hMenuItem[5] == 1)
		{
			static uint32_t addresses[] =
			{
				0xED31D0, 0xF42C4C, 0xF42C40, 0xF42B78, 0xF42BA0,
				0xF42C30, 0xF42C20, 0xF42B68, 0xF42B94, 0xF42C10,
				0xF42C00, 0xF42B58, 0xF42B34, 0xF42B40, 0xF50E10,
				0xF50E08, 0xEDAF00
			};

			for (uint32_t i = 0; i < sizeof(addresses) / sizeof(uint32_t); i++)
			{
				InvalidateString(reinterpret_cast<char*>(ascshell_base + addresses[i]));
			}

			// M-idle
			OverwriteString(reinterpret_cast<char*>(ascshell_base + 0xF57464), "M-c-SBdown_d", 12);
		}
		if (hMenuItem[5] == 0)
		{
			static uint32_t addresses[] =
			{
				0xED31D0, 0xF42C4C, 0xF42C40, 0xF42B78, 0xF42BA0,
				0xF42C30, 0xF42C20, 0xF42B68, 0xF42B94, 0xF42C10,
				0xF42C00, 0xF42B58, 0xF42B34, 0xF42B40, 0xF50E10,
				0xF50E08, 0xEDAF00
			};

			for (uint32_t i = 0; i < sizeof(addresses) / sizeof(uint32_t); i++)
			{
				ValidateString(reinterpret_cast<char*>(ascshell_base + addresses[i]), 'M');
			}

			// M-idle
			OverwriteString(reinterpret_cast<char*>(ascshell_base + 0xF57464), "M-idle", 6);
		}

	}
	if (asCShell != NULL)
	{
		DWORD adsLTClientShell = *(DWORD*)(asCShell + asLTClientShell); {
			if (adsLTClientShell != 0) {
				DWORD adsUnlimitedBag = *(DWORD*)(adsLTClientShell + 0xE920);
				if (adsUnlimitedBag != 0) {
					if (GetAsyncKeyState('B') && hMenuItem[41] == 1) {
						*(DWORD*)(adsUnlimitedBag + 0xC) = 0;
					}
				}
			}
		}
	}*/

	
}

/*void dmga()
{
	int lola = 1;
	DWORD as12CShell = (DWORD)GetModuleHandleA("CShell.dll");
	if (hMenuItem[8] == 1)
	{

		
		if (lola == 1)
		{

			*(float*)(as12CShell + as12versioncode) = 0;
			*(float*)(as12CShell + as12TargetZone) = 0;
			*(float*)(as12CShell + as12Floor) = 0;
			*(float*)(as12CShell + as12world) = 0;
			*(float*)(as12CShell + as12Normal) = 0;
			*(float*)(as12CShell + as12MaxDepth) = 0;
			*(float*)(as12CShell + as12USE_DAMAGE_ZONE_VER1) = 0;
			*(float*)(as12CShell + as12ZonemanName) = 0;
			*(float*)(as12CShell + as12VisibleZoneIndex) = 0;
			*(float*)(as12CShell + as12DamageZone) = 0;
			*(float*)(as12CShell + as12DamagePerSec) = 0;
			*(float*)(as12CShell + as12DamagePerMeter) = 0;
			*(float*)(as12CShell + as12Zoneman) = 0;
			*(float*)(as12CShell + as12Eatman) = 0;
			*(float*)(as12CShell + as12EatmanName) = 0;
		}

	}
}*/
/*#define lessrico1 0x500
#define lessrico2 0x5F0/*
void bbuggy()
{
	DWORD asCShell = (DWORD)GetModuleHandleA("CShell.dll");
	int bbu = 1;
	/*if (hMenuItem[15] == 0)
	{
		if (asCShell != NULL)
		{
			if (bbu == 1)
			{
				*(float*)(asCShell + asversioncode) = 0;
				*(float*)(asCShell + asTargetZone) = 0;
				*(float*)(asCShell + asFloor) = 0;
				*(float*)(asCShell + asworld) = 0;
				*(float*)(asCShell + asNormal) = 0;
				*(float*)(asCShell + asMaxDepth) = 0;
				*(float*)(asCShell + asUSE_DAMAGE_ZONE_VER1) = 0;
				*(float*)(asCShell + asZonemanName) = 0;
				*(float*)(asCShell + asVisibleZoneIndex) = 0;
				*(float*)(asCShell + asDamageZone) = 0;
				*(float*)(asCShell + asDamagePerSec) = 0;
				*(float*)(asCShell + asDamagePerMeter) = 0;
				*(float*)(asCShell + asZoneman) = 0;
				*(float*)(asCShell + asEatman) = 0;
				*(float*)(asCShell + asEatmanName) = 0;
			}
		}
	}*/
	int ri = 1;
	/*DWORD asZPlayerClient12 = *(DWORD*)(asCShell + aspCLTPlayerClient + 0x70);
	if (hMenuItem[21] == 0)
	{
		if (asZPlayerClient12 != NULL)
		{
			if (ri == 1)
			{
				*(float*)(asZPlayerClient12 + lessrico1) = 0.0f;
				*(float*)(asZPlayerClient12 + lessrico2) = 0.0f;

			}

		}
	}
}*/

	bool isGameReadyF0rHook()
	{
		if (GetModuleHandleA("CShell.dll") != NULL && GetModuleHandleA("ClientFx.fxd") != NULL)
			return true;
		return false;
	}


	void Animations()
	{
		if (!isGameReadyF0rHook()) return;

		DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
		//================Anti Send Error Report===============//
		DWORD crossfire = (DWORD)GetModuleHandleA(eCF);
		if (crossfire == NULL) return;

		//=============Invisible==================//
		if (hMenuItem[49] == 1)
		{
			char* text1 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mwait0), text1, strlen(text1));
			char* text2 = "M-combo_Bighead";//M-RM-B-UBdown | M-RM-B-LBdown
			OverwriteString(reinterpret_cast<char*>(CShell + Midle), text2, strlen(text2));
			char* text3 = "M-combo_Bighead";
			OverwriteString(reinterpret_cast<char*>(CShell + Midle1), text3, strlen(text3));
			char* text4 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkRside), text4, strlen(text4));
			char* text5 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkLside), text5, strlen(text5));
			char* text6 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkRside), text6, strlen(text6));
			char* text7 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkLside), text7, strlen(text7));
			char* text8 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mrun), text8, strlen(text8));
			char* text9 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunBside), text9, strlen(text9));
			char* text10 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mwalk), text10, strlen(text10));
			char* text11 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkBside), text11, strlen(text11));
			char* text12 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mcwalk), text12, strlen(text12));
			char* text13 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkBside), text13, strlen(text13));
			char* text14 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MJump), text14, strlen(text14));
			char* text15 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mcidle), text15, strlen(text15));
			char* text16 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Midleup), text16, strlen(text16));
			char* text17 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunLside), text17, strlen(text17));
			char* text18 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunRside), text18, strlen(text18));
			char* text19 = "M-combo_Bighead";
			OverwriteString(reinterpret_cast<char*>(CShell + midle), text19, strlen(text19));
			char* text20 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mhit01), text20, strlen(text20));
			char* text21 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + Mhit02), text21, strlen(text21));
			char* text22 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + MSuperjump), text22, strlen(text22));
			char* text23 = "Unknown";
			OverwriteString(reinterpret_cast<char*>(CShell + McSuperjump), text23, strlen(text23));
		}
		else
		{
			char* text1 = "M-wait0";
			OverwriteString(reinterpret_cast<char*>(CShell + Mwait0), text1, strlen(text1));
			char* text2 = "M-idle";
			OverwriteString(reinterpret_cast<char*>(CShell + Midle), text2, strlen(text2));
			char* text3 = "M-idle1";
			OverwriteString(reinterpret_cast<char*>(CShell + Midle1), text3, strlen(text3));
			char* text4 = "M-walk-Rside";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkRside), text4, strlen(text4));
			char* text5 = "M-walk-Lside";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkLside), text5, strlen(text5));
			char* text6 = "M-c-walk-Rside";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkRside), text6, strlen(text6));
			char* text7 = "M-c-walk-Lside";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkLside), text7, strlen(text7));
			char* text8 = "M-run";
			OverwriteString(reinterpret_cast<char*>(CShell + Mrun), text8, strlen(text8));
			char* text9 = "M-run-Bside";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunBside), text9, strlen(text9));
			char* text10 = "M-walk";
			OverwriteString(reinterpret_cast<char*>(CShell + Mwalk), text10, strlen(text10));
			char* text11 = "M-walk-Bside";
			OverwriteString(reinterpret_cast<char*>(CShell + MwalkBside), text11, strlen(text11));
			char* text12 = "M-c-walk";
			OverwriteString(reinterpret_cast<char*>(CShell + Mcwalk), text12, strlen(text12));
			char* text13 = "M-c-walk-Bside";
			OverwriteString(reinterpret_cast<char*>(CShell + McwalkBside), text13, strlen(text13));
			char* text14 = "M-Jump";
			OverwriteString(reinterpret_cast<char*>(CShell + MJump), text14, strlen(text14));
			char* text15 = "M-c-idle";
			OverwriteString(reinterpret_cast<char*>(CShell + Mcidle), text15, strlen(text15));
			char* text16 = "M-idle-up";
			OverwriteString(reinterpret_cast<char*>(CShell + Midleup), text16, strlen(text16));
			char* text17 = "M-run-Lside";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunLside), text17, strlen(text17));
			char* text18 = "M-run-Rside";
			OverwriteString(reinterpret_cast<char*>(CShell + MrunRside), text18, strlen(text18));
			char* text19 = "m-idle";
			OverwriteString(reinterpret_cast<char*>(CShell + midle), text19, strlen(text19));
			char* text20 = "M-hit01";
			OverwriteString(reinterpret_cast<char*>(CShell + Mhit01), text20, strlen(text20));
			char* text21 = "M-hit02";
			OverwriteString(reinterpret_cast<char*>(CShell + Mhit02), text21, strlen(text21));
			char* text22 = "M-Superjump";
			OverwriteString(reinterpret_cast<char*>(CShell + MSuperjump), text22, strlen(text22));
			char* text23 = "M-c-Superjump";
			OverwriteString(reinterpret_cast<char*>(CShell + McSuperjump), text23, strlen(text23));
		}
	}

	