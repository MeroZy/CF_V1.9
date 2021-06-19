#ifndef _CLASS_H_
#define _CLASS_H_


enum GradientOrientation
{
	Horizontal,
	Vertical
};

class LTVector
{
public:
	float x, y, z;
};
class LTRotation
{
public:
	float x, y, z, w;
};
class LTObject
{
public:
	char _0x0000[4];
	LTVector BoxMin; //0x0004 
	LTVector BoxMax; //0x0010 
	char _0x001C[128];
	LTVector Scale; //0x009C 
	char _0x00A8[4];
	unsigned int Type; //0x00AC 
	char _0x00B0[8];
	LTVector Dimentions; //0x00B8 
	char _0x00C4[12];
	LTVector ModelCullingPosition; //0x00D0 
	char _0x00DC[4];
	LTVector Position; //0x00E0 
	LTRotation Rotation; //0x00EC 
	LTVector Velocity; //0x00FC 
	LTVector GlobalForceOverride; //0x0108 
	char _0x0114[8];
	LTVector Acceleration; //0x011C 
};//Size=0x0128

struct cObject
{
public:
	char Spacer[4];
	D3DXVECTOR3 Body;
	D3DXVECTOR3 Foot;
	D3DXVECTOR3 Head;
};

typedef bool(*ObjectFilterFn1)(cObject* hObj, void *pUserData);

struct _Transform
{
	D3DXVECTOR3 Pos;
	unsigned char spacer00[0x100];
};

class CLTPlayerClient
{
public:
	char Spacer[0x4F4];
	_Transform* pPlayerPos;//0x4F4
	_Transform* pZMPos;//4F8
	char _0x04FC[4];
	float Yaw;//0x500
	float Pitch;//0x504
	float Roll;//0x508
	char spacer3[0x868];//50A + 856
	float NPitch;
	float NYaw;
	float NRoll;
};

class CPlayer
{
public:
char _0x0000[8];
	cObject *Object; //0x0008 
	BYTE ClientID; //0x000C 
	BYTE TeamID; //0x000D 
	char Name[12]; //0x000E 
	int Rank;
char _0x0016[2];
char _0x001C[8];
	BYTE got_C4; //0x0028 
char _0x0025[27];
	BYTE Health; //0x0044 
char _0x003F[3387];
};//Size=0x0D80

	class CCameraBase
{
public:
	/*char _0x0000[100];
	__int32 Camera; //0x0064 */
	char _0x0000[12];
	__int32 Mirror; //0x000C
	char _0x0010[84];
	__int32 Camera; //0x0064
};//Size=0x0068

struct IntersectInfo
{
	D3DXVECTOR3 vImpactPos;	//0x0000
	char _UnkSpace[16];			//SPACE
	cObject* hObjImpact;	//0x001C
	DWORD m_hPoly;			//0x0020
	DWORD m_SurfaceFlags;	//0x0024
	DWORD m_hNode;			//0x0028
};

struct IntersectQuery
{
	D3DXVECTOR3 From;					//0x0000
	D3DXVECTOR3 To;						//0x000C
	char _UnkSpace[12];						//SPACE
	unsigned int Flags;					//0x0024
	ObjectFilterFn1 FilterFn;			//0x0028
	void* FilterIntersectParam;			//0x002C
	ObjectFilterFn1 FilterIntersectFn;	//0x0030
	void* FilterParam;					//0x0034
	void* PolyFilterParam;				//0x0038
};

static char* ranks[] =
{
	"Trainee 1"            ,
	"Trainee 2"            ,
	"Private"              ,
	"PFC"                  ,
	"Corporal"             ,
	"Sergeant 1"           ,
	"Sergeant 2"           ,
	"Sergeant 3"           ,
	"Sergeant 4"           ,
	"Staff Sergeant 1"     ,
	"Staff Sergeant 2"     ,
	"Staff Sergeant 3"     ,
	"Staff Sergeant 4"     ,
	"Staff Sergeant 5"     ,
	"Staff Sergeant 6"     ,
	"SFC 1"                ,
	"SFC 2"                ,
	"SFC 3"                ,
	"SFC 4"                ,
	"SFC 5"                ,
	"SFC 6"                ,
	"Master Sergeant 1"    ,
	"Master Sergeant 2"    ,
	"Master Sergeant 3"    ,
	"Master Sergeant 4"    ,
	"Master Sergeant 5"    ,
	"Master Sergeant 6"    ,
	"2nd Lieutenant 1"     ,
	"2nd Lieutenant 2"     ,
	"2nd Lieutenant 3"     ,
	"2nd Lieutenant 4"     ,
	"2nd Lieutenant 5"     ,
	"2nd Lieutenant 6"     ,
	"2nd Lieutenant 7"     ,
	"2nd Lieutenant 8"     ,
	"1st Lieutenant 1"     ,
	"1st Lieutenant 2"     ,
	"1st Lieutenant 3"     ,
	"1st Lieutenant 4"     ,
	"1st Lieutenant 5"     ,
	"1st Lieutenant 6"     ,
	"1st Lieutenant 7"     ,
	"1st Lieutenant 8"     ,
	"Captain 1"            ,
	"Captain 2"            ,
	"Captain 3"            ,
	"Captain 4"            ,
	"Captain 5"            ,
	"Captain 6"            ,
	"Captain 7"            ,
	"Captain 8"            ,
	"Major 1"              ,
	"Major 2"              ,
	"Major 3"              ,
	"Major 4"              ,
	"Major 5"              ,
	"Major 6"              ,
	"Major 7"              ,
	"Major 8"              ,
	"Lieutenant Colonel 1" ,
	"Lieutenant Colonel 2" ,
	"Lieutenant Colonel 3" ,
	"Lieutenant Colonel 4" ,
	"Lieutenant Colonel 5" ,
	"Lieutenant Colonel 6" ,
	"Lieutenant Colonel 7" ,
	"Lieutenant Colonel 8" ,
	"Colonel 1"            ,
	"Colonel 2"            ,
	"Colonel 3"            ,
	"Colonel 4"            ,
	"Colonel 5"            ,
	"Colonel 6"            ,
	"Colonel 7"            ,
	"Colonel 8"            ,
	"Brigadiar General 1"  ,
	"Brigadiar General 2"  ,
	"Brigadiar General 3"  ,
	"Brigadiar General 4"  ,
	"Brigadiar General 5"  ,
	"Brigadiar General 6"  ,
	"Major General 1"      ,
	"Major General 2"      ,
	"Major General 3"      ,
	"Major General 4"      ,
	"Major General 5"      ,
	"Major General 6"      ,
	"Lieutenant General 1" ,
	"Lieutenant General 2" ,
	"Lieutenant General 3" ,
	"Lieutenant General 4" ,
	"Lieutenant General 5" ,
	"Lieutenant General 6" ,
	"General 1"            ,
	"General 2"            ,
	"General 3"            ,
	"General 4"            ,
	"General 5"            ,
	"General 6"            ,
	"Marshal"
};

#endif
