#pragma once
#include "../global/vars.h"

void inject_audio(bool replace);

BOOL __stdcall ACMEnumCallBack(HACMDRIVERID hadid, DWORD_PTR dwInstance, DWORD fdwSupport);
void ACMCloseFile();
bool ACMOpenFile(const char* name);
void ACMEmulateCDStop();

#define ACMClose	( (void(__cdecl*)()) 0x00474760 )
