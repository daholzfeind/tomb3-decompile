#pragma once
#include "../global/vars.h"

void inject_inventry(bool replace);

long GetDebouncedInput(long in);
void SelectMeshes(INVENTORY_ITEM* item);
long AnimateInventoryItem(INVENTORY_ITEM* item);

#define Display_Inventory	( (long(__cdecl*)(long)) 0x00435400 )
