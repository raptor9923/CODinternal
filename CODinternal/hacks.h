#pragma once
#include<string>
#include"windows.h"
#include"drawing.h"


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
	LPD3DXFONT* GetFontPtr();
	void MyCreateFont(IDirect3DDevice9* device, const std::wstring& font);
	void DrawMenu(IDirect3DDevice9* device);
	void KeyInput();
};

