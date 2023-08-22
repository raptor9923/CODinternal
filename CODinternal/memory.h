#pragma once
#include <Windows.h>

namespace memory
{
	void PatchMemory(BYTE* destination, BYTE* source, int size);
	bool Hook(BYTE* source, BYTE* destination, int size);
	BYTE* Detour32(BYTE* source, BYTE* destination, int size);
}