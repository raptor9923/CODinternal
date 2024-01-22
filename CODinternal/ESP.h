#pragma once
#include"drawing.h"

#include <math.h>
#include"geometry.h"

struct Color
{
	short r, g, b;
	Color() {}
	Color(short x, short y, short z)
	{
		r = x;
		g = y;
		b = z;
	}
};
class Entity
{
public:
	int m_inGame;
	int m_health;
	int m_team;
	int m_isValid;
	int m_isAlive;
	int m_clientNumber;
	Color m_color;
	Vec3 m_position;
};

namespace ESP
{
	void SetupDirectX(LPDIRECT3DDEVICE9 pDevice,LPD3DXFONT* pFont);
	void Esp(PDIRECT3DDEVICE9 pDevice,bool esp,bool aimbot);
	Entity GetPlayerData();
	bool WorldToScreen(const Vec3& world, const Vec3& camera);
	void GetAngles();
	void UpdateRes();
	void DrawESPBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, IDirect3DDevice9* pDevice);
	int FindEnemy(Entity* targets,int numtargets,const Entity& player);
}
