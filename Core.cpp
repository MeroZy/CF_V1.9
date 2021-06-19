#include "Core.h"
#include "Menu.h"
#include "Hacks.h"
#include "addrr.h"
#include "Class.h"
#include "Engine.h"
#include "ESP.h"
#include "Aimbot.h"
#include <cstdint>
#include <process.h>
#include "bypass.h"

#pragma comment(lib, "winmm.lib")

//Globals
hMenuCore *hMenu;

VOID hBuildItems( VOID )
{
	hMenu->AddGroup( "VISUAL", &hMenuFolder[1], hFld, 2 );
	if( hMenuFolder[1] )
	{
		hMenu->AddItem("CrossHair", &hMenuItem[1], hOpt, 2);
		hMenu->AddItem("WallHack", &hMenuItem[2], hOpt, 2);
		hMenu->AddItem("FullBright", &hMenuItem[3], hOpt, 2);
		hMenu->AddItem("Chams", &hMenuItem[58], cms, 6);
		hMenu->AddItem("Glow", &hMenuItem[19], hOpt, 2);
		hMenu->AddItem("Wireframe", &hMenuItem[4], hOpt, 2);
		hMenu->AddItem("Asus WallHack", &hMenuItem[5], hOpt, 2);
		hMenu->AddItem("X-Ray", &hMenuItem[6], hOpt, 2);
		hMenu->AddItem("NoFog", &hMenuItem[7], hOpt, 2);


	}
	hMenu->AddGroup("ESP", &hMenuFolder[4], hFld, 2);
	if (hMenuFolder[4])
	{
	//	hMenu->AddItem("Team ESP", &hMenuItem[70], hOpt, 2);
		hMenu->AddItem( "Name ESP", &hMenuItem[9], hOpt, 2 );
		//hMenu->AddItem("Box ESP (2D)", &hMenuItem[99], hOpt, 2);
		hMenu->AddItem( "Line ESP", &hMenuItem[10], hOpt, 2 );
		hMenu->AddItem( "Skeleton ESP", &hMenuItem[11], hOpt, 2 );
		hMenu->AddItem( "Distance ESP", &hMenuItem[12], hOpt, 2 );
		//hMenu->AddItem( "C4 ESP", &hMenuItem[13], hOpt, 2 );
	//	hMenu->AddItem( "Rank ESP", &hMenuItem[14], hOpt, 2 );
	//	hMenu->AddItem( "Health ESP", &hMenuItem[15], hOpt, 2 );
		hMenu->AddItem( "Box ESP", &hMenuItem[16], hOpt, 2 );
		hMenu->AddItem( "Visible Check", &hMenuItem[21], hAuto, 2 );
	}

	hMenu->AddGroup( "MEMORY", &hMenuFolder[2], hFld, 2 );
	if( hMenuFolder[2] )
	{
//	hMenu->AddItem("Fly [Space]", &hMenuItem[33], hOpt, 2);
	//hMenu->AddItem("WTW [E]", &hMenuItem[8], hOpt, 2);

	//hMenu->AddItem("ttesa", &hMenuItem[16], Dmg, 1);
	hMenu->AddItem("Speed Walk [L-Shift]", &hMenuItem[41], spd, 5);
	hMenu->AddItem("Speed Crouch [L-Ctrl]", &hMenuItem[42], spd, 5);
	hMenu->AddItem("SuperKill", &hMenuItem[18], hOpt, 2);
	hMenu->AddItem("Unlimited Bag [B]", &hMenuItem[29], hOpt, 2);
	hMenu->AddItem("Fly [Space]", &hMenuItem[37], hOpt, 2);
	//hMenu->AddItem("Spectator [T]", &hMenuItem[23], hOpt, 2);

	//	hMenu->AddItem("SuperKill", &hMenuItem[28], Jmp, 3);
	//	hMenu->AddItem("Fly [Space]", &hMenuItem[29], hOpt, 2);
		//hMenu->AddItem("WTW [E]"		,&hMenuItem[3]	,hOpt	,2);
		//hMenu->AddItem("Spectator [T]"		,&hMenuItem[2]	,hOpt	,2);
		//hMenu->AddItem("Speed [Shift]"		,&hMenuItem[4]	,hOpt	,2);
		////hMenu->AddItem("Unlimited Bag [B]", &hMenuItem[41], hOpt, 2);
		hMenu->AddItem("God Mode"		,&hMenuItem[49]	,hOpt	,2);
		hMenu->AddItem("Unlock All Mutants", &hMenuItem[21], hAuto, 2);
		hMenu->AddItem("No Recoil", &hMenuItem[21], hAuto, 2);
		hMenu->AddItem("No Spread", &hMenuItem[21], hAuto, 2);
		//hMenu->AddItem("No Ricole", &hMenuItem[21], Dmg, 1);
	//	hMenu->AddItem("No Zone/Bug Damage"		,&hMenuItem[15]	,Dmg	,1);*/
	}
/*	hMenu->AddGroup("VIP Weapons", &hMenuFolder[4], hFld, 2);
	if (hMenuFolder[4])
	{
		hMenu->AddItem("M4A1-S-G-Spirit", &hMenuItem[28], Dmg, 1);
		hMenu->AddItem("AK47-KnifeBornBeast", &hMenuItem[28], Dmg, 1);
		hMenu->AddItem("DesertEagleElDorado", &hMenuItem[28], Dmg, 1);
		hMenu->AddItem("Barrett-Iron-Shark", &hMenuItem[28], Dmg, 1);
	}*/
	/*hMenu->AddGroup("Aimbot", &hMenuFolder[5], hFld, 2);
	if (hMenuFolder[5])
	{
		hMenu->AddItem("Aimbot Key", &hMenuItem[51], Keys, 6);
		hMenu->AddItem("Aimbot Position", &hMenuItem[52], Aim, 8);
		hMenu->AddItem("Aimbot Near To", &hMenuItem[53], Nea, 2);
		hMenu->AddItem("Visible Check", &hMenuItem[54], Dmg, 1);
	}*/
	hMenu->AddGroup( "MISC", &hMenuFolder[3], hFld, 2 );
	if (hMenuFolder[3])
	{
		hMenu->AddItem("Mouse Control", &hMenuSettings[2], hOpt, 2);
		hMenu->AddItem("Move Menu", &hMenuSettings[3], hOpt, 2);
		hMenu->AddItem("Disable All Hacks", &hMenuSettings[4], hOpt, 2);
	}
}

#define  TBlack		D3DCOLOR_ARGB(170, 000, 000, 000)
#define  TRed		D3DCOLOR_ARGB(100, 255, 000, 000)
#define  Blue		D3DCOLOR_ARGB(255, 000, 000, 255)

static float		fFps				= NULL;
static float		fLastTickCount		= NULL;
static float		fCurrentTickCount;
static char			cFrameRate[50]		= {NULL};

void hBuildMenu( LPDIRECT3DDEVICE9 pDevice )
{
	if (!hMenu) 
	{	
		hMenu = new hMenuCore( "MeroZy V1.9", 100, 180, 15 );
		hMenu->visible=1;
		hMenu->col_title = hWhite;
	}else{
		if (!hMenu->noitems)
			hBuildItems();
		if (hMenu->visible==1)
		{
			//Title Box
			hMenu->hDrawBox((int)hMenu->x-7,(int)hMenu->y-4,(int)hMenu->totwidth,(float)18,hBlack,pDevice);
			hMenu->hDrawRectangle((int)hMenu->x-7,hMenu->y-4,(int)hMenu->totwidth,(float)18,1,hBlack,pDevice);

			//Item Box
			hMenu->hDrawBox((int)hMenu->x-7,(int)hMenu->y+15,(int)hMenu->totwidth,(float)hMenu->noitems*hMenu->height+12,0x8C000000,pDevice);
			hMenu->hDrawRectangle((int)hMenu->x-7,hMenu->y+15,(int)hMenu->totwidth,(float)hMenu->noitems*hMenu->height+12,1,hBlack,pDevice);

			//Credits Box

			fCurrentTickCount = clock() * 0.001f;
			++fFps;
			if((fCurrentTickCount - fLastTickCount) > 1.0f)
			{
				fLastTickCount = fCurrentTickCount;
				sprintf_s( cFrameRate, "FPS %d", int( fFps ) );
				fFps = 0;
			}

			hMenu->hDrawBox((int)hMenu->x-7,(int)(hMenu->y+hMenu->totheight)+11,(int)hMenu->totwidth,(float)18,TBlack,pDevice);
			hMenu->hDrawRectangle((int)hMenu->x-7,(hMenu->y+hMenu->totheight)+11,(int)hMenu->totwidth,(float)18,1,hBlack,pDevice);
			hMenu->DrawTextShadowC((int)hMenu->x+(hMenu->totwidth/2 - 5), hMenu->max_y+13, hLightBlue, cFrameRate, pFont);

			//Box 2
			hMenu->hDrawBox((int)hMenu->x-7,(int)(hMenu->y+hMenu->totheight)+33,(int)hMenu->totwidth,(float)18,TBlack,pDevice);
			hMenu->hDrawRectangle((int)hMenu->x-7,(hMenu->y+hMenu->totheight)+33,(int)hMenu->totwidth,(float)18,1,hBlack,pDevice);
			hMenu->DrawTextShadowC((int)hMenu->x+(hMenu->totwidth/2 - 5), hMenu->max_y+34, hLightBlue, "FB.com/groups/MeroZy", pFont);

			hMenu->hDrawBox((int)hMenu->x - 7, (int)(hMenu->y + hMenu->totheight) + 55, (int)hMenu->totwidth, (float)18, TBlack, pDevice);
			hMenu->hDrawRectangle((int)hMenu->x - 7, (hMenu->y + hMenu->totheight) + 55, (int)hMenu->totwidth, (float)18, 1, hBlack, pDevice);
			hMenu->DrawTextShadowC((int)hMenu->x + (hMenu->totwidth / 2 - 5), hMenu->max_y + 58, hLightBlue, "Credits: TheGeek", pFont);
		}
		/*else
		{
			hMenu->DrawTextShadowC(50,1, hGreen, "Put you text here", pFont);//50
		}*/
		hMenu->Show(pFont,pDevice);
		hMenu->Nav();
	}
}

/*HRESULT WINAPI hMyReset( LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters )
{
	pFont->OnLostDevice();
	HRESULT hTorna = hReset(pDevice, pPresentationParameters);
	if(SUCCEEDED(hTorna))
	{
		pFont->OnResetDevice();
	}

	return hTorna;
}*/



/*void Chams(LPDIRECT3DDEVICE9 D3DDEVICE, DWORD COLOR)
{
	D3DDEVICE->SetRenderState(D3DRS_AMBIENT, COLOR);
}
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}
void InstantChams(LPDIRECT3DDEVICE9 D3DDEVICE, LPDIRECT3DTEXTURE9 tCOLOR, DWORD COLOR)
{
	GenerateTexture(D3DDEVICE, &tCOLOR, COLOR);
	D3DDEVICE->SetTexture(0, tCOLOR);
}
LPDIRECT3DTEXTURE9 tRed;
LPDIRECT3DTEXTURE9 tYellow;
void Br(LPDIRECT3DDEVICE9 D3DDEVICE, DWORD VALUE)
{
	D3DDEVICE->SetRenderState(D3DRS_ZENABLE, VALUE);
}
HRESULT WINAPI myDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{

	if (pDevice->GetStreamSource(0, &StreamData, &OffsetInBytes, &m_Stride) == D3D_OK)
	{
		StreamData->Release();
	}

#define WARZ_HUMANS ( (m_Stride == 36) || (m_Stride == 32) || (m_Stride == 44) || (m_Stride == 40) )
	if (hMenuItem[12])//wall
	{
		Br(pDevice, D3DZB_FALSE);
	}
	if (hMenuItem[20])
	{
	if (hMenuItem[20] == 1)//map
	{
	InstantChams(pDevice, tRed, hRed);//Define tYellow like that: LPDIRECT3DTEXTURE9 tYellow;

	}
	if (hMenuItem[20] == 2)//map
	{
	InstantChams(pDevice, tYellow, hYellow);//Define tYellow like that: LPDIRECT3DTEXTURE9 tYellow;

	}
	if (hMenuItem[20] == 3)//map
	{
	InstantChams(pDevice, tYellow, hPink);//Define tYellow like that: LPDIRECT3DTEXTURE9 tYellow;

	}
	if (hMenuItem[20] == 4)//map
	{
	InstantChams(pDevice, tYellow, hGreen);//Define tYellow like that: LPDIRECT3DTEXTURE9 tYellow;

	}
	if (hMenuItem[20] == 5)//map
	{
	InstantChams(pDevice, tYellow, hBlue);//Define tYellow like that: LPDIRECT3DTEXTURE9 tYellow;

	}

	}
	if (hMenuItem[19])//WallHack
	{
		if (hMenuItem[19] == 1)//WallHack
		{
			if (WARZ_HUMANS)
			{
				Chams(pDevice, hRed);

			}
		}
		if (hMenuItem[19] == 2)//WallHack
		{
			if (WARZ_HUMANS)
			{
				Chams(pDevice, hYellow);

			}
		}
		if (hMenuItem[19] == 3)//WallHack
		{
			if (WARZ_HUMANS)
			{
				Chams(pDevice, hPink);

			}
		}
		if (hMenuItem[19] == 4)//WallHack
		{
			if (WARZ_HUMANS)
			{
				Chams(pDevice, hGreen);

			}
		}
		if (hMenuItem[19] == 5)//WallHack
		{
			if (WARZ_HUMANS)
			{
				Chams(pDevice, hBlue);

			}
		}
	}
	if (hMenuItem[13])//WireFrame
	{
		if (WARZ_HUMANS)
		{
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{
			pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}

	if (hMenuItem[14])//FullBright
	{
		if (WARZ_HUMANS)
		{
			pDevice->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
		}
	}
	return pDrawIndexedPrimitive(pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}*/
HRESULT _stdcall my_Present(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	DWORD InGame = (DWORD)GetModuleHandleA("Object.dll");

	hCreateFont(pDevice);
	hBuildMenu(pDevice);
	hBuildHacks(pDevice);
	pFlyHackF(hMenuItem[37] && GetAsyncKeyState(VK_SPACE));
	unlockallmutants();
	AaaadPlayerESP(pDevice);
	if (isGameReadyF0rHook())
	{
		Animations();
		
	}

	
	
	
	
	

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return pPresent(pDevice, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

__declspec(naked) DWORD __stdcall D3DXCreateFont(DWORD A, DWORD B, DWORD C, DWORD D, DWORD E, DWORD F, DWORD G, DWORD H, DWORD I, DWORD J, DWORD K, DWORD L)
{
	__asm
	{
		MOV EDI, EDI
			PUSH EBP
			MOV EBP, ESP
			jmp org_scp
	}
}


__declspec(naked) HRESULT WINAPI DrawIndexedPrimitive_1(void)
{
	static LPDIRECT3DDEVICE9 pDevice;
	static D3DPRIMITIVETYPE Type;
	static INT BaseVertexIndex;
	static UINT MinVertexIndex, NumVertices, startIndex, primCount;

	__asm
	{
		mov eax, [eax + 0x148]
			mov[primCount], edi
			push edi
			mov[startIndex], ecx
			push ecx
			mov[NumVertices], ebp
			push ebp
			mov[MinVertexIndex], edx
			push edx
			push 0
			push 4
			mov[pDevice], ebx
			push ebx
			pushad
	}

	if (hMenuItem[2])
	{
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);// WallHack
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	if (hMenuItem[5]) // Asus WallHack
	{
		pDevice->SetRenderState(D3DRS_SRCBLEND, 3);
		pDevice->SetRenderState(D3DRS_DESTBLEND, 4);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	}

	if (hMenuItem[4]) //WireFrame
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (hMenuItem[3]) //FullBright
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, false); //d3d lighting off
		pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255)); // use all colors to glow up the lighting ingame
	}

	if (hMenuItem[6]) //X-Ray

		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	if (hMenuItem[7])
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //No Fog
	}
	if (hMenuItem[58])//WallHack
	{
		if (hMenuItem[58] == 1)//WallHack
		{
			pDevice->SetRenderState(D3DRS_AMBIENT, hRed);



		}
		if (hMenuItem[58] == 2)//WallHack
		{
			pDevice->SetRenderState(D3DRS_AMBIENT, hYellow);
			//Chams(pDevice, hYellow);


		}
		if (hMenuItem[58] == 3)//WallHack
		{
			pDevice->SetRenderState(D3DRS_AMBIENT, hPink);
			//Chams(pDevice, hPink);


		}
		if (hMenuItem[58] == 4)//WallHack
		{
			
			pDevice->SetRenderState(D3DRS_AMBIENT, hGreen);
			//Chams(pDevice, hGreen);

		}

		if (hMenuItem[58] == 5)//WallHack
		{
			
			pDevice->SetRenderState(D3DRS_AMBIENT, hBlue);
			//Chams(pDevice, hBlue);


		}
	}


	__asm
	{
		popad
			mov edx, ADDR_DIPENGINE_1
			add edx, 0x0F
			jmp edx
	}
}

__declspec(naked) HRESULT WINAPI DrawIndexedPrimitive_2(void)
{
	static LPDIRECT3DDEVICE9 pDevice;
	static UINT NumVertices, primCount;

	__asm
	{
		mov ecx, [eax + 0x148]
			mov[primCount], ebp
			push ebp
			push 0
			mov[NumVertices], ebx
			push ebx
			push 0
			push 0
			push 4
			mov[pDevice], edi
			push edi
			pushad
	}

	if (hMenuItem[2])
	{
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);// WallHack
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	if (hMenuItem[5]) // Asus WallHack
	{
		pDevice->SetRenderState(D3DRS_SRCBLEND, 3);
		pDevice->SetRenderState(D3DRS_DESTBLEND, 4);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	}

	if (hMenuItem[4]) //WireFrame
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	if (hMenuItem[3]) //FullBright
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, false); //d3d lighting off
		pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255, 255, 255, 255)); // use all colors to glow up the lighting ingame
	}

	if (hMenuItem[6]) //X-Ray

		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	if (hMenuItem[7])
	{
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE); //No Fog
	}

	__asm
	{
		popad
			mov eax, ADDR_DIPENGINE_2
			add eax, 0x11
			jmp eax
	}
}


DWORD WINAPI dwStartHook(void *)
{
	while ((memcmp((void *)ADDR_DIPENGINE_1, "\x8B", 1) && // da jmp memcpy famlo4 lazma
		(memcmp((void *)ADDR_DIPENGINE_2, "\x8B", 1))))
		Sleep(10);

	*(BYTE  *)(ADDR_DIPENGINE_1 + 0x00) = 0xE9;
	*(DWORD *)(ADDR_DIPENGINE_1 + 0x01) = ((DWORD)DrawIndexedPrimitive_1 - ADDR_DIPENGINE_1) - 5;
	*(BYTE  *)(ADDR_DIPENGINE_1 + 0x05) = 0x90;

	*(BYTE  *)(ADDR_DIPENGINE_2 + 0x00) = 0xE9;
	*(DWORD *)(ADDR_DIPENGINE_2 + 0x01) = ((DWORD)DrawIndexedPrimitive_2 - ADDR_DIPENGINE_2) - 5;
	*(BYTE  *)(ADDR_DIPENGINE_2 + 0x05) = 0x90;

	return 0;
}

DWORD __stdcall MyD3DXCreateFont(DWORD A, DWORD B, DWORD C, DWORD D, DWORD E, DWORD F, DWORD G, DWORD H, DWORD I, DWORD J, DWORD K, DWORD L)
{
	DWORD thisa = *(DWORD*)A;

	/*=====Present Hook=====*/
	DWORD oldflagES;
	DWORD ESAddress = thisa + 68;//17*4 Present 
	DWORD ESHook = *(DWORD*)ESAddress;
	retES = ESHook + 5;

	//ES Hook
	VirtualProtect((LPVOID)ESHook, 5, PAGE_EXECUTE_READWRITE, &oldflagES);
	*(PBYTE)ESHook = 0xE9;
	*(PULONG)(ESHook + 1) = (DWORD)my_Present - (ESHook + 5);
	/*=====Present Hook=====*/





	*(PULONG)(org_scp - 5) = 0x0000008b;
	*(PULONG)(org_scp - 4) = 0xEC8B55FF;

	return D3DXCreateFont(A, B, C, D, E, F, G, H, I, J, K, L);
}


UINT APIENTRY StartD3D(LPVOID param)
{
	DWORD OLD_Font;
	HMODULE user32 = LoadLibraryA(ed3d9_29);
	PVOID Address_Font = (PVOID)GetProcAddress(user32, eCreateFont);
	VirtualProtect(Address_Font, 5, PAGE_EXECUTE_READWRITE, &OLD_Font);
	org_scp = (DWORD)Address_Font + 0x5;
	*(PULONG)Address_Font = 0xE9;
	*(PULONG)((DWORD)Address_Font + 0x1) = (DWORD)MyD3DXCreateFont - ((DWORD)Address_Font + 0x5);
	return true;
}

UINT APIENTRY settingsThread(void *null)
{
	for (;;)
	{
		hSettings();
		Sleep(5);
	}
	Sleep(20);
}


typedef HRESULT(WINAPI* oEndScene)(LPDIRECT3DDEVICE9 pDevice);
oEndScene pEndScene = NULL;

HRESULT APIENTRY myEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	DWORD InGame = (DWORD)GetModuleHandleA("Object.dll");

	DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");

	DWORD CrOSS = (DWORD)GetModuleHandleA("Crossfire.exe");

	hCreateFont(pDevice);
	hBuildMenu(pDevice);
	//hBuildHacks(pDevice);




	return pEndScene(pDevice);
}


#include "D3DHook.h"


void* d3d9Device[119];
uintptr_t endSceneAddr;

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		endSceneAddr = (uintptr_t)d3d9Device[42];
		pEndScene = (oEndScene)TrampHook((char*)d3d9Device[42], (char*)myEndScene, 7);
		//hReset = (oReset)TrampHook((char*)d3d9Device[16], (char*)hMyReset, 7);
	}
	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpvReserved)
{

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		DisableThreadLibraryCalls(hModule);
		hEraseHeaders(hModule);
		hHideModule(hModule);
		//_beginthreadex(0, 0, StartD3D, 0, 0, 0);
		_beginthreadex(0, 0, settingsThread, 0, 0, 0);

		//MessageBoxA(0, "Use Hack After 5min ,after joining the channel \n + SuperKill [Fixed] \n - VIP Weapons [Removed] \n + Fly [Added]", "Don2a", 0);
		MessageBoxA(0, "Use Hack After 5min ,after joining the channel \n + Unlocked All Mutants \n [Buy Smoke Mutants From MP Shop to unlock all Mutants] \n + ESP [Name-Line-Distance-Box-More] \n - Distance ESP [May Cause Error]", "GG Ty", 0);
		//system("start https://www.facebook.com/groups/MeroZy/");
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, 0);
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return true;
}

#pragma endregion


