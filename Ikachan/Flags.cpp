#include "Flags.h"

unsigned char gFlagNPC[FLAG_BYTES];

void InitFlags()
{
	for (int i = 0; i < FLAG_BYTES; i++)
		gFlagNPC[i] = 0;
}

bool SetNPCFlag(long a)
{
	if (a > (FLAG_BYTES * 8))
		return false;
	gFlagNPC[a / 8] |= 1 << a % 8;
	return true;
}

bool CutNPCFlag(long a)
{
	if (a > (FLAG_BYTES * 8))
		return true;
	gFlagNPC[a / 8] &= ~(1 << a % 8);
	return false;
}

bool GetNPCFlag(long a)
{
	if (a > (FLAG_BYTES * 8))
		return false;
	if (gFlagNPC[a / 8] & (1 << a % 8))
		return true;
	else
		return false;
}
