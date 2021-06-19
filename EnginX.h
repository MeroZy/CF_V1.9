
#define GetPlayerByIndex(LTClientShell, dwID) (CPlayer*)(LTClientShell + (dwID * 0xD80) + 0x208)

IntersectQuery iQuery;
IntersectInfo iInfo;

typedef bool(__cdecl *_IntersectSegment)(const IntersectQuery &Query, IntersectInfo *pInfo);
_IntersectSegment IntersectSegment;
typedef unsigned int uint32_t;
bool IsGameReadyForHookPoint()
{
	if (GetModuleHandleA(eCShell) != NULL && GetModuleHandleA("crossfire.exe") != NULL && GetModuleHandleA(eClient) != NULL && GetModuleHandleA("D3D9.DLL") != NULL)
		return true;
	return false;
}

bool isValidClient(CPlayer* Clients)
{
	if ((Clients != NULL) && (Clients->Health > 0) && (strlen(Clients->Name) > 2) && (Clients->Object != NULL))
		return true;
	return false;
}

D3DXVECTOR3 GetMidPoint(D3DXVECTOR3 V1, D3DXVECTOR3 V2)
{
	return D3DXVECTOR3((V1.x + V2.x) / 2, (V1.y + V2.y) / 2, (V1.z + V2.z) / 2);
}

char GetMyIndex(DWORD pLTCLientShell)
{
	if (pLTCLientShell)
	{
		BYTE clients = *(BYTE*)(pLTCLientShell + 0x208);
		if (clients < 16)
			return *(char*)(pLTCLientShell + clients * 0xD80 + 0x214);
	}
	return -1;
}

bool inGame()
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
	DWORD pLTClientShell = *(DWORD*)(CShell + 0x14B04B0);
	CPlayer* player = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));
	if ((player != NULL) && (strlen(player->Name) > 2) && (player->Object != NULL))
		return true;
	return false;
}

bool IsTM(CPlayer* Me, CPlayer* Target)
{
	if (Me->TeamID != Target->TeamID)
		return false;
	return true;
}

void GetBonePositionEx(cObject* obj, UINT Bone, _Transform* Trans)  // by ~FALLEN~ //
{
	DWORD CShell = (DWORD)GetModuleHandleA(eCShell);
	DWORD pLTModel = *(DWORD*)(CShell + 0x14AB79C);

	__asm
	{
		MOV ECX, pLTModel
			MOV EDX, DWORD PTR DS : [ECX]
			MOV EDX, DWORD PTR DS : [EDX + 0x3C]
			PUSH 1
			PUSH Trans
			PUSH Bone
			PUSH obj
			CALL EDX
	}
}

D3DXVECTOR3 GetBonePosition(cObject* obj, UINT Bone)
{
	_Transform Trans;
	GetBonePositionEx(obj, Bone, &Trans);
	return (Trans.Pos);
}

void GetNodePosition(cObject* obj, UINT Bone, D3DXVECTOR3 &Out)
{
	_Transform Trans;
	GetBonePositionEx(obj, Bone, &Trans);
	Out = Trans.Pos;
	Out.y += 5;
}

float CalculateDistance(D3DXVECTOR3 from, D3DXVECTOR3 to)
{
	return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y) + (to.z - from.z) * (to.z - from.z));
}
float CalculateDistance2(LTVector from, LTVector to)
{
	return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y) + (to.z - from.z) * (to.z - from.z));
}

bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 *InOut)
{
	D3DXVECTOR3 vScreen;
	D3DXVECTOR3 PlayerPos(InOut->x, InOut->y, InOut->z);
	D3DVIEWPORT9 viewPort = { 0 };
	D3DXMATRIX projection, view, world;
	pDevice->GetTransform(D3DTS_VIEW, &view);
	pDevice->GetTransform(D3DTS_PROJECTION, &projection);
	pDevice->GetTransform(D3DTS_WORLD, &world);
	pDevice->GetViewport(&viewPort);
	D3DXVec3Project(&vScreen, &PlayerPos, &viewPort, &projection, &view, &world);
	if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < viewPort.Width && vScreen.y < viewPort.Height)
	{
		*InOut = vScreen;
		return true;
	}
	return false;
}

/*bool __cdecl IsVisible(D3DXVECTOR3 MePos, D3DXVECTOR3 TargetPos)
{
IntersectSegment = (_IntersectSegment)(AaadaIntersectSegment);

if (IntersectSegment != NULL)
{
iQuery.From = MePos;
iQuery.To = TargetPos;
return !IntersectSegment(iQuery, &iInfo);
}
return false;
}*/
