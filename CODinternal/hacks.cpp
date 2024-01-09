#include "Hacks.h"

void Hacks::KeyInput()
{
	if (GetAsyncKeyState(VK_INSERT)&1)
		m_hacks[m_hacksEnum::menu] = !m_hacks[m_hacksEnum::menu];
}

void Hacks::MyCreateFont(IDirect3DDevice9* device,const std::wstring& font)
{
	D3DXCreateFont(device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font.c_str(), &m_font);
}

LPD3DXFONT* Hacks::GetFontPtr()
{
	return &m_font;

}

void Hacks::DrawMenu(IDirect3DDevice9* device)
{
	if (m_hacks[m_hacksEnum::menu] == true)
	{
		Drawing::DrawFilledRect(55, 20, 200, 50, D3DCOLOR_ARGB(255, 0, 42, 255), device);
	}
}