#include "Draw.h"
#include "FakeRect.h"
//#include <ddraw.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

//Global cliprect
RECT grcFull = { 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT };

//Draw state
int mag;
bool fullscreen;

/* Rendering */
#define MAX_SURFACE 512
BitMap surf[MAX_SURFACE];     // 1-bit surfaces
Ptr    surfData[MAX_SURFACE]; // backing memory for each bitmap

GrafPtr renderer = NULL;      // destination port

//Loaded font
// HFONT font;

//Window rect and size
Rect backbuffer_rect;
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

/* Helpers */
bool CreateSurface(int index, short width, short height)
{
    long rowBytes = ((width + 15) >> 4) << 1; // 16-bit aligned
    long size = rowBytes * height;

    surfData[index] = NewPtr(size);
    if (!surfData[index])
        return false;

    surf[index].baseAddr = surfData[index];
    surf[index].rowBytes = rowBytes;
    SetRect(&surf[index].bounds, 0, 0, width, height);
    return true;
}

void DrawSurface(int index, const Rect *srcRect, const Rect *dstRect)
{
    CopyBits(&surf[index], &renderer->portBits,
             srcRect, dstRect, srcCopy, NULL);
}


//End of frame function
bool Flip_SystemTask_IKA()
{
	/* TODO: IMPLEMENT */
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
	return true;
}

/* Create window */
bool StartDirectDraw(WindowPtr window, int wndSize)
{
    renderer = &((WindowPeek)window)->port;
    SetPort(renderer);

    switch (wndSize)
    {
        case WS_FULLSCREEN: mag = 2; fullscreen = true; break;
        case WS_320x240:    mag = 1; fullscreen = false; break;
        case WS_640x480:    mag = 2; fullscreen = false; break;
    }

    scaled_window_width  = SURFACE_WIDTH * mag;
    scaled_window_height = SURFACE_HEIGHT * mag;

    SetRect(&backbuffer_rect, 0, 0, scaled_window_width, scaled_window_height);

    return CreateSurface(0, scaled_window_width, scaled_window_height);
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
#endif

	return false;
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
	/* TODO: IMPLEMENT */
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
}

//Cort box
void CortBox(const RECT *rect, unsigned long col)
{
	/* TODO: IMPLEMENT */
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
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
