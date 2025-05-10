#include "FakeRect.h"

SDL_Rect FakeRect_to_SDLRect(RECT r)
{
    SDL_Rect out = {0, 0, 0, 0};

    out.x = r.left;
    out.y = r.top;
    out.w = r.right - out.x;
    out.h = r.bottom - out.y;

    return out;
}
