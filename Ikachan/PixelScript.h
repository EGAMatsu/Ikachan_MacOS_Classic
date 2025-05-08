#pragma once
#include "Draw.h"
#include "PiyoPiyo.h"
//#include <windows.h>

#define MAX_PSLINES ((SURFACE_HEIGHT + 24) / 24)

struct PIX_SCR
{
	char* data;
	unsigned long p_read;
	unsigned long size;
	int ypos_line[MAX_PSLINES];
	unsigned long line;
	char scale;
	bool end;
};

bool ReadPixelScript(PIX_SCR *ptx, const char* path);
void LoadPixelScript(PIX_SCR *ptx, const char* path, char scale);
int PixelScriptProc(PIX_SCR *ptx, PIYOPIYO_CONTROL *piyocont, bool ending);
void EndPixelScript(PIX_SCR *ptx);
