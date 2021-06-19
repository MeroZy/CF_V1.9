#pragma warning(disable:4305)

DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");

 float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

float CalculateDistance2(D3DXVECTOR3 from, D3DXVECTOR3 to)
{
	return sqrt((to.x - from.x) * (to.x - from.x) + (to.y - from.y) * (to.y - from.y) + (to.z - from.z) * (to.z - from.z));
}

/*void SetMouseCursor (LPDIRECT3DDEVICE9 pDevice, CPlayer* Me, CPlayer* pPlayer, D3DXVECTOR3 pos)
{
	CLTPlayerClient* pClient = (CLTPlayerClient*)(*(DWORD*)(AAAAAAAAAAAaCLTPlayerClient + AAAAAAAAAAACLTPlayerClientOffset));
	if (pPlayer && pPlayer->Object && pPlayer->Health > 0 && pPlayer != Me)
	{
		D3DXMATRIX View, iView;
		D3DXVECTOR3 fDist;
		pDevice->GetTransform(D3DTS_VIEW, &View);
		D3DXMatrixInverse(&iView, 0, &View);
		D3DXVec3Subtract(&fDist,&pos,&D3DXVECTOR3(iView._41, iView._42, iView._43));
		pClient->Pitch	= (float)atan2(-fDist.y,sqrt(fDist.x * fDist.x + fDist.z * fDist.z));
		pClient->Yaw	= (float)atan2(fDist.x, fDist.z);
	}
}

int GetNearestByCrossHair (LPDIRECT3DDEVICE9 pDevice)
{
	int iAimAt = -1;
	float MaxDistance = 0xFFFFFFF;

	D3DVIEWPORT9 viewP;
	pDevice->GetViewport(&viewP);
	float ScreenX = viewP.Width / 2; 
	float ScreenY = viewP.Height / 2 ;
	float PosX = 0.0f, PosY = 0.0f;

	DWORD pLTClientShell = *(DWORD*)AAAAAAAAAaLTClientShell;
	CPlayer* Me = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));

	for (int i=0; i<16; i++)
	{
		CPlayer* pPlayer = GetPlayerByIndex(pLTClientShell, i);
		D3DXVECTOR3 pos = GetBonePosition(pPlayer->Object,6);
		
		if (!IsValidClient(pPlayer) && Me != pPlayer) continue;
		if (IsTM(Me, pPlayer)) continue;

		if(WorldToScreen(pDevice,&pos))
		{
			PosX = pos.x > ScreenX ? pos.x - ScreenX : ScreenX - pos.x;
			PosY = pos.y > ScreenY ? pos.y - ScreenY : ScreenY - pos.y; 

			float Tmp = sqrt( PosX*PosX + PosY*PosY );

			if(Tmp < MaxDistance)
			{
				MaxDistance = Tmp;
				iAimAt = i;
			}
		}
	}
	return iAimAt;
}*/


void StartAimBot(LPDIRECT3DDEVICE9 pDevice)
{
	DWORD eBject = (DWORD)GetModuleHandleA("Object.dll");
	if (eBject)
	{
		
		///try mo na//try
		//anti send errorr report
		DWORD crossfire = (DWORD)GetModuleHandleA("crossfire.exe");
		if (crossfire == NULL) return;
		DWORD CShell = (DWORD)GetModuleHandleA("CShell.dll");
		if (hMenuItem[51] > 0 && eBject) // a7a !!

		{
			int TargetIndex, BONE_ID;
			switch (hMenuItem[52])// aiil di we a3mil connection m3 el d3d bta3tk 

			{
			case 1: BONE_ID = 6; break;//Head
			case 2: BONE_ID = 5; break;//Neck
			case 3: BONE_ID = 2; break;//Body
			case 4: BONE_ID = 10; break;//LeftHand
			case 5: BONE_ID = 17; break;//RightHand
			case 6: BONE_ID = 23; break;//LeftFoot
			case 7: BONE_ID = 28; break;//RightFoot
			default: BONE_ID = 6;//Head
			}

			int iAimAt = -1;
			float MaxDistance = 0xFFFFFFF;

			POINT pt;
			D3DVIEWPORT9 viewP;
			pDevice->GetViewport(&viewP);
			float ScreenX = viewP.Width / 2;
			float ScreenY = viewP.Height / 2;
			pt.x = ScreenX;
			pt.y = ScreenY;



			DWORD pLTClientShell = *(DWORD*)(CShell + AAAAAAAAAaLTClientShell);
			if (pLTClientShell != NULL)
			{
				CPlayer* Me = GetPlayerByIndex(pLTClientShell, GetMyIndex(pLTClientShell));
				if (isValidClient(Me))
				{
					for (int i = 0; i < 16; i++)
					{
						CPlayer* pPlayer = GetPlayerByIndex(pLTClientShell, i);
						D3DXVECTOR3 pos = GetBonePosition(pPlayer->Object, 6);

						if (!isValidClient(pPlayer) && Me != pPlayer) continue;
						if (IsTM(Me, pPlayer)) continue;
					
						if (WorldToScreen(pDevice, &pos))
						{
							float radiusx = (15 * 5.0f) * (ScreenX / 100.0f);
							float radiusy = (15 * 5.0f) * (ScreenY / 100.0f);

							float Tmp = NULL;

							if (hMenuItem[53] = 0) { // Get player distance from crosshair
								Tmp = GetDistance(pos.x, pos.y, ScreenX, ScreenY);
							}
							else if (hMenuItem[53] = 1) { // Get player distance from player
								Tmp = CalculateDistance2(Me->Object->Body, pPlayer->Object->Body) / 100;
							}

							if (pos.x >= ScreenX - radiusx && pos.x <= ScreenX + radiusx && pos.y >= ScreenY - radiusy && pos.y <= ScreenY + radiusy)
							{
								if (Tmp < MaxDistance)
								{
									MaxDistance = Tmp;
									iAimAt = i;
									
								}
							}
						}
					}

					if (iAimAt == -1)
						return;

					if (iAimAt > -1)
					{
						CPlayer* Target = GetPlayerByIndex(pLTClientShell, iAimAt);
						if (isValidClient(Target))
						{
							if (Target && Target->Object && Target->Health > 0 && Target != Me)
							{
								D3DXVECTOR3 AimPos = GetBonePosition(Target->Object, BONE_ID);
								if (WorldToScreen(pDevice, &AimPos))
								{
									float DistX = AimPos.x - ScreenX;
									float DistY = AimPos.y - ScreenY;

									if (hMenuItem[53] == 0)
									{
											switch (hMenuItem[51])
											{
											case 1: mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
											case 2: if (GetAsyncKeyState(VK_LBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
											case 3: if (GetAsyncKeyState(VK_RBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
											case 4: if (GetAsyncKeyState(VK_SHIFT)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL);	break;
											case 5: if (GetAsyncKeyState(VK_MENU)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
											default: if (GetAsyncKeyState(VK_LBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
											}
									}
									else if (hMenuItem[53] == 0)
									{
										switch (hMenuItem[51])
										{
										case 1: mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
										case 2: if (GetAsyncKeyState(VK_LBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
										case 3: if (GetAsyncKeyState(VK_RBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
										case 4: if (GetAsyncKeyState(VK_SHIFT)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL);	break;
										case 5: if (GetAsyncKeyState(VK_MENU)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
										default: if (GetAsyncKeyState(VK_LBUTTON)) mouse_event(MOUSEEVENTF_MOVE, (float)DistX, (float)DistY, 0, NULL); break;
										}
									}

								}
							}
						}
					}
				}
			}
		}

	}
}
