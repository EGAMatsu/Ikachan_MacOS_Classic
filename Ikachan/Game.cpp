#include "Game.h"
#include "Generic.h"
#include "Item.h"
#include "Draw.h"
#include "Flags.h"
#include "PixelScript.h"
#include "EventScript.h"
#include "Opening.h"
#include "Map.h"
#include "Player.h"
#include "NpChar.h"
#include "PiyoPiyo.h"
#include "Editor.h"
#include "Boss.h"
#include "Effect.h"
#include "System.h"

#include <time.h>
#include <stdio.h>

unsigned long gKeyTrg, gMouseTrg, gMouseTrg2;

RECT grcLoading = { 0, 0, 32, 8 };

void GetTrg()
{
	static unsigned long key_prev, mouse_prev;

	//Get pressed key
	gKeyTrg = (key_prev ^ gKey) & gKey;
	key_prev = gKey;

	//Get pressed mouse
	gMouseTrg = (mouse_prev ^ gMouse) & gMouse;
	mouse_prev = gMouse;

	//Get some mouse thing
	static int timer;
	if (gMouse)
		timer++;
	else
		timer = 0;

	gMouseTrg2 = 0;
	if (timer > 20 || timer == 1)
		gMouseTrg2 = gMouse;
}

unsigned long CountFramePerSecound()
{
	unsigned long current_tick;
	static bool first = true;
	static unsigned long max_count;
	static unsigned long count;
	static unsigned long wait;

	if (first)
	{
		wait = clock();
		first = false;
	}

	current_tick = clock();
	++count;

	if (wait + 1000 <= current_tick)
	{
		wait += 1000;
		max_count = count;
		count = 0;
	}

	return max_count;
}

enum GAMEMODE
{
	GAMEMODE_OPENING,
	GAMEMODE_GAMEPLAY,
	GAMEMODE_EDITOR,
	GAMEMODE_INVENTORY,
	GAMEMODE_INTRO = 5,
	GAMEMODE_LOAD,
	GAMEMODE_STAFF
};

bool Game() // TODO hWnd
{
	char path[MAX_PATH];
	
	OPENING opening;
	FADE fade;
	ITEMS items;
	EVENT_SCR event_scr;
	PIX_SCR pix_scr;
	MAP map;
	NPCHAR npc[MAX_NPCS];
	CARET caret[MAX_CARETS];
	CARET_SPAWNER caret_spawner[MAX_CARET_SPAWNERS];
	FRAME frame;
	PIYOPIYO_CONTROL piyocont;
	unsigned long tick;
	
	//Load generic data
	LoadGenericData();
	
	//Initalize game
	InitFlags();
	InitItem(&items);
	InitEventScript(&event_scr);
	InitMyChar();
	InitNpChar(npc);
	InitBoss();
	LoadNpChar(npc);
	InitTextObject(NULL);
	
	//Initialize editor
	gEditorNPC = 0;
	gEditorMode = 0;
	
	//Initialize frame
	frame.x = gMC.x - (SURFACE_WIDTH << 9);
	frame.y = gMC.y - (SURFACE_HEIGHT << 9);
	
	//Initialize fade
	fade.mode = FADE_MODE_NONE;
	fade.mask = false;
	
	//Initialize carets
	for (int i = 0; i < MAX_CARET_SPAWNERS; i++)
		caret_spawner[i].cond = false;
	for (int i = 0; i < MAX_CARETS; i++)
		caret[i].cond = false;
	
	//Load fade surface here for some reason
	MakeSurface_File("Pbm/Fade.pbm", SURFACE_ID_FADE);
	
	//Start game (start in opening)
	char mode = GAMEMODE_OPENING;
	InitOpening(&opening);
	char next_mode = mode;
	
	//Play opening music
	piyocont.track = 3;
	piyocont.mode = 1;
	PiyoPiyoControl(&piyocont);
	
	//Opening
	while (mode == GAMEMODE_OPENING)
	{
		ProcessSystemEvent(NULL);
		/*SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ProcessSystemEvent();
			if (e.type == SDL_QUIT) {
				return true;
			}
		}*/
		//Start frame
		tick = clock();
		PiyoPiyoControl(&piyocont);
		GetTrg();
		CortBox(&grcFull, 0x000000);
		
		//Run opening
		if (gKeyTrg & KEY_Z)
			fade.mode = FADE_MODE_FADEOUT;
		PutOpening(&opening);
		if (ProcFade(&fade, &frame, caret_spawner) == true)
			mode = GAMEMODE_LOAD;
		
		//End frame
		if (!Flip_SystemTask_IKA())
			return true;
		PiyoPiyoProc();
	}
	
	//Load map event and data
	sprintf(path, "%s/%s", gModulePath, "Event.ptx");
	if (!ReadEventScript(path, &event_scr))
		return true;
	DebugPutText((const char*)event_scr.data);
	
	sprintf(path, "%s/%s", gModulePath, "Pbm/Map1.pbm");
	if (!LoadMapData(path, &map))
		return true;
	
	//Run load script
	event_scr.mode = 1;
	event_scr.x1C = 4;
	event_scr.event_no = 1;
	
	//Load screen
	next_mode = GAMEMODE_INTRO;
	while (mode == GAMEMODE_LOAD)
	{
		ProcessSystemEvent(NULL);
		/*SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ProcessSystemEvent(&e);
		}*/
		
		//Start frame
		tick = clock();
		PiyoPiyoControl(&piyocont);
		GetTrg();
		CortBox(&grcFull, 0x000000);
		
		//Run load script
		if (EventScriptProc(&event_scr, &items, npc, &map, &piyocont, &fade, &frame) == 2)
		{
			fade.wait = 0;
			fade.mode = 3;
			next_mode = GAMEMODE_GAMEPLAY;
		}
		if (event_scr.mode == 0)
			mode = next_mode;
		PutMsgBox(&event_scr);
		
		//End frame
		if (!Flip_SystemTask_IKA())
			return true;
		PiyoPiyoProc();
	}
	
	//Prepare for intro
	if (gKey & KEY_S)
		mode = GAMEMODE_EDITOR;
	if (mode == GAMEMODE_INTRO)
	{
		//Play intro music
		piyocont.track = 1;
		piyocont.mode = 1;
		PiyoPiyoControl(&piyocont);
		
		//Run new game event when game starts
		event_scr.event_no = 2;
		event_scr.mode = 1;
	}
	
	//Load intro script
	sprintf(path, "%s/%s", gModulePath, "Words.ptx");
	LoadPixelScript(&pix_scr, path, 2);
	
	//Intro
	while (mode == GAMEMODE_INTRO)
	{
		ProcessSystemEvent(NULL);
		/*SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ProcessSystemEvent(&e);
			if (e.type == SDL_QUIT) {
				return true;
			}
		}*/
		//Start frame
		tick = clock();
		PiyoPiyoControl(&piyocont);
		GetTrg();
		CortBox(&grcFull, 0x00FFFF);
		
		//Run Pixel Script
		if (PixelScriptProc(&pix_scr, &piyocont, false) == 1)
		{
			//Start gameplay
			mode = GAMEMODE_GAMEPLAY;
			fade.mask = true;
		}
		
		//End frame
		if (!Flip_SystemTask_IKA())
			return true;
		PiyoPiyoProc();
	}
	EndPixelScript(&pix_scr);
	
	//Draw loading screen
	CortBox(&grcFull, 0x000000);
	PutBitmap3(&grcFull, (SURFACE_WIDTH / 2) - 16, (SURFACE_HEIGHT / 2) - 4, &grcLoading, SURFACE_ID_LOADING);
	if (!Flip_SystemTask_IKA())
		return true;
	
	//Play theme song
	piyocont.track = 0;
	piyocont.mode = 1;
	PiyoPiyoControl(&piyocont);
	
	//Initialize frame
	frame.x = gMC.x - (SURFACE_WIDTH << 9);
	frame.y = gMC.y - (SURFACE_HEIGHT << 9);
	frame.mode = FRAME_MODE_MYCHAR;
	frame.npc = 0;
	
	//Initialize editor
	if (mode == GAMEMODE_EDITOR)
		InitEditor();
	
	//Enter game loop
	while (mode != GAMEMODE_STAFF)
	{
		ProcessSystemEvent(NULL);
		/*SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ProcessSystemEvent(&e);
			if (e.type == SDL_QUIT) {
				return true;
			}
		}*/
		//Gameplay
		while (mode == GAMEMODE_GAMEPLAY)
		{
			ProcessSystemEvent(NULL);
			/*SDL_Event e;
			while (SDL_PollEvent(&e)) {
				ProcessSystemEvent(&e);
				if (e.type == SDL_QUIT) {
					return true;
				}
			}*/
			//Start frame
			tick = clock();
			PiyoPiyoControl(&piyocont);
			GetTrg();
			CortBox(&grcFull, 0x000000);
			
			//Update frame position
			MoveFrame(&frame, npc, &map);
			if (gKeyTrg & KEY_X)
				gMC.x += 0x200; //Move Ikachan right half a pixel when X is pressed (not sure why)
			
			//Draw background
			PutBack(&frame);
			PutMapBack(&map, frame.x, frame.y);
			
			//Update and draw Iron Head
			if (!event_scr.msg_box)
				ActBoss(caret_spawner);
			if (gMC.unit != 2)
				PutBoss(&frame);
			HitMyCharBoss(&event_scr, caret_spawner);
			
			//Update and draw NPCs
			HitNpCharMap(npc, &map);
			if (!event_scr.msg_box)
				ActNpChar(npc);
			PutNpChar(npc, &frame);
			
			//Update and draw Ikachan
			if (gMC.cond)
			{
				//Update player
				if (event_scr.msg_box == false)
					ActMyChar(caret, caret_spawner);
				
				//Player collision
				if (gMC.unit != 2)
				{
					HitMyCharNpChar(npc, &event_scr, caret_spawner);
					HitMyCharMap(&map, caret_spawner);
				}
				
				//Draw player
				if ((gMC.shock % 2) == 0 || event_scr.msg_box == true)
					PutMyChar(&frame);
			}
			
			//Run death event when Ikachan dies
			if (gMC.dead)
			{
				gMC.dead = 0;
				event_scr.mode = 1;
				event_scr.event_no = 6;
			}
			
			//Draw foreground
			PutMapFront(&map, frame.x, frame.y);
			PutMapVector(&map, frame.x, frame.y);
			
			//Run carets
			ProcCaret(caret, &map, &frame);
			ProcCaretSpawner(caret_spawner, caret);
			
			//Run event
			ProcFade(&fade, &frame, caret_spawner);
			switch (EventScriptProc(&event_scr, &items, npc, &map, &piyocont, &fade, &frame))
			{
				case 1:
					return true;
				case 3:
					mode = GAMEMODE_STAFF;
					break;
				default:
					break;
			}
			PutMsgBox(&event_scr);
			
			//Open inventory and draw status
			if ((gKeyTrg & KEY_S) && event_scr.mode == 0)
			{
				BackupSurface(SURFACE_ID_BACKUP, &grcFull);
				mode = GAMEMODE_INVENTORY;
				items.selected_item = 0;
			}
			PutMyStatus();
			
			//Play end cutscene when Ikachan exits the top of the screen
			if (gMC.y < -0x8000 && !event_scr.msg_box)
			{
				event_scr.msg_box = 1;
				event_scr.event_no = 4000;
				event_scr.mode = 1;
			}
			
			//End frame
			PutNumber(SURFACE_WIDTH - 48, 0, CountFramePerSecound());
			if (!Flip_SystemTask_IKA())
				return true;
			PiyoPiyoProc();
		}
		
		//Inventory
		while (mode == GAMEMODE_INVENTORY)
		{
			ProcessSystemEvent(NULL);
			/*SDL_Event e;
			while (SDL_PollEvent(&e)) {
				ProcessSystemEvent(&e);
				if (e.type == SDL_QUIT) {
					return true;
				}
			}*/
			//Start frame
			tick = clock();
			PiyoPiyoControl(&piyocont);
			GetTrg();
			CortBox(&grcFull, 0x000000);
			
			//Handle inventory
			if (event_scr.mode == 0)
				MoveItem(&items, &event_scr);
			PutItem(&items);
			if (gKeyTrg & KEY_S)
				mode = GAMEMODE_GAMEPLAY;
			
			//Run event and draw status
			EventScriptProc(&event_scr, &items, npc, &map, &piyocont, &fade, &frame);
			PutMsgBox(&event_scr);
			PutMyStatus();
			
			//End frame
			if (!Flip_SystemTask_IKA())
				return true;
			PiyoPiyoProc();
		}
		
		//Editor
		while (mode == GAMEMODE_EDITOR)
		{
			ProcessSystemEvent(NULL);
			/*SDL_Event e;
			while (SDL_PollEvent(&e)) {
				ProcessSystemEvent(&e);
				if (e.type == SDL_QUIT) {
					return true;
				}
			}*/
			//Start frame
			tick = clock();
			GetTrg();
			CortBox(&grcFull, 0x000000);
			
			//Save NPCs if S is pressed
			if (gKeyTrg & KEY_S)
				SaveNpChar(npc);
			
			//Move frame and draw map
			MoveFrameEditor(&frame, &map);
			PutMapBack(&map, frame.x, frame.y);
			PutNpChar(npc, &frame);
			PutMapFront(&map, frame.x, frame.y);
			PutMapVector(&map, frame.x, frame.y);
			
			//Run editor
			EditorProc(npc);
			PutEditorSelect(npc, &frame);
			PutEditorNpcInfo(npc);
			PutEditorCursor();
			
			//Run event (why?)
			EventScriptProc(&event_scr, &items, npc, &map, &piyocont, &fade, &frame);
			PutMsgBox(&event_scr);
			
			//End frame
			if (!Flip_SystemTask_IKA())
				return true;
		}
	}
	
	//Play ending theme
	piyocont.track = 5;
	piyocont.mode = 1;
	PiyoPiyoControl(&piyocont);
	
	//Load staff script
	sprintf(path, "%s/%s", gModulePath, "Staff.ptx");
	LoadPixelScript(&pix_scr, path, 4);
	
	//Staff
	while (mode == GAMEMODE_STAFF)
	{
		ProcessSystemEvent(NULL);
		/*SDL_Event e;
		while (SDL_PollEvent(&e)) {
			ProcessSystemEvent(&e);
			if (e.type == SDL_QUIT) {
				return true;
			}
		}*/
		//Start frame
		tick = clock();
		PiyoPiyoControl(&piyocont);
		GetTrg();
		CortBox(&grcFull, 0x000000);
		
		//Run Pixel Script
		PixelScriptProc(&pix_scr, &piyocont, true);
		
		//End frame
		if (!Flip_SystemTask_IKA())
			return true;
		PiyoPiyoProc();
	}
	return false;
}
