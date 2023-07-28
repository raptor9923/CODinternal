#pragma once
#pragma comment(lib, "d3d9.lib")
#include<d3d9.h>

typedef HRESULT(APIENTRY * tEndScene)(LPDIRECT3DDEVICE9 device);

bool GetD3D9Device(void**, size_t size);
