#include "functions.h"

void get_bit_color(int x, int y, SDL_Surface* s, int& r, int& g, int& b)
{
    //SDL_LockSurface(s);
    Uint8* p = (Uint8*)s->pixels + y * s->pitch + x * s->format->BytesPerPixel;
    //SDL_UnlockSurface(s);
    SDL_Color rgb;
    SDL_GetRGB(p[0] | p[1] << 8 | p[2] << 16, s->format, &rgb.r, &rgb.g, &rgb.b);
    r = unsigned(rgb.r);
    g = unsigned(rgb.g);
    b = unsigned(rgb.b);
}

string rev(string s)
{
    string rs;
    for (int i = s.size() - 1; i >= 0; i--)
        rs += s[i];
    return rs;
}

void draw_rect(int x, int y, int w, int h, SDL_Renderer* r)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            SDL_RenderDrawPoint(r, x + j, y + i);
        }
    }
}
