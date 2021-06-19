
//----------------------------------------[ESP]------------------------------------------//
void WriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, CHAR *text)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);

	int g = 1;

	RECT rect1;
	SetRect(&rect1, x + g, y, x + g, y);
	RECT rect2;
	SetRect(&rect2, x - g, y, x - g, y);
	RECT rect3;
	SetRect(&rect3, x, y + g, x, y + g);
	RECT rect4;
	SetRect(&rect4, x, y - g, x, y - g);

	pFont->DrawTextA(NULL, text, -1, &rect1, DT_NOCLIP | DT_LEFT, hBlack);
	pFont->DrawTextA(NULL, text, -1, &rect2, DT_NOCLIP | DT_LEFT, hBlack);
	pFont->DrawTextA(NULL, text, -1, &rect3, DT_NOCLIP | DT_LEFT, hBlack);
	pFont->DrawTextA(NULL, text, -1, &rect4, DT_NOCLIP | DT_LEFT, hBlack);

	pFont->DrawText(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

bool Trans3DTo2D(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 *InOut)
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
struct D3DTLVERTEX
{
	float x, y, z, rhw;
	DWORD color;
};

void DrawLine(LPDIRECT3DDEVICE9 pDevice, float X, float Y, float X2, float Y2, DWORD dwColor)
{
	if (!pDevice) return;
	D3DTLVERTEX qV[2] =
	{
		{ (float)X, (float)Y, 0.0f, 1.0f, dwColor },
		{ (float)X2, (float)Y2, 0.0f, 1.0f, dwColor },
	};
	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, false);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, qV, sizeof(D3DTLVERTEX));
}
void DrawBone(LPDIRECT3DDEVICE9 pDevice, cObject *Obj, UINT iStart, UINT iEnd, D3DCOLOR Color)
{
	D3DXVECTOR3 StartPos, EndPos;
	GetNodePosition(Obj, iStart, StartPos);
	GetNodePosition(Obj, iEnd, EndPos);

	if (Trans3DTo2D(pDevice, &StartPos) && Trans3DTo2D(pDevice, &EndPos))
		DrawLine(pDevice, StartPos.x, StartPos.y, EndPos.x, EndPos.y, Color);
}

float CalculateDist(D3DXVECTOR3 from, D3DXVECTOR3 to)
{
	float _x, _y, _z;
	_x = to.x - from.x;
	_y = to.y - from.y;
	_z = to.z - from.z;
	return sqrt(_x*_x + _y*_y + _z*_z);
}


void FillRGB(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}
void DrawBorder(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, int px, D3DCOLOR BorderColor)
{
	FillRGB(pDevice, x, (y + h - px), w, px, BorderColor);
	FillRGB(pDevice, x, y, px, h, BorderColor);
	FillRGB(pDevice, x, y, w, px, BorderColor);
	FillRGB(pDevice, x + w - px, y, px, h, BorderColor);
}
bool IsValidCl1ent(CPlayer* Clients)
{
	if ((Clients != 0) && (Clients->Health >> 0))
		return true;
	return false;
}

void AaaadPlayerESP(LPDIRECT3DDEVICE9 pDevice)
{
	int len = 0;
	char pHEALTH[0x50];
	POINT pt;
	D3DVIEWPORT9 Viewport;
	pDevice->GetViewport(&Viewport);
	int PI2 = 6.283185307179586;
	DWORD x1 = Viewport.Width / 2;
	DWORD y1 = Viewport.Height / 2;
	pt.x = x1;
	pt.y = y1;
	if (!GetModuleHandle("CShell.dll")) return;
	if (!GetModuleHandle("ClientFx.fxd")) return;
	DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD InGame = (DWORD)GetModuleHandleA("Object.dll");

	DWORD pLTClientShell = *(DWORD*)(CShell + aLTClientShell);//

	if (pLTClientShell != NULL)
	{
		CPlayer* Me = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));

		for (int i = 0; i < 16; i++)
		{
			CPlayer* pPlayer = GetPlayerByIndex(pLTClientShell, i);
			if (IsValidCl1ent(pPlayer) && Me != pPlayer)
			{
				D3DXVECTOR3 Body = GetBonePosition(pPlayer->Object, 2);
				D3DXVECTOR3 Head = GetBonePosition(pPlayer->Object, 6);
				D3DXVECTOR3 Box = Body - Head; // Foot - Head
				if (Box.y < 0) Box.y *= -1;

				int HeadRadius = (int)Box.y * 1.5;

				DWORD ESP_Color = hGreen;
				DWORD healthcolor = 0xFF00FF00;

				if (pPlayer->Health > 80)
					healthcolor = 0xFF00FF00;
				else if (pPlayer->Health > 60)
					healthcolor = 0xFFFFFF00;
				else if (pPlayer->Health > 40)
					healthcolor = 0xFFFF4500;
				else
					healthcolor = 0xFFFF0000;

				int G = pPlayer->Health;

				if (Me->TeamID != pPlayer->TeamID)
					ESP_Color = hRed;
				else
					ESP_Color = hBlue;

				if (Trans3DTo2D(pDevice, &Body))
				{
					D3DVIEWPORT9 viewP;
					pDevice->GetViewport(&viewP);
					DWORD ScreenCenterX = viewP.Width / 2;
					DWORD ScreenCenterY = viewP.Height;

					char pNAME[10000];
					char szRank[100];
					char txt[0x30];
					char *HasC4 = "->Has C4<-";
					if (hMenuItem[10] == 1)
					{
						DrawLine(pDevice, ScreenCenterX, ScreenCenterY, Body.x, Body.y, ESP_Color);
						//DrawCircle(pt.x, pt.y, 18 * PI2,hRed, pDevice);
					}
					if (hMenuItem[9] == 1)
					{
						sprintf_s(pNAME, "Name: [%s]", (int)pPlayer->Name);
						WriteText(pDevice, Body.x + 20, Body.y - 50, hGreen, pNAME);
						//DrawCircle(pt.x, pt.y, 18 * PI2,hRed, pDevice);

					}/////
					if (hMenuItem[15] == 1)
					{
						sprintf_s(pHEALTH, "HP: %d", pPlayer->Health);
						len = strlen(pHEALTH);
						//DirectX->AddTextC(tBody.x - 6, tBody.y - 80, Yellow, TLeft, pFont, Health);
						WriteText(pDevice, Body.x - len * 2, Body.y + 100, ESP_Color, pHEALTH);

						//	DrawBorder(pDevice, Body.x, Body.y - 2, 41, 5, 1, ESP_Color);
						//FillRGB(pDevice, Body.x, Body.y - 1, G / 2.5, 3, healthcolor);
					}


					if (hMenuItem[13] == 1)
					{
						if (pPlayer->got_C4)

							WriteText(pDevice, Body.x + 20, Body.y - 70, hBlack, HasC4);
					}

					if (hMenuItem[12] == 1)
					{
						sprintf_s(txt, "Distance: [%d]", (DWORD)(CalculateDist(Me->Object->Body, pPlayer->Object->Body) / 100));
						WriteText(pDevice, Body.x + 20, Body.y - 60, hOrange, txt);
					}
					if (hMenuItem[11] == 1)
					{

						DrawBone(pDevice, pPlayer->Object, 6, 0, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 5, 6, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 4, 5, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 3, 4, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 2, 3, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 1, 2, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 21, 1, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 22, 21, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 23, 22, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 24, 23, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 25, 1, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 26, 25, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 27, 26, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 28, 27, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 14, 5, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 15, 14, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 16, 15, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 17, 16, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 18, 17, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 19, 17, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 20, 17, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 7, 5, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 8, 7, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 9, 8, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 10, 9, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 11, 10, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 12, 10, ESP_Color);
						DrawBone(pDevice, pPlayer->Object, 13, 10, ESP_Color);
					}

					if (hMenuItem[16] == 1)
					{
						D3DXVECTOR3 Pos0, Pos1, Pos2, Pos3, Pos4, Pos5, Pos6, Pos7, Pos8;
						Pos0 = GetMidPoint(GetBonePosition(pPlayer->Object, 6), GetBonePosition(pPlayer->Object, 3));
						Pos1 = Pos0 + D3DXVECTOR3(-50, 160, -50);
						Pos2 = Pos0 + D3DXVECTOR3(-50, -160, -50);
						Pos3 = Pos0 + D3DXVECTOR3(50, -160, -50);
						Pos4 = Pos0 + D3DXVECTOR3(50, 160, -50);
						Pos5 = Pos0 + D3DXVECTOR3(-50, 160, 50);
						Pos6 = Pos0 + D3DXVECTOR3(-50, -160, 50);
						Pos7 = Pos0 + D3DXVECTOR3(50, -160, 50);
						Pos8 = Pos0 + D3DXVECTOR3(50, 160, 50);

						if (Trans3DTo2D(pDevice, &Pos1) && Trans3DTo2D(pDevice, &Pos2) && Trans3DTo2D(pDevice, &Pos3) && Trans3DTo2D(pDevice, &Pos4) && Trans3DTo2D(pDevice, &Pos5) && Trans3DTo2D(pDevice, &Pos6) && Trans3DTo2D(pDevice, &Pos7) && Trans3DTo2D(pDevice, &Pos8))
						{
							//DrawCircle(pt.x, pt.y, 18 * PI2,hRed, pDevice);
							DrawLine(pDevice, Pos1.x, Pos1.y, Pos2.x, Pos2.y, ESP_Color);
							DrawLine(pDevice, Pos2.x, Pos2.y, Pos3.x, Pos3.y, ESP_Color);
							DrawLine(pDevice, Pos3.x, Pos3.y, Pos4.x, Pos4.y, ESP_Color);
							DrawLine(pDevice, Pos4.x, Pos4.y, Pos1.x, Pos1.y, ESP_Color);
							DrawLine(pDevice, Pos5.x, Pos5.y, Pos6.x, Pos6.y, ESP_Color);
							DrawLine(pDevice, Pos6.x, Pos6.y, Pos7.x, Pos7.y, ESP_Color);
							DrawLine(pDevice, Pos7.x, Pos7.y, Pos8.x, Pos8.y, ESP_Color);
							DrawLine(pDevice, Pos8.x, Pos8.y, Pos5.x, Pos5.y, ESP_Color);
							DrawLine(pDevice, Pos1.x, Pos1.y, Pos5.x, Pos5.y, ESP_Color);
							DrawLine(pDevice, Pos2.x, Pos2.y, Pos6.x, Pos6.y, ESP_Color);
							DrawLine(pDevice, Pos3.x, Pos3.y, Pos7.x, Pos7.y, ESP_Color);
							DrawLine(pDevice, Pos4.x, Pos4.y, Pos8.x, Pos8.y, ESP_Color);
						}
					}
				}
			}
		}
	}
}
