#include"getd3d9device.h"
#include"memory.h"

tEndScene origEndScene;
LPDIRECT3DDEVICE9 devicePtr=nullptr;
void* device[119];

HRESULT APIENTRY Hack(LPDIRECT3DDEVICE9 device)
{
    OutputDebugStringA("SD");
    return origEndScene(device);
}

DWORD WINAPI HackThread()
{
    if (GetD3D9Device(device, sizeof(device)))
    {
        origEndScene = (tEndScene)memory::Detour32((BYTE*)device[42], (BYTE*)Hack, 7);
    }
            //hook process
    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{

    DisableThreadLibraryCalls(hModule);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, 0, 0, 0);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

