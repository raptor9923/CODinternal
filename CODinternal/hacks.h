#pragma once
#include<string>
#include"windows.h"
#include"drawing.h"
#include<array>


class Hacks
{
public:
	enum m_hacksEnum
	{
		menu,
		aim,
		esp,
		recoil,
		count
	};
	short m_menuIndex = 1;
	bool m_hacks[m_hacksEnum::count]{ false };
	LPD3DXFONT m_font;
	std::array<std::string, m_hacksEnum::count-1> m_hacksTitles {"aim","esp","recoil"};
public:
	
	LPD3DXFONT* GetFontPtr();
	void MyCreateFont(IDirect3DDevice9* device, const std::wstring& font);
	void DrawMenu(IDirect3DDevice9* device);
	void KeyInput();
};

