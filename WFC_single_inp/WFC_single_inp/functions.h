#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <ctime>
#include <tuple>
#include <iostream>
#include <set>

using namespace std;

void get_bit_color(int x, int y, SDL_Surface* s, int& r, int& g, int& b);

string rev(string s);

void draw_rect(int x, int y, int w, int h, SDL_Renderer* r);

;

template <typename W>
void shuffle(vector<W> &v)
{
    int r;
    W temp;
    for (int i = 0; i < v.size(); i++)
    {
        r = rand() % (v.size() - i) + i;
        temp = v[i];
        v[i] = v[r];
        v[r] = temp;
    }
}

struct colour
{
    int r;
    int g;
    int b;
    colour() :r(70), g(70), b(70) {};
    colour(int _r, int _g, int _b) :r(_r), g(_g), b(_b) {};
    bool operator==(colour c) { return (r == c.r && g == c.g && b == c.b); }
};