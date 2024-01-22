#pragma once
#include "ESP.h"
#include"offsets.h"
LPD3DXFONT fontPtr; 
IDirect3DDevice9* deviceESPPtr;
LPD3DXLINE initLine;
HWND wndHandle;
RECT windowRect;
static const int MAX_PLAYERS=64;
int resX, resY;
int focusTarget=-1;
float fov1, fov2;
bool bRes = false;
float screenX, screenY;
int screenCenterX, screenCenterY;
Vec3 viewAngles;
Vec3 vForward;
Vec3 vRight;
Vec3 vUpward;
float drawx, drawy;

namespace ESP
{

	void SetupDirectX(LPDIRECT3DDEVICE9 pDevice, LPD3DXFONT* pFont)
	{
		fontPtr = *pFont;
		deviceESPPtr = pDevice;
		D3DXCreateLine(deviceESPPtr, &initLine);
		wndHandle = FindWindow(NULL, L"Call of Duty 4");
	}

	Entity GetPlayerData()
	{
		Entity player,player2;
		player.m_inGame = *(int*)(Offsets::cg_t + Offsets::playerIngame);
		player.m_health = *(int*)(Offsets::cg_t + Offsets::playerHealth);
		player.m_clientNumber = *(int*)(Offsets::cg_t);
		player.m_team = *(int*)(Offsets::clientinfoArray + player.m_clientNumber * Offsets::clientinfoSize + Offsets::clientinfoTeam);
		player.m_position = *(Vec3*)(Offsets::cg_t2 + Offsets::refDef + Offsets::cameraPos);
		viewAngles = *(Vec3*)(Offsets::cg_t2 + Offsets::playerState + Offsets::playerViewAngles);
		fov1 = *(float*)(Offsets::cg_t2 + Offsets::refDef + Offsets::fov);
		fov2 = *(float*)(Offsets::cg_t2 + Offsets::refDef + Offsets::fov+0x4);
		player2 = player; // cant see return struct in debug
		return player2;
	}

	void Esp(PDIRECT3DDEVICE9 pDevice, bool esp,bool aimbot)
	{
		Entity player = GetPlayerData();
		if (!player.m_inGame)
			return;
		UpdateRes();
		Entity enemies[64];
		int enemyCount = 0;
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			Entity enemy;
			uintptr_t enemyAddress = Offsets::clientinfoArray + i * Offsets::clientinfoSize;
			enemy.m_isValid= *(int*)(enemyAddress);
			enemy.m_health= *(int*)(Offsets::cg_t + i * Offsets::cg_t_size + Offsets::playerHealth);
			enemy.m_isAlive = *(int*)(Offsets::cg_entities + i * Offsets::entities_size + Offsets::entitiesIsAlive);
			enemy.m_clientNumber= *(int*)(Offsets::cg_entities + i * Offsets::entities_size + Offsets::entitiesClientNum);
			enemy.m_team= *(int*)(Offsets::clientinfoArray + i * Offsets::clientinfoSize + Offsets::clientinfoTeam);
			if (enemy.m_isValid && enemy.m_isAlive && enemy.m_clientNumber != player.m_clientNumber)
			{
				if (enemy.m_team == player.m_team)
					enemy.m_color = Color(0, 255, 0);
				else
					enemy.m_color = Color(255, 0, 0);

				enemy.m_position = *(Vec3*)(enemyAddress +Offsets::clientinfoPosition);
				enemies[enemyCount] = enemy;
				enemyCount++;
			}
		}
		if(esp)
		{
			player = GetPlayerData();
			float distance;
		
			for (int i = 0; i < enemyCount; i++)
			{
				distance = Distance(player.m_position, enemies[i].m_position) / 48;
				if (WorldToScreen(enemies[i].m_position, player.m_position))
				{

					drawx = 400.0f / distance;
					drawy = 800.0f / distance;
					DrawESPBox((int)(screenX)-(drawx / 2), //start drawing on the left
						(int)(screenY - drawy),
						drawx,
						drawy,
						2,
						D3DCOLOR_ARGB(255/*Alpha*/,
							enemies[i].m_color.r,
							enemies[i].m_color.g,
							enemies[i].m_color.b),
						pDevice);
				}
			}
		}
		if (aimbot)
		{
			Entity targets[MAX_PLAYERS];
			int targetCounter=0;
			for (int i = 0; i < enemyCount; i++)
			{
				if (enemies[i].m_team != player.m_team)
				{
					targets[targetCounter] = enemies[i];
					if (focusTarget == targetCounter)
					{
						if (targets[targetCounter].m_health < 1)
							focusTarget = -1;
					}
					targetCounter++;
				}
				
			}
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				int target=0;
				if (focusTarget != -1)
				{
					if (targets[focusTarget].m_health > 0)
						target = focusTarget;
					else
						target = FindEnemy(targets, targetCounter, player);
				}
				else
					target = FindEnemy(targets, targetCounter, player);
				if (target != -1)
				{
					float distance = Distance(player.m_position, targets[target].m_position)/48;
					WorldToScreen(targets[target].m_position, player.m_position);
					focusTarget = target;
					drawx = 400.0f / distance;
					drawy = 700.0f / distance;
					int x = screenX;
					int y = screenY - drawy;
					if (targets[target].m_health > 0)
					{
						GetWindowRect(wndHandle, &windowRect);
						SetCursorPos(windowRect.left + x, windowRect.top + y);
					}
				}
			}
		}

	}

	bool WorldToScreen(const Vec3& world, const Vec3& camera)
	{
		GetAngles();
		Vec3 temp, transform;
		temp = world - camera;

		transform.z = DotProduct(temp, vForward);
		transform.x = DotProduct(temp, vRight);
		transform.y = DotProduct(temp, vUpward);
		if (transform.z< 0.01f)
			return false;
		
		screenX = screenCenterX + (screenCenterX/ transform.z * (1 / fov1)) * transform.x;
		screenY = screenCenterY - (screenCenterY / transform.z * (1 / fov2)) * transform.y;
		
		
		return true;
	}

	void GetAngles()
	{
		float angle;
		float rad = 3.141f / 180.0f;
		angle = viewAngles.y * rad;
		float sinYaw = sinf(angle);
		float cosYaw = cosf(angle);
		angle = viewAngles.x * rad;
		float sinPitch = sinf(angle);
		float cosPitch = cosf(angle);
		angle = viewAngles.z * rad;
		float sinRoll = sinf(angle);
		float cosRoll = cosf(angle);
		vForward.x = cosYaw * cosPitch;
		vForward.y = sinYaw * cosPitch;
		vForward.z = -sinPitch;
		vRight.x = -1*(cosYaw * sinPitch * sinRoll - cosRoll * sinYaw);
		vRight.y = -1 * (sinYaw * sinPitch * sinRoll + cosRoll * cosYaw);
		vRight.z = -1 * cosPitch * sinRoll;
		vUpward.x = cosYaw * sinPitch * cosRoll + sinRoll * sinYaw;
		vUpward.y = sinYaw * sinPitch * cosRoll - sinRoll * cosYaw;
		vUpward.z = cosPitch * cosRoll;

	}

	void UpdateRes()
	{
		resX = *(int*)(Offsets::cg_t2 + Offsets::refDef + Offsets::screenWidth);
		resY = *(int*)(Offsets::cg_t2 + Offsets::refDef + Offsets::screenWidth + 0x4);
		screenCenterX = resX / 2;
		screenCenterY = resY / 2;
		bRes = true;
	}

	void DrawESPBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, IDirect3DDevice9* pDevice)
	{
		//Top horiz line
		Drawing::DrawFilledRect(x, y, w, thickness, Colour, pDevice);
		//Left vertical line
		Drawing::DrawFilledRect(x, y, thickness, h, Colour, pDevice);
		//right vertical line
		Drawing::DrawFilledRect((x + w), y, thickness, h, Colour, pDevice);
		//bottom horiz line
		Drawing::DrawFilledRect(x, y + h, w + thickness, thickness, Colour, pDevice);
	}

	int FindEnemy(Entity* targets, int numtargets, const Entity& player)
	{
		float distance=0;
		float closest = 9999999;
		int index = -1;
		for (int i = 0; i < numtargets; i++)
		{
			if (targets[i].m_health > 1)
			{
				distance = Distance(targets[i].m_position, player.m_position);
				if (distance < closest)
					index = i;
			}
		}
		return index;
	}
}