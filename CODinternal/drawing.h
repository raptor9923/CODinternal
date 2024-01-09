#pragma once

#include<d3d9.h>
#include"d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace Drawing
{
	void DrawMyText(LPCSTR TextToDraw, int x,int y,D3DCOLOR color,LPD3DXFONT font);
	void DrawFilledRect(int x, int y, int w, int h, D3DCOLOR color,IDirect3DDevice9* pDevice);
	void DrawBorderBox(int x, int y, int w, int h, int thickness, D3DCOLOR Colour, IDirect3DDevice9* pDevice);
}