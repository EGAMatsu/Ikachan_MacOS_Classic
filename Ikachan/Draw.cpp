#include "Draw.h"
#include "FakeRect.h"
//#include <ddraw.h>
#include <SDL2/SDL.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

//Global cliprect
RECT grcFull = { 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT };

//Draw state
int mag;
bool fullscreen;

//DirectDraw objects
// LPDIRECTDRAW lpDD;
// LPDIRECTDRAWSURFACE frontbuffer;
// LPDIRECTDRAWSURFACE backbuffer;
// LPDIRECTDRAWCLIPPER clipper;

//"DirectDraw" objects
SDL_Renderer *renderer;

//Surfaces
#define MAX_SURFACE 512
// LPDIRECTDRAWSURFACE surf[MAX_SURFACE] = {NULL};
SDL_Texture* surf[MAX_SURFACE] = {NULL};

//Loaded font
// HFONT font;

//Window rect and size
RECT backbuffer_rect;
int scaled_window_width;
int scaled_window_height;

//Client
int client_x;
int client_y;

void SetClientOffset(int width, int height)
{
	client_x = width;
	client_y = height;
}

#if 0
//End of frame function
bool Flip_SystemTask(HWND hWnd)
{
	//Run system tasks while waiting for next frame
	static unsigned long timePrev;
	while (GetTickCount() < (timePrev + 20))
	{
		Sleep(1);
		if (!SystemTask())
			return false;
	}

	if ((timePrev + 100) < GetTickCount())
		timePrev = GetTickCount();
	else
		timePrev += 20;
	
	//Blit backbuffer to front buffer
	RECT dst_rect;
	GetWindowRect(hWnd, &dst_rect);
	dst_rect.left += client_x;
	dst_rect.top += client_y;
	dst_rect.right = dst_rect.left + scaled_window_width;
	dst_rect.bottom = dst_rect.top + scaled_window_height;
	frontbuffer->Blt(&dst_rect, backbuffer, &backbuffer_rect, DDBLT_WAIT, NULL);
	return true;
}

//DirectDraw interface
bool StartDirectDraw(HWND hWnd, int wndSize)
{
	//Create DirectDraw instance
	if (DirectDrawCreate(NULL, &lpDD, NULL) != DD_OK)
		return false;

	//Set cooperative level
	switch (wndSize)
	{
		case WS_FULLSCREEN:
			mag = 2;
			fullscreen = true;
			lpDD->SetCooperativeLevel(hWnd, DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE);
			lpDD->SetDisplayMode(SURFACE_WIDTH * mag, SURFACE_HEIGHT * mag, 16);
			break;
		case WS_320x240:
			mag = 1;
			fullscreen = false;
			lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
			break;
		case WS_640x480:
			mag = 2;
			fullscreen = false;
			lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
			break;
	}

	//Initialize window rects and sizes
	backbuffer_rect.left = 0;
	backbuffer_rect.top = 0;
	backbuffer_rect.right = SURFACE_WIDTH * mag;
	backbuffer_rect.bottom = SURFACE_HEIGHT * mag;

	scaled_window_width = SURFACE_WIDTH * mag;
	scaled_window_height = SURFACE_HEIGHT * mag;

	//Create screen buffers
	DDSURFACEDESC ddsd;

	//Frontbuffer
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	ddsd.dwBackBufferCount = 0;

	if (lpDD->CreateSurface(&ddsd, &frontbuffer, NULL) != DD_OK)
		return false;

	//Backbuffer
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = SURFACE_WIDTH * mag;
	ddsd.dwHeight = SURFACE_HEIGHT * mag;

	if (lpDD->CreateSurface(&ddsd, &backbuffer, NULL) != DD_OK)
		return false;

	//Create clipper
	lpDD->CreateClipper(0, &clipper, NULL);
	clipper->SetHWnd(0, hWnd);
	frontbuffer->SetClipper(clipper);
	return true;
}

void EndDirectDraw(HWND hWnd)
{
	//Release surfaces
	for (int i = 0; i < MAX_SURFACE; i++)
	{
		if (surf[i] != NULL)
		{
			surf[i]->Release();
			surf[i] = NULL;
		}
	}

	//Release frontbuffer
	if (frontbuffer != NULL)
		frontbuffer->Release();

	//Exit fullscreen
	if (fullscreen)
		lpDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);

	//Release DirectDraw instance
	if (lpDD != NULL)
		lpDD->Release();
}
#endif

//End of frame function
bool Flip_SystemTask()
{
	//Run system tasks while waiting for next frame
	static unsigned long timePrev;
	while (SDL_GetTicks() < (timePrev + 20))
	{
		SDL_Delay(1);
		if (!SystemTask())
			return false;
	}

	if ((timePrev + 100) < SDL_GetTicks())
		timePrev = SDL_GetTicks();
	else
		timePrev += 20;
	
	SDL_RenderPresent(renderer);
	return true;
}

bool StartDirectDraw(SDL_Window *window, int wndSize)
{
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
	// Create SDL renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "SDL create renderer fail: %s\n", SDL_GetError());
		return false;
	}

	// TODO scaling options (1x for now)
	mag = 1;

	return true;
}
//Surface creation
bool MakeSurface_File(const char* name, int surf_no) //TODO: implement
{
#if 0
	//Get path
	char path[MAX_PATH];
	sprintf(path, "%s/%s", gModulePath, name);
	
	//Make sure a surface can be made here
	if (surf_no > MAX_SURFACE)
		return false;
	if (surf[surf_no] != NULL)
		return false;
	
	//Load image
	HANDLE handle = LoadImage(GetModuleHandle(NULL), path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (handle == NULL)
		return false;

	BITMAP bitmap;
	GetObjectA(handle, sizeof(BITMAP), &bitmap);

	//Get surface descriptor
	DDSURFACEDESC ddsd;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = bitmap.bmWidth * mag;
	ddsd.dwHeight = bitmap.bmHeight * mag;
	lpDD->CreateSurface(&ddsd, &surf[surf_no], NULL);

	//Scale image
	int src_x = 0;
	int src_y = 0;
	int src_w = bitmap.bmWidth;
	int src_h = bitmap.bmHeight;

	int dst_x = 0;
	int dst_y = 0;
	int dst_w = bitmap.bmWidth * mag;
	int dst_h = bitmap.bmHeight * mag;

	HDC hdc = CreateCompatibleDC(NULL);
	HGDIOBJ hgdiobj = SelectObject(hdc, handle);

	HDC hdc2;
	surf[surf_no]->GetDC(&hdc2);
	StretchBlt(hdc2, dst_x, dst_y, dst_w, dst_h, hdc, src_x, src_y, src_w, src_h, SRCCOPY);
	surf[surf_no]->ReleaseDC(hdc2);

	SelectObject(hdc, hgdiobj);
	DeleteDC(hdc);

	//Set surface colour key
	DDCOLORKEY ddcolorkey;
	ddcolorkey.dwColorSpaceLowValue = 0;
	ddcolorkey.dwColorSpaceHighValue = 0;
	surf[surf_no]->SetColorKey(DDCKEY_SRCBLT, &ddcolorkey);

	//Release image handle
	DeleteObject(handle);
	return true;
#else
	fprintf(stderr, "unfinished function: %s\n", __PRETTY_FUNCTION__);

	//Get path
	char path[MAX_PATH];
	sprintf(path, "%s/%s", gModulePath, name);
	
	//Make sure a surface can be made here
	if (surf_no > MAX_SURFACE)
		return false;
	if (surf[surf_no] != NULL)
		return false;
	
	//Load image
	SDL_Surface *s = SDL_LoadBMP(path);
	if (s == NULL)
		return false;

	//Scale image (TODO unsupported yet!)
	int src_x = 0;
	int src_y = 0;
	int src_w = s->w;
	int src_h = s->h;

	int dst_x = 0;
	int dst_y = 0;
	int dst_w = s->w * mag;
	int dst_h = s->h * mag;

	//Set surface colour key
	SDL_SetColorKey(s, SDL_TRUE, 0);

	surf[surf_no] = SDL_CreateTextureFromSurface(renderer, s);

	//Release image handle
	SDL_FreeSurface(s);
	return true;
#endif
}

bool MakeSurface_Generic(int bxsize, int bysize, int surf_no)
{
#if 0
	//Make sure a surface can be made here
	if (surf_no > MAX_SURFACE)
		return false;
	if (surf[surf_no] != NULL)
		return false;

	//Create surface
	DDSURFACEDESC ddsd;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize = sizeof(DDSURFACEDESC);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = bxsize * mag;
	ddsd.dwHeight = bysize * mag;
	lpDD->CreateSurface(&ddsd, &surf[surf_no], NULL);

	//Set surface colour key
	DDCOLORKEY ddcolorkey;
	ddcolorkey.dwColorSpaceLowValue = 0;
	ddcolorkey.dwColorSpaceHighValue = 0;
	surf[surf_no]->SetColorKey(DDCKEY_SRCBLT, &ddcolorkey);
	return true;
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
	return false;
#endif
}

//Backbuffer backup
void BackupSurface(int surf_no, const RECT *rect)
{
#if 0
	//Construct rect descriptor
	DDBLTFX ddbltfx;
	memset(&ddbltfx, 0, sizeof(DDBLTFX));
	ddbltfx.dwSize = sizeof(DDBLTFX);
	
	//Magnify rect
	RECT rcSet;
	rcSet.left = rect->left * mag;
	rcSet.top = rect->top * mag;
	rcSet.right = rect->right * mag;
	rcSet.bottom = rect->bottom * mag;
	
	//Blit backbuffer to destination surface
	surf[surf_no]->Blt(&rcSet, backbuffer, &rcSet, DDBLT_WAIT, &ddbltfx);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

//Bitmap
void PutBitmap3(const RECT *rcView, int x, int y, const RECT *rect, int surf_no)
{
	//Clip source rect
	RECT rcWork = *rect;
	if (x + rect->right - rect->left > rcView->right)
		rcWork.right -= (x + rect->right - rect->left) - rcView->right;
	if (x < rcView->left)
	{
		rcWork.left += rcView->left - x;
		x = rcView->left;
	}
	if (y + rect->bottom - rect->top > rcView->bottom)
		rcWork.bottom -= (y + rect->bottom - rect->top) - rcView->bottom;
	if (y < rcView->top)
	{
		rcWork.top += rcView->top - y;
		y = rcView->top;
	}

	//Get destination rect
	RECT rcSet;
	rcSet.left = x;
	rcSet.top = y;
	rcSet.right = x + rcWork.right - rcWork.left;
	rcSet.bottom = y + rcWork.bottom - rcWork.top;

	//Multiply rects
	rcWork.left *= mag;
	rcWork.top *= mag;
	rcWork.right *= mag;
	rcWork.bottom *= mag;

	rcSet.left *= mag;
	rcSet.top *= mag;
	rcSet.right *= mag;
	rcSet.bottom *= mag;

	//Blit surface
	SDL_Rect srcr = FakeRect_to_SDLRect(rcWork);
	SDL_Rect dstr = FakeRect_to_SDLRect(rcSet);
	SDL_RenderCopy(renderer, surf[surf_no], &srcr, &dstr);
}

//Cort box (TODO)
void CortBox(const RECT *rect, unsigned long col)
{
#if 0
	//Construct rect descriptor
	static DDBLTFX ddbltfx;
	memset(&ddbltfx, 0, sizeof(DDBLTFX));
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = col;

	static RECT rcSet;
	rcSet.left = rect->left * mag;
	rcSet.top = rect->top * mag;
	rcSet.right = rect->right * mag;
	rcSet.bottom = rect->bottom * mag;

	//Blit rect
	backbuffer->Blt(&rcSet, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);

	SDL_SetRenderDrawColor(renderer, col & 0xFF, (col & 0xFF00) >> 8, (col & 0xFF0000) >> 16, (col & 0xFF000000) >> 24);
	static RECT rcSet;
	rcSet.left = rect->left * mag;
	rcSet.top = rect->top * mag;
	rcSet.right = rect->right * mag;
	rcSet.bottom = rect->bottom * mag;
	static SDL_Rect sr = FakeRect_to_SDLRect(rcSet);

	//Blit rect
	SDL_RenderFillRect(renderer, &sr);
#endif
}

// TODO
void CortBox2(const RECT *rect, unsigned long col, int surf_no)
{
#if 0
	//Construct rect descriptor
	static DDBLTFX ddbltfx;
	memset(&ddbltfx, 0, sizeof(DDBLTFX));
	ddbltfx.dwSize = sizeof(DDBLTFX);
	ddbltfx.dwFillColor = col;

	static RECT rcSet;
	rcSet.left = rect->left * mag;
	rcSet.top = rect->top * mag;
	rcSet.right = rect->right * mag;
	rcSet.bottom = rect->bottom * mag;

	//Blit rect
	surf[surf_no]->Blt(&rcSet, 0, 0, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

//Text (TODO)
void InitTextObject(const char* name)
{
#if 0
	//Get font width and height
	unsigned int width, height;
	switch (mag)
	{
		case 1:
			height = 12;
			width = 6;
			break;
		case 2:
			height = 20;
			width = 10;
			break;
	}

	//Create font object
	font = CreateFont(height, width, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, name);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void PutText(int x, int y, const char* text, unsigned long color, bool unk) // TODO
{
#if 0
	//Lock backbuffer
	HDC hdc;
	backbuffer->GetDC(&hdc);

	//Draw text onto backbuffer
	HGDIOBJ hgdiobj = SelectObject(hdc, font);
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);
	TextOut(hdc, x * mag, y * mag, text, (int)strlen(text));
	SelectObject(hdc, hgdiobj);

	//Unlock backbuffer
	backbuffer->ReleaseDC(hdc);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void PutText2(int x, int y, const char* text, unsigned long color, int surf_no, bool unk)
{
#if 0
	//Lock surface
	HDC hdc;
	surf[surf_no]->GetDC(&hdc);

	//Draw text onto surface
	HGDIOBJ hgdiobj = SelectObject(hdc, font);
	SetBkMode(hdc, 1);
	SetTextColor(hdc, color);
	TextOut(hdc, x * mag, y * mag, text, (int)strlen(text));
	SelectObject(hdc, hgdiobj);

	//Unlock surface
	surf[surf_no]->ReleaseDC(hdc);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void EndTextObject()
{
	// DeleteObject(font);
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
}
