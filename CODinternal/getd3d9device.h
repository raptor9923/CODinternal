#pragma once
#include<d3d9.h>
#include"d3dx9.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")



typedef HRESULT(APIENTRY * tEndScene)(LPDIRECT3DDEVICE9 device);

bool GetD3D9Device(void** vTable, size_t size);
