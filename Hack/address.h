#include <Windows.h>

// Others //
DWORD VisibleZoneIndex;
DWORD DamageZone;
DWORD DamagePerSec;
DWORD DamagePerMeter;

// Player Pointer //
DWORD aCLTPlayerClient;
DWORD ModelNode;

#define ADDR_DIPENGINE_1		0x004DBD46
#define ADDR_DIPENGINE_2		0x004D4AB4


#define IsInvi1 0xF42BA8 //                    ;  ASCII "M-run"
#define IsInvi2 0xF42C4C   //                  ;  ASCII "M-run-Rside"
#define IsInvi3 0xF42C40     //                ;  ASCII "M-run-Lside"
#define IsInvi4 0xF42B78       //              ;  ASCII "M-run-Bside"
#define IsInvi5 0xF42BA0         //            ;  ASCII "M-walk"
#define IsInvi6 0xF42C30           //          ;  ASCII "M-walk-Rside"
#define IsInvi7 0xF42C20             //        ;  ASCII "M-walk-Lside"
#define IsInvi8 0xF42B68            //         ;  ASCII "M-walk-Bside"
#define IsInvi9 0xF42B94             //        ;  ASCII "M-c-walk"
#define IsInvi10    0xF42C10      //               ;  ASCII "M-c-walk-Rside"
#define IsInvi11    0xF42C00       //              ;  ASCII "M-c-walk-Lside"
#define IsInvi12    0xF50DFC        //          ;  ASCII "M-idle-up"
#define IsInvi13    0xF42B34         //            ;  ASCII "M-c-idle"
#define IsInvi14    0xF42B40          //           ;  ASCII "M-jump"
#define IsInvi15    0xF50E10//                  ;  ASCII "M-hit02"
#define IsInvi16    0xF50E08 //                 ;  ASCII "M-hit01"
#define IsInvi17    0xF60D0C  //                   ;  ASCII "M-Superjump"
#define IsInvi18    0xF60CFC   //                  ;  ASCII "M-c-Superjump"
#define IsInvi19    0xEDAF00    //                 ;  ASCII "M-wait0"
#define IsInvi20    0xEDAFFC     //                ;  ASCII "M-idle"
#define IsInvi21    0xF57464      //               ;  ASCII "M-idle1"
#define IsInvi22    0xEDAEE4       //              ;  ASCII "m-idle"
#define IsInvi23    0xF50DFC        //          ;  ASCII "M-idle-up"
#define IsInvi24    0xF42B34 //                    ;  ASCII "M-c-idle"
#define IsInvi25    0xF42B78  //                   ;  ASCII "M-run-Bside"
#define IsInvi26    0xF42C40   //                  ;  ASCII "M-run-Lside"
#define IsInvi27    0xF42C4C    //                 ;  ASCII "M-run-Rside"
#define IsInvi28  0xF42C40//M-run-Lside

#define IsInvi29  0xF42C4C//M-run-Rside
#define IsInvi30  0xF42BA8//M-run*/





DWORD Mwait0 = 0xEDAF00;
DWORD MwalkRside = 0xF42C30;
DWORD MwalkLside = 0xF42C20;
DWORD McwalkRside = 0xF42C10;
DWORD McwalkLside = 0xF42C00;
DWORD Mrun = 0xF42BA8;
DWORD MrunBside = 0xF42B78;
DWORD Mwalk = 0xF42BA0;
DWORD MwalkBside = 0xF42B68;
DWORD Mcwalk = 0xF42B94;
DWORD McwalkBside = 0xF42B58;
DWORD MJump = 0xF42B40;
DWORD Mcidle = 0xF42B34;
DWORD Midleup = 0xF50DFC;
DWORD MrunLside = 0xF42C40;
DWORD MrunRside = 0xF42C4C;
DWORD Midle = 0xEDAFFC;
DWORD Midle1 = 0xF57464;
DWORD Mhit01 = 0xF50E08;
DWORD Mhit02 = 0xF50E10;
DWORD McSuperjump = 0xF60CFC;
DWORD MSuperjump = 0xF60D0C;
DWORD midle = 0xEDAEE4;
DWORD Mneckdown = 0xF7C648; // M-neck-down





bool loggadressen = false;
bool bCompare3(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == '0' && *pData != *bMask)
			return false;
	return (*szMask) == 0;
}
DWORD FindPattern3(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i<dwLen; i++)
		if (bCompare3((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
	return false;
}
bool bCompare2(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == '0' && *pData != *bMask)
			return false;
	return (*szMask) == 0;
}

DWORD FindPattern2(DWORD dwAddress, DWORD dwLen, BYTE *bMask, const char * szMask)
{
	for (DWORD i = 0; i<dwLen; i++)
		if (bCompare2((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
	return false;
}

void MemoryAdressen ()
{
	if(!loggadressen)
	{
		
		if(!GetModuleHandle("CShell.dll")) return;

		DWORD CShell = (DWORD)GetModuleHandle("CShell.dll");

		
		
		
		loggadressen = true;
	}
}

