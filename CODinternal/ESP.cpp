#pragma once
#include "ESP.h"

LPD3DXFONT fontPtr; 
IDirect3DDevice9* deviceESPPtr;
LPD3DXLINE initLine;
HWND wndHandle;
namespace ESP
{

	void SetupDirectX(LPDIRECT3DDEVICE9 pDevice, LPD3DXFONT* pFont)
	{
		fontPtr = *pFont;
		deviceESPPtr = pDevice;
		D3DXCreateLine(deviceESPPtr, &initLine);
		wndHandle = FindWindow(NULL, L"Call of Duty 4");
	}
}