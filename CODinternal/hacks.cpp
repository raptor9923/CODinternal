#include "Hacks.h"

D3DCOLOR fontRed = D3DCOLOR_ARGB(255, 255, 0, 0);
D3DCOLOR fontGreen = D3DCOLOR_ARGB(255, 0, 255, 0);
D3DCOLOR fontBlue = D3DCOLOR_ARGB(255, 0, 42, 255);
D3DCOLOR fontWhite = D3DCOLOR_ARGB(255, 255, 255, 255);
D3DCOLOR fontBlack = D3DCOLOR_ARGB(255, 0, 0, 0);

void Hacks::KeyInput()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		m_hacks[m_hacksEnum::menu] = !m_hacks[m_hacksEnum::menu];
	if (m_hacks[m_hacksEnum::menu]==true)
	{
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			if (m_menuIndex != 1)
				m_menuIndex--;

		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			if ((m_menuIndex != m_hacksEnum::count))
				m_menuIndex++;

		}
		if (GetAsyncKeyState(VK_END) & 1)
		{
			m_hacks[m_menuIndex] = !m_hacks[m_menuIndex];
		}
	}
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
		// title
		Drawing::DrawFilledRect(55, 20, 200, 50, fontBlue, device);
		Drawing::DrawBorderBox(55, 20, 200, 50, 4, fontBlack, device);
		Drawing::DrawMyText("COD 4 hack", 190, 30, fontWhite, m_font);
		// hacks window
		Drawing::DrawFilledRect(30, 55, 250, (62 * m_hacksEnum::count)+10, fontBlue, device);
		Drawing::DrawBorderBox(30, 55, 250, (62 * m_hacksEnum::count)+10, 6, fontBlack, device);
		// hacks
		int y = 40;
		for (int i = 1; i<= m_hacksEnum::count; i++)
		{
			Drawing::DrawFilledRect(45, 70 + y, 220, 40, m_hacks[i]? fontGreen : fontRed, device);
			Drawing::DrawBorderBox(45, 70 + y, 220, 40, 4, fontBlack, device);

			//draw White border to show the user which hack item is currently selected
			if (m_menuIndex == i)
			{
				Drawing::DrawBorderBox(41, 66 + y, 228, 48, 4, fontWhite, device);
			}

			//if the  hack is on we display the text colour in green
			//Drawing::DrawMyText(m_hacks[i], 170, 39 + y, fontBlack , m_font);
			//used to position the next item below
			y += 50;
		}
		Drawing::DrawMyText("Select using arrow keys", 170, 65, fontWhite, m_font);
		Drawing::DrawMyText("Turn ON/OFF [END] key", 170, 85, fontWhite, m_font);
	}
	
}