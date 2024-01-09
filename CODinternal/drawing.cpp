#include"drawing.h"

namespace Drawing
{
	void DrawMyText(LPCSTR TextToDraw, int x, int y, D3DCOLOR color, LPD3DXFONT font)
	{
		RECT rct = { x - 120,y,x + 120,y + 15 };
		font->DrawTextA(NULL, TextToDraw, -1, &rct, DT_NOCLIP, color);
	}
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
	{
		D3DRECT rct = { x,y,x + w,y + h };
		pDevice->Clear(1, &rct, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
	}
	void DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR color, IDirect3DDevice9* pDevice)
	{
		DrawFilledRect(x, y, w, thickness, color, pDevice);
		DrawFilledRect(x, y, thickness, h, color, pDevice);
		DrawFilledRect(x+w, y, thickness, h, color, pDevice);
		DrawFilledRect(x, y+h, w+thickness, thickness, color, pDevice);
	}
}