#pragma once
#include "Map.h"
#include "EventScript.h"
//#include <windows.h>
#include "FakeRect.h"

struct BOSS
{
	bool cond;
	short life;
	short shock;
	unsigned char x6;
	char code_char;
	short code_event;
	short defeat_event;
	short act_wait;
	char act_no;
	char ani_no;
	short ani_wait;
	char direct;
	unsigned char flag;
	bool airborne;
	int x;
	int y;
	int xm;
	int ym;
	int tgt_x;
	int tgt_y;
	RECT hit;
};

extern BOSS gBoss;

void InitBoss();
void PutBoss(FRAME *frame);
void ActBoss(CARET_SPAWNER *caret_spawner);
void HitMyCharBoss(EVENT_SCR *event_scr, CARET_SPAWNER *caret_spawner);