#pragma once
#include "../global/vars.h"

void inject_larafire(bool replace);

long WeaponObject(long weapon_type);
long FireWeapon(long weapon_type, ITEM_INFO* target, ITEM_INFO* source, short* angles);
void HitTarget(ITEM_INFO* item, GAME_VECTOR* hitpos, long damage);
void SmashItem(short item_number, long weapon_type);
void AimWeapon(WEAPON_INFO* winfo, LARA_ARM* arm);
void LaraTargetInfo(WEAPON_INFO* winfo);

#define LaraGun	( (void(__cdecl*)()) 0x00449BB0 )
#define InitialiseNewWeapon	( (void(__cdecl*)()) 0x0044A1E0 )
#define DoProperDetection	( (void(__cdecl*)(short, long, long, long, long, long, long)) 0x0044AFB0 )
