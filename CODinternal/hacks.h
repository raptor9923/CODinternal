#pragma once
#include<string>
#include"windows.h"
#include"d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include<d3d9.h>

class Hacks
{
	bool m_hacks[1]{ false };
	LPD3DXFONT m_font;
public:
	enum m_hacksEnum
	{
		menu,
		aim
	};
	void MyCreateFont(IDirect3DDevice9* device, std::wstring font);
	void KeyInput();
};

