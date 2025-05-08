#pragma once
#include "NpChar.h"
#include "Map.h"
//#include <windows.h>

extern bool gEditorMode;
extern short gEditorNPC;

void InitEditor();
void PutEditorCursor();
void PutEditorSelect(NPCHAR *npc, FRAME *frame);
void EditorProc(NPCHAR *npc);
void PutEditorNpcInfo(NPCHAR *npc);
bool LoadNpChar(NPCHAR *npc);
bool SaveNpChar(NPCHAR *npc);
