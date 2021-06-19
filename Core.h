#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma warning( disable: 4244 )

//Menu Items & Chars
int hMenuItem[100];
int hMenuFolder[40];
int hMenuSettings[10];

char* hOpt[] = { "OFF", "ON" };
char* Jmp[] = { "OFF", "High" ,"Ultra"};
char* hFld[] = { ">>", "<<" };
char *Folder[]	= {"", ""};
char *OnOff[]	= {"OFF", "ON"};
char *Dmg[]    = { "AUTO" };
char *hAuto[] = {"Off","Auto"};
char *Nea[] = { "CrossHair" ,"Player"};
char *cms[] = { "OFF", "Red", "Yellow", "Pink", "Green", "Blue" };
char *Aim[] = { "OFF", "Head", "Neck", "Body", "LHand", "RHand", "LFoot", "RFoot" };
char *spd[] = { "OFF", "x1", "x2", "x3", "Max"};
char *Keys[] = { "OFF", "AUTO", "LMOUSE", "RMOUSE", "SHIFT", "ALT" };
//Hooking
typedef HRESULT ( WINAPI* oPresent ) ( LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion);
oPresent hPresent;

typedef HRESULT (WINAPI* oReset) (LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
oReset hReset;

typedef HRESULT (WINAPI* oDrawIndexedPrimitive) (LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount);
oDrawIndexedPrimitive pDrawIndexedPrimitive;

DWORD org_scp = 0, retES = 0, jump_DrawIndexedPrimitive;

__declspec(naked) DWORD __stdcall pPresent(LPDIRECT3DDEVICE9 pDevice, CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	__asm
	{
		MOV EDI, EDI
			PUSH EBP
			MOV EBP, ESP
			jmp retES
	}
}

//Others
LPDIRECT3DDEVICE9 hDevice;
ID3DXFont *pFont;

void hCreateFont(LPDIRECT3DDEVICE9 pDevice)
{
	if(pFont == NULL)
	{
		D3DXCreateFont(pDevice, 14, 6, 750, 1, 0, 1, 0, 4, 0 | (0<<4), "Ariel", &pFont);
	}
	else
	{
		if(hDevice != pDevice)
		{
			hDevice = pDevice;

			try
			{
				if(pFont != 0) pFont->Release();

			} catch (...) {}

			pFont = 0;
			D3DXCreateFont(pDevice, 14, 6, 750, 1, 0, 1, 0, 4, 0 | (0<<4), "Ariel", &pFont);
		}
	}
}

DWORD hDetourCreate(DWORD DetourSrc, DWORD DetourtVlca, DWORD SizeDetour)
{
#define SizeDetour 5
	DWORD DetourPre, dwProtect, i;
	if (DetourSrc && DetourtVlca && SizeDetour == SizeDetour)
	{
		DetourPre = (DWORD)VirtualAlloc(NULL, SizeDetour + SizeDetour, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (DetourPre && VirtualProtect((VOID*)DetourSrc, SizeDetour, PAGE_EXECUTE_READWRITE, &dwProtect))
		{
			for (i = 0; i < SizeDetour; i++)
			{
				*(BYTE*)(DetourPre + i) = *(BYTE*)(DetourSrc + i);
			}
			*(BYTE*)(DetourPre + SizeDetour + 0) = 0x50;
			*(BYTE*)(DetourPre + SizeDetour + 0) = 0x58;
			*(BYTE*)(DetourPre + SizeDetour + 0) = 0xE9;
			*(DWORD*)(DetourPre + SizeDetour + 1) = (DetourSrc - DetourPre - SizeDetour);
			*(BYTE*)(DetourSrc + 0) = 0x50;
			*(BYTE*)(DetourSrc + 0) = 0x58;
			*(BYTE*)(DetourSrc + 0) = 0xE9;
			*(DWORD*)(DetourSrc + 1) = (DetourtVlca - DetourSrc - SizeDetour);
			VirtualProtect((VOID*)DetourSrc, SizeDetour, dwProtect, &dwProtect);
			VirtualProtect((VOID*)DetourPre, SizeDetour + SizeDetour, PAGE_EXECUTE_READ, &dwProtect);
			return DetourPre;
		}
	}
	return (0);
}

DWORD hD3D9VTable()
{
	DWORD dwObjBase = (DWORD)LoadLibraryA("D3D9.DLL");
	while (dwObjBase++ < dwObjBase + 0x127850)
	{
		if ((*(WORD*)(dwObjBase + 0x00)) == 0x06C7 && (*(WORD*)(dwObjBase + 0x06)) == 0x8689 && (*(WORD*)(dwObjBase + 0x0C)) == 0x8689)
		{
			dwObjBase += 2;
			break;
		}
	}
	return (dwObjBase);
}

void hEraseHeaders(HINSTANCE hModule)
{
	/* 
	* jus a func to erase headers by Croner.
	* keep in mind you wont be able to load 
	* any resources after you erase headers.
	*/

	PIMAGE_DOS_HEADER pDoH; 
	PIMAGE_NT_HEADERS pNtH;
	DWORD i, ersize, protect;

	if (!hModule) return;
	
	// well just to make clear what we doing
	pDoH = (PIMAGE_DOS_HEADER)(hModule);

	pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	ersize = sizeof(IMAGE_DOS_HEADER);
	if ( VirtualProtect(pDoH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pDoH + i) = 0;
	}

	ersize = sizeof(IMAGE_NT_HEADERS);
	if ( pNtH && VirtualProtect(pNtH, ersize, PAGE_READWRITE, &protect) )
	{
		for ( i=0; i < ersize; i++ )
				*(BYTE*)((BYTE*)pNtH + i) = 0;
	}
	return;
}


void hHideModule(HINSTANCE hModule)/*Credits to Thanatos aka Surpintine for his hide module function*/
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h]             
		mov eax, [eax+0Ch]               
		mov dwPEB_LDR_DATA, eax	

		InLoadOrderModuleList:
			mov esi, [eax+0Ch]	     
			mov edx, [eax+10h]	     

		LoopInLoadOrderModuleList: 
		    lodsd		         
			mov esi, eax	
			mov ecx, [eax+18h]  
			cmp ecx, hModule	
			jne SkipA		 
		    mov ebx, [eax]	  
		    mov ecx, [eax+4]  
		    mov [ecx], ebx    
		    mov [ebx+4], ecx	  
			jmp InMemoryOrderModuleList 

		SkipA:
			cmp edx, esi     
			jne LoopInLoadOrderModuleList

		InMemoryOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+14h]
			mov edx, [eax+18h]

		LoopInMemoryOrderModuleList: 
			lodsd
			mov esi, eax
			mov ecx, [eax+10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InInitializationOrderModuleList

		SkipB:
			cmp edx, esi
			jne LoopInMemoryOrderModuleList

		InInitializationOrderModuleList:
			mov eax, dwPEB_LDR_DATA
			mov esi, [eax+1Ch]	  
			mov edx, [eax+20h]	  

		LoopInInitializationOrderModuleList: 
			lodsd
			mov esi, eax		
			mov ecx, [eax+08h]
			cmp ecx, hModule		
			jne SkipC
			mov ebx, [eax] 
			mov ecx, [eax+4]
			mov [ecx], ebx
			mov [ebx+4], ecx
			jmp Finished

		SkipC:
			cmp edx, esi
			jne LoopInInitializationOrderModuleList

		Finished:
			popfd;
			popad;
	}
}
/**

void * WriteJump(BYTE * orig, BYTE * hook, int len)
{
	/*
	/	* Coders:          Hans211 , AeroMan
		* Original source: Hans211
		* Date of source:  10/04/2013
		* Release:         Private
	


	//We define some variables
	INT      dwSize    = 5;                                           //We define the size of the 'jmp'
	DWORD    dwProtect = 0;                                           //We define our variable where we store the protection value in
	BYTE     dwJmpByte = 233;                                         //We define our jump byte
	BYTE   * dwjmp     = (BYTE*)malloc(len + dwSize);                 //We allocate  the memory

	if(len > 5)                                                       //If our len is bigger then 5 we display a message
	{
		MessageBoxA(NULL, "There was entered an invalid detouring size!\nPlease try again with a lower size!", "API Detouring", MB_ICONERROR);
		ExitProcess(0);                                               //We exit the process
	}

	if(memcpy(dwjmp, orig, len == NULL))                              //If our bytes have not been written yet
	{
		VirtualProtect(orig, len, PAGE_READWRITE, &dwProtect);        //We change the protection state
		memcpy(dwjmp, orig, len); dwjmp += len;                       //We copy our bytes

		dwjmp[0] = dwJmpByte;                                         //We set the jump bytes (233)
		*(DWORD*)(dwjmp + 1) = (DWORD)(orig + len - dwjmp) - dwSize;  //We make our jump
		
		orig[0] = dwJmpByte;                                          //We set the jump bytes (233)
		*(DWORD*)(orig + 1) = (DWORD)(hook - orig) - dwSize;          //We make our jump
		VirtualProtect(orig, len, dwProtect, &dwProtect);             //We restore the protection state
	}
	return (dwjmp - len);                                             //We return our byte - the len
}*/

LPDIRECT3DVERTEXBUFFER9 StreamData;
UINT OffsetInBytes;
UINT m_Stride;