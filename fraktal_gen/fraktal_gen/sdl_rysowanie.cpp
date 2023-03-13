#include <SDL.h>
#include <ctime>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stack>









double k = 45;










using namespace std;
SDL_Event zdarzenie;
SDL_Renderer* renderer;
SDL_Window* window;
const int width = 1920;
const int height = 1080;
int n = 0;
double b;
double xwsk = 360;
double ywsk = 1060;
double kwsk;
double wsp = sqrt(2);
void rys_pkt(double x, double y);
void forward(double bok);
void right(double kat);
void left(double kat);
void back(double bok);
bool jest(char z, vector<char> v);
void clear();
void rys_pkty(double x1, double x2, double y1, double y2);
void rys_gcir(int x, int y, int r);
void rys_rcir(int x, int y, int r);



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    
	window = SDL_CreateWindow("okno", 0, 0, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//SDL_RenderDrawPoint(renderer, 5, 5);
	SDL_RenderPresent(renderer);
	bool zmiana;

	do
	{
		b = 10;
		xwsk = 360;
		ywsk = 1060;
		kwsk = 0;
		zmiana = false;
		{
			vector <char> v;
			vector <char> c;
			string s;
			map <char, string> r;

			ifstream var("var.txt");
			ifstream cons("cons.txt");
			ifstream start("start.txt");
			ifstream rules("rules.txt");


			char z;
			string l;
			if (var && cons && start && rules)
			{
				while (var >> z)
				{
					v.push_back(z);
				}

				while (cons >> z)
				{
					c.push_back(z);
				}

				getline(start, s);

				while (rules >> z)
				{
					getline(rules, l);
					getline(rules, l);
					r[z] = l;
				}
				var.close();
				cons.close();
				start.close();
				rules.close();
			}




			int i, j;

			for (i = 0; i < n; i++)
			{
				string instr;
				for (j = 0; j < s.size(); j++)
				{
					if (jest(s[j], v))
					{
						instr += r[s[j]];
					}
					else
					{
						instr += s[j];
					}
				}
				s = instr;
			}
			
			double maxx = 0;
			double minx = width;
			double maxy = 0;
			double miny = height;
			double poczx = xwsk;
			double poczy = ywsk;
			double poczk = kwsk;

			if (maxx < xwsk)
			{
				maxx = xwsk;
			}
			if (minx > xwsk)
			{
				minx = xwsk;
			}
			if (maxy < ywsk)
			{
				maxy = ywsk;
			}
			if (miny > ywsk)
			{
				miny = ywsk;
			}


			{
				stack<vector<double>>stos;
				vector<double> vec{ 0,0,0 };
				double w = 1;
				for (i = 0; i < s.size(); i++)
				{
					switch (s[i])
					{
					case'A':
						forward(b * w);
						break;
					case'B':
						forward(b * w);
						break;
					case'C':
						forward(b * w);
						break;
					case'D':

						break;
					case'E':

						break;
					case'F':

						break;
					case'G':

						break;
					case's':
						w *= wsp;
						break;
					case'r':
						w /= wsp;
						break;
					case'+':
						left(k);
						break;
					case'-':
						right(k);
						break;

					case'[':
						vec[0] = xwsk;
						vec[1] = ywsk;
						vec[2] = kwsk;
						stos.push(vec);
						break;
					case']':
						vec = stos.top();
						xwsk = vec[0];
						ywsk = vec[1];
						kwsk = vec[2];
						stos.pop();
						break;
					}
					if (maxx < xwsk)
					{
						maxx = xwsk;
					}
					if (minx > xwsk)
					{
						minx = xwsk;
					}
					if (maxy < ywsk)
					{
						maxy = ywsk;
					}
					if (miny > ywsk)
					{
						miny = ywsk;
					}
					//SDL_RenderPresent(renderer);
				}
			}


			double dlgx = maxx - minx;
			double dlgy = maxy - miny;

			double stosunek = ((width - 50) / dlgx) < ((height - 50) / dlgy) ? ((width - 50) / dlgx) : ((height - 50) / dlgy);

			b = floor(b * stosunek);

			xwsk = poczx - ((poczx - (poczx - minx) * stosunek + (maxx - poczx) * stosunek + poczx) / 2 - width / 2);
			ywsk = poczy - ((poczy - (poczy - miny) * stosunek + (maxy - poczy) * stosunek + poczy) / 2 - height / 2);
			kwsk = poczk;
			
			clear();
			{
				stack<vector<double>>stos;
				vector<double> vec{ 0,0,0 };
				double w = 1;
				for (i = 0; i < s.size(); i++)
				{
					switch (s[i])
					{
					case'A':
						forward(b * w);
						break;
					case'B':
						forward(b * w);
						break;
					case'C':
						forward(b * w);
						break;
					case'D':
						
						break;
					case'E':
						
						break;
					case'F':

						break;
					case'G':

						break;
					case's':
						w *= wsp;
						break;
					case'r':
						w /= wsp;
						break;
					case'+':
						left(k);
						break;
					case'-':
						right(k);
						break;
					case'[':
						vec[0] = xwsk;
						vec[1] = ywsk;
						vec[2] = kwsk;
						stos.push(vec);
						break;
					case']':
						vec = stos.top();
						xwsk = vec[0];
						ywsk = vec[1];
						kwsk = vec[2];
						stos.pop();
						break;
					}
					if (maxx < xwsk)
					{
						maxx = xwsk;
					}
					if (minx > xwsk)
					{
						minx = xwsk;
					}
					if (maxy < ywsk)
					{
						maxy = ywsk;
					}
					if (miny > ywsk)
					{
						miny = ywsk;
					}
					//SDL_RenderPresent(renderer);
				}
			}


			SDL_RenderPresent(renderer);
		}

		rys_gcir(10, 10, 30);
		bool kon = false;

		while (!kon)
		{
			while (SDL_PollEvent(&zdarzenie))
			{
				if (zdarzenie.type == SDL_KEYDOWN)
				{
					switch (zdarzenie.key.keysym.sym)
					{
					case SDLK_SPACE:

						kon = true;
						break;
					case SDLK_RIGHT:

						n++;
						zmiana = true;
						kon = true;
						break;
					case SDLK_LEFT:

						n--;
						zmiana = true;
						kon = true;
						break;
					case SDLK_UP:

						k = k + 5;
						zmiana = true;
						kon = true;
						break;
					case SDLK_DOWN:

						k = k - 5;
						zmiana = true;
						kon = true;
						break;
					}
				}
			}
		}
		rys_rcir(10, 10, 30);
	} while (zmiana);
	
	

	


    SDL_Quit();
    return 0;
}





bool jest(char z, vector<char> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (z == v[i])
		{
			return true;
		}
	}
	return false;
}


void forward(double bok)
{
	if (kwsk == 90 || kwsk == 270)
	{
		int przes = (kwsk / 90) - 2;
		int bok2;
		if (ceil(bok) - bok < bok - floor(bok))
		{
			bok2 = ceil(bok);
		}
		else
		{
			bok2 = floor(bok);
		}

		for (int i = 0; i < bok2 + 1; i++)
		{
			rys_pkt(xwsk, ywsk + (i) * przes);
		}

		ywsk = ywsk + bok * przes;
		//SDL_RenderPresent(renderer);
	}
	else
	{

		double kat = kwsk * 2 * 3.14159265 / 360;
		double wsp = tan(kat);
		double dlug;
		dlug = abs(bok * cos(kat));
		if (ceil(dlug) - dlug < dlug - floor(dlug))
		{
			bok = ceil(dlug);
		}
		else
		{
			bok = floor(dlug);
		}

		double x = xwsk, y = ywsk;
		rys_pkt(xwsk, ywsk);
		if (kwsk > 90 && kwsk < 270)
		{
			if (kwsk > 135 && kwsk < 225)
			{

				for (int i = 0; i < bok; i++)
				{

					x--;
					y += wsp;

					rys_pkt(x, y);

				}
			}
			else
			{
				dlug = abs(dlug / cos(kat));
				dlug = abs(dlug * sin(kat));
				if (ceil(dlug) - dlug < dlug - floor(dlug))
				{
					bok = ceil(dlug);
				}
				else
				{
					bok = floor(dlug);
				}

				for (int i = 0; i < bok; i++)
				{
					if (kwsk > 135)
					{
						y++;
						x -= 1 / wsp;
					}
					else
					{
						y--;
						x += 1 / wsp;
					}


					rys_pkt(x, y);

				}

				dlug = abs(dlug / sin(kat));
				dlug = abs(dlug * cos(kat));

			}

		}
		else
		{
			if (kwsk > 45 && kwsk < 315)
			{

				dlug = abs(dlug / cos(kat));
				dlug = abs(dlug * sin(kat));
				if (ceil(dlug) - dlug < dlug - floor(dlug))
				{
					bok = ceil(dlug);
				}
				else
				{
					bok = floor(dlug);
				}

				for (int i = 0; i < bok; i++)
				{
					if (kwsk < 91)
					{
						y--;
						x += 1 / wsp;
					}
					else
					{
						y++;
						x -= 1 / wsp;
					}


					rys_pkt(x, y);

				}

				dlug = abs(dlug / sin(kat));
				dlug = abs(dlug * cos(kat));

			}
			else
			{
				for (int i = 0; i < bok; i++)
				{

					x++;
					y -= wsp;
					rys_pkt(x, y);
				}
			}


		}
		dlug = abs(dlug / cos(kat));

		xwsk += dlug * cos(kat);
		ywsk -= dlug * sin(kat);

		//SDL_RenderPresent(renderer);



	}
}







void right(double kat)
{
	kwsk = kwsk - kat;
	while (kwsk < 0)
	{
		kwsk += 360;
	}
}


void left(double kat)
{
	kwsk = kwsk + kat;

	while (kwsk >= 360)
	{
		kwsk -= 360;
	}
}



void back(double bok)
{
	right(180);
	forward(bok);
	right(180);
}

void rys_pkt(double x, double y)
{
	if (ceil(x) - x < x - floor(x))
	{
		if (ceil(y) - y < y - floor(y))
		{
			SDL_RenderDrawPoint(renderer, ceil(x), ceil(y));
		}
		else
		{
			SDL_RenderDrawPoint(renderer, ceil(x), floor(y));
		}
	}
	else
	{
		if (ceil(y) - y < y - floor(y))
		{
			SDL_RenderDrawPoint(renderer, floor(x), ceil(y));
		}
		else
		{
			SDL_RenderDrawPoint(renderer, floor(x), floor(y));
		}
	}
}

void clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}

	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


/*
void forward(double bok)
{
	double poczxwsk = xwsk;
	double poczywsk = ywsk;

	double kat = kwsk * 2 * 3.14159265 / 360;
	xwsk += cos(kat) * bok;
	ywsk -= sin(kat) * bok;
	rys_pkty(poczxwsk, xwsk, poczywsk, ywsk);
}


void rys_pkty(double x1, double x2, double y1, double y2)
{
	if (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) > 1)
	{
		rys_pkty(x1, (x1 + x2) / 2, y1, (y1 + y2) / 2);
		rys_pkty((x1 + x2) / 2, x2, (y1 + y2) / 2, y2);
	}
	else
	{
		rys_pkt(x1, y1);
		rys_pkt(x2, y2);
	}
}
*/



void rys_gcir(int x, int y, int r)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (int i = 0; i < 2 * r + 1; i++)
	{
		for (int j = 0; j < 2 * r + 1; j++)
		{
			if (sqrt((r - i) * (r - i) + (r - j) * (r - j) <= r))
			{
				SDL_RenderDrawPoint(renderer, i + x, j + y);
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}

void rys_rcir(int x, int y, int r)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < 2 * r + 1; i++)
	{
		for (int j = 0; j < 2 * r + 1; j++)
		{
			if (sqrt((r - i) * (r - i) + (r - j) * (r - j) <= r))
			{
				SDL_RenderDrawPoint(renderer, i + x, j + y);
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderPresent(renderer);
}