#pragma once
#include "functions.h"


using namespace std;

class pixels
{
private:
	vector<vector<colour>> arr;
public:
	pixels(SDL_Surface* s);
	pixels(int w, int h);
	int width();
	int height();
	pixels get_fragment(int x, int y, int w, int h);
	pixels rotate();
	void draw(SDL_Renderer* r, int scale);
	void draw_frag(SDL_Renderer* r, int scale, int x, int y, int w, int h);
	void reset_frag(SDL_Renderer* r, int scale, int x, int y, int w, int h);
	void set_pixel(int x, int y, colour c);
	colour get_pixel(int x, int y);
	pixels ubdate_output(pixels input, int x, int y);
	bool the_same(pixels p);
};

