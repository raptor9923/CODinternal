#include"memory.h"

namespace memory
{
	void PatchMemory(BYTE* destination, BYTE* source, int size)
	{
		DWORD protection;
		VirtualProtect(destination,size,PAGE_EXECUTE_READWRITE,&protection);
		memcpy_s(destination, size, source, size);
		VirtualProtect(destination, size, protection, &protection);

	}
	bool Hook(BYTE* source, BYTE* destination, int size)
	{
		if (size < 5)
			return false;
		//VirtualAlloc();
	}
	
	BYTE* Detour32(BYTE* source, BYTE* destination, int size)
	{
		// check proper size
		if (size < 5)
			return 0;
		// create code section for executing cut bytes
		auto gateway = (BYTE*)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		// copy bytes
		memcpy_s(gateway, size, source, size);
		auto relativeAddres = (uintptr_t)((uintptr_t)source - (uintptr_t)gateway);
		auto relativeAddres2 = (uintptr_t)((uintptr_t)gateway- (uintptr_t)source);
		auto srelativeAddres = (intptr_t)((uintptr_t)source - (uintptr_t)gateway);
		auto srelativeAddres2 = (intptr_t)((uintptr_t)gateway - (uintptr_t)source);
		int b = 2;
		int c = 2 + b;

		return 0;
	}
}