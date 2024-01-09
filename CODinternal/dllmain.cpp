#include"getd3d9device.h"
#include"memory.h"
#include"hacks.h"
#include"ESP.h"

tEndScene origEndScene;
Hacks hack;
LPDIRECT3DDEVICE9 devicePtr=nullptr;
void* device[119];
bool bInit{ false };

// hooked endScene function
HRESULT APIENTRY HackedEndScene(LPDIRECT3DDEVICE9 device)
{
    if (!bInit)
    {
        hack.MyCreateFont(device, L"Tahoma");
        ESP::SetupDirectX(device, hack.GetFontPtr());
        bInit = true;
    }
    hack.KeyInput();
    hack.DrawMenu(device);

   return origEndScene(device);
}

DWORD WINAPI HackThread()
{
    // hook endScene function
    if (GetD3D9Device(device, sizeof(device)))
    {
        origEndScene = (tEndScene)memory::Detour32((BYTE*)device[42], (BYTE*)HackedEndScene, 7);
    }
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

