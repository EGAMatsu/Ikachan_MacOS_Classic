#pragma once

#include <SDL2/SDL.h>

typedef struct fakeRECT
{
    long left;
    long top;
    long right;
    long bottom;
} RECT;

SDL_Rect FakeRect_to_SDLRect(RECT r);
