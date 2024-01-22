#pragma once
#include<Windows.h>

namespace Offsets
{
	uintptr_t clientinfoArray = 0x00831270;
	uintptr_t clientinfoTeam = 0x1C;
	uintptr_t clientinfoPosition = 0x398;
	uintptr_t clientinfoSize = 0x4CC;
	uintptr_t clientInfoHealth = 0x38;

	uintptr_t cg_t = 0x01280500;
	uintptr_t playerIngame = 0x30;
	uintptr_t playerHealth = 0x1A0;
	uintptr_t cg_t_size = 0x274;
	
	uintptr_t cg_t2 = 0x00746338;
	uintptr_t playerPosition = 0x1C;
	uintptr_t playerState = 0x4613C;
	uintptr_t playerViewAngles = 0x108;
	uintptr_t refDef = 0x492C8;
	uintptr_t screenWidth = 0x8;
	uintptr_t fov = 0x10;
	uintptr_t cameraPos = 0x18;

	uintptr_t cg_entities = 0x8472D8;
	uintptr_t entitiesIsValid = 0x2;
	uintptr_t entitiesClientNum = 0xCC;
	uintptr_t entitiesIsAlive = 0x1C0;
	uintptr_t entities_size= 0x1DC;
	
}