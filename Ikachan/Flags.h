#pragma once
//#include <windows.h>

#define FLAG_BYTES (32)
extern unsigned char gFlagNPC[FLAG_BYTES];

void InitFlags();
bool SetNPCFlag(long a);
bool CutNPCFlag(long a);
bool GetNPCFlag(long a);
