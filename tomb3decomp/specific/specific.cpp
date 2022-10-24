#include "../tomb3/pch.h"
#include "specific.h"
#include "file.h"
#include "utils.h"

static long MasterVolume;

uchar SWR_FindNearestPaletteEntry(uchar* p, long r, long g, long b, bool ignoreSystemPalette)
{
	double best, dr, dg, db, d;
	long start, end, c;

	best = 10000000000.0;
	c = 0;					//originally uninitialized

	if (ignoreSystemPalette)
	{
		start = 10;
		end = 246;
		p += 30;
	}
	else
	{
		start = 0;
		end = 256;
	}

	for (; start < end; start++)
	{
		dr = double(r - *p++);
		dg = double(g - *p++);
		db = double(b - *p++);
		d = SQUARE(dr) + SQUARE(dg) + SQUARE(db);

		if (d < best)
		{
			best = d;
			c = start;
		}
	}

	return (uchar)c;
}

bool CD_Init()
{
	FILE* file;
	char VFAW[] = "d:\\VFAW.AFP";
	char NEIR[] = "d:\\NEIR.AFP";
	char OKET[] = "d:\\OKET.AFP";
	char AWCS[] = "d:\\AWCS.AFP";
	bool found;

	while (!FindCDDrive())
	{
		if (!UT_OKCancelBox(MAKEINTRESOURCE(102), App.WindowHandle))
			return 0;
	}

	VFAW[0] = cd_drive;
	NEIR[0] = cd_drive;
	OKET[0] = cd_drive;
	AWCS[0] = cd_drive;

	while (1)
	{
		file = fopen(VFAW, "rb");

		if (!file)
			found = 0;
		else
		{
			fseek(file, 0x29845000, SEEK_SET);
			found = fgetc(file) == '{';
			fclose(file);
		}

		if (found)
			break;

		file = fopen(NEIR, "rb");

		if (!file)
			found = 0;
		else
		{
			fseek(file, 0x29825800, SEEK_SET);
			found = fgetc(file) == '3';
			fclose(file);
		}

		if (found)
			break;

		file = fopen(OKET, "rb");

		if (!file)
			found = 0;
		else
		{
			fseek(file, 0x29842800, SEEK_SET);
			found = fgetc(file) == 'u';
			fclose(file);
		}

		if (found)
			break;

		file = fopen(AWCS, "rb");

		if (!file)
			found = 0;
		else
		{
			fseek(file, 0x2981E000, SEEK_SET);
			found = fgetc(file) == '{';
			fclose(file);
		}

		if (found)
			break;

		if (!UT_OKCancelBox(MAKEINTRESOURCE(102), App.WindowHandle))
			return 0;
	}

	return 1;
}

long CalcVolume(long volume)
{
	return long((float(MasterVolume * volume) * 0.00019074068F - 400.0F) * 6.0F);
}

void S_SoundSetMasterVolume(long volume)
{
	MasterVolume = volume;
}

void inject_specific(bool replace)
{
	INJECT(0x0048D500, SWR_FindNearestPaletteEntry, replace);
	INJECT(0x0048D2E0, CD_Init, replace);
	INJECT(0x0048D0A0, CalcVolume, replace);
	INJECT(0x0048D200, S_SoundSetMasterVolume, replace);
}
