#include "Hacks.h"

void Hacks::KeyInput()
{
	if (GetAsyncKeyState(VK_INSERT))
		m_hacks[m_hacksEnum::menu] = !m_hacks[m_hacksEnum::menu];
}

void Hacks::MyCreateFont(IDirect3DDevice9* device, std::wstring font)
{
	D3DXCreateFont(device, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font.c_str(), &m_font);
}