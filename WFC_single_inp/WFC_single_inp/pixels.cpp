#include "pixels.h"


pixels::pixels(SDL_Surface* s)
{
	for (int i = 0; i < s->h; i++)
	{
		vector<colour> vec_temp;
		colour col_temp;
		for (int j = 0; j < s->w; j++)
		{
			get_bit_color(j, i, s, col_temp.r, col_temp.g, col_temp.b);
			vec_temp.push_back(col_temp);
		}
		arr.push_back(vec_temp);
	}
}

pixels::pixels(int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		vector<colour> vec_temp;
		colour col_temp;
		for (int j = 0; j < w; j++)
			vec_temp.push_back(col_temp);
		arr.push_back(vec_temp);
	}
}

int pixels::width()
{
	return arr[0].size();
}
int pixels::height()
{
	return arr.size();
}

pixels pixels::get_fragment(int x, int y, int w, int h)
{
	pixels temp(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			temp.arr[j][i] = arr[y + j][x + i];
		}
	}
	return temp;
}

pixels pixels::rotate()
{
	if (arr.size() != arr[0].size())
		exit(0);
	pixels temp(arr.size(), arr.size());
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr.size(); j++)
		{
			temp.arr[i][j] = arr[arr.size() - 1 - j][i];
		}
	}
	return temp;
}

void pixels::draw(SDL_Renderer* r, int scale)
{
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[0].size(); j++)
		{
			SDL_SetRenderDrawColor(r, arr[i][j].r, arr[i][j].g, arr[i][j].b, 255);
			draw_rect(j * scale, i * scale, scale, scale, r);
		}
	}
	SDL_RenderPresent(r);
}

void pixels::draw_frag(SDL_Renderer* r, int scale, int x, int y, int w, int h)
{
	for (int i = y; i < h + y; i++)
	{
		for (int j = x; j < w + x; j++)
		{
			SDL_SetRenderDrawColor(r, arr[i][j].r, arr[i][j].g, arr[i][j].b, 255);
			draw_rect(j * scale, i * scale, scale, scale, r);
		}
	}
	SDL_RenderPresent(r);
}

void pixels::set_pixel(int x, int y, colour c)
{
	arr[y][x] = c;
}

bool pixels::the_same(pixels p)
{
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[0].size(); j++)
		{
			if (!(arr[i][j] == p.arr[i][j]))
				return false;
		}
	}
	return true;
}

pixels pixels::ubdate_output(pixels input, int x, int y)
{
	pixels output2(*this);
	for (int i = 0; i < input.width(); i++)
	{
		for (int j = 0; j < input.width(); j++)
		{
			output2.arr[i + y][j + x] = input.arr[i][j];
		}
	}
	return output2;
}

colour pixels::get_pixel(int x, int y)
{
	return arr[y][x];
}



void pixels::reset_frag(SDL_Renderer* r, int scale, int x, int y, int w, int h)
{
	for (int i = y; i < h + y; i++)
	{
		for (int j = x; j < w + x; j++)
		{
			SDL_SetRenderDrawColor(r, 70, 70, 70, 255);
			draw_rect(j * scale, i * scale, scale, scale, r);
		}
	}
	SDL_RenderPresent(r);
}
