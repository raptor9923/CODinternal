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
		DWORD protection;
		VirtualProtect(source, size, PAGE_EXECUTE_READWRITE, &protection);
		auto relativeAddress = (uintptr_t)((uintptr_t)destination - (uintptr_t)source - 5);
		*source = 0xE9;
		*(uintptr_t*)(source + 1) = relativeAddress;
		DWORD temp;
		VirtualProtect(source, size, protection, &temp);
		return true;
	}
	
	BYTE* Detour32(BYTE* source, BYTE* destination, int size)
	{
		// check proper size
		if (size < 5)
			return 0;
		// create code section for executing cut bytes
		auto gateway = (BYTE*)VirtualAlloc(0, size + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		// copy code to gateway 
		memcpy_s(gateway, size, source, size);
		// insert jump address to gateway code
		auto relativeAddres =(uintptr_t)source - (uintptr_t)gateway;
		*(gateway + size) = 0xE9;
		*(uintptr_t*)(gateway + size + 1) = relativeAddres;

		Hook(source, destination, size);
		return gateway;
		
	}
}