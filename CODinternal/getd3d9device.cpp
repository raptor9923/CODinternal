#include"getd3d9device.h"

bool GetD3D9Device(void** vTable, size_t size)
{
	if (!vTable)   // check if already exists
		return false;
	// initialize direct3D9
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!direct3D9)
		return false;
	// create simple parameters for d3d9 device
	D3DPRESENT_PARAMETERS d3d9Params{};
	d3d9Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3d9Params.hDeviceWindow = GetForegroundWindow();
	d3d9Params.Windowed = ((GetWindowLong(d3d9Params.hDeviceWindow, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;
	d3d9Params.Windowed = true;
	IDirect3DDevice9* device;
	// create d3d9 device
	if (FAILED(direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3d9Params.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3d9Params, &device)))
	{
		direct3D9->Release();
		return false;
	}
	// return pointer to deviece and free memory
	memcpy(vTable, *reinterpret_cast<void***>(device),size);
	device->Release();
	direct3D9->Release();
	return true;
}
