// sdl_rysowanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <SDL.h>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

SDL_Renderer* renderer;
SDL_Window* window;
SDL_Event zdarzenie;


SDL_Surface* win_surface;


SDL_Surface* input;
SDL_Surface* output;
SDL_Surface* b;
SDL_Surface* w;


SDL_Texture* texture;
SDL_Texture* texture_i;
SDL_Texture* texture_o;

SDL_Rect* rect1;
SDL_Rect* rect2;

const int WIDTH = 1500;
const int HEIGHT = 800;

const string INPUT = "input.bmp";
const string OUTPUT = "output.bmp";
const string B = "b.bmp";
const string W = "w.bmp";

void f1()
{
    for (int k = 0; k < 100; k++)
    {
        rect1->y++;
        rect1->x++;
        rect1->w -= 2;
        rect1->h -= 2;
        texture = SDL_CreateTextureFromSurface(renderer, input);
        SDL_RenderCopy(renderer, texture, rect1, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
}

void f2()
{
    for (int i = 0; i < 10000; i++)
    {
        cout << i << endl;
    }
}


void f(string name)
{
    // Create an empty RGB surface that will be used to create the screenshot bmp file
    SDL_Surface* pScreenShot = SDL_CreateRGBSurface(0, output->w, output->h, output->format->BytesPerPixel, output->format->Rmask, output->format->Gmask, output->format->Bmask, output->format->Amask);
    //pScreenShot = SDL_ConvertSurface(pScreenShot, output->format, 0);
    if (pScreenShot)
    {
        // Read the pixels from the current render target and save them onto the surface
        SDL_RenderReadPixels(renderer, NULL, 0, pScreenShot->pixels, pScreenShot->pitch);

        // Create the bmp screenshot file
        SDL_SaveBMP(pScreenShot, name.c_str());

        // Destroy the screenshot surface
        SDL_FreeSurface(pScreenShot);
    }


}


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

void draw_pix(SDL_Surface* s, int r, int g, int b)
{

}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    

    input = SDL_LoadBMP(INPUT.c_str());
    output = SDL_LoadBMP(OUTPUT.c_str());

    w = SDL_LoadBMP(B.c_str());
    b = SDL_LoadBMP(W.c_str());



    window = SDL_CreateWindow("out", 50, 100, output->w, output->h, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);



    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderFillRect(renderer, NULL);
    SDL_RenderPresent(renderer);
    SDL_RenderDrawPoint(renderer, 1, 1);


    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    w = SDL_ConvertSurface(w, output->format, 0);
    b = SDL_ConvertSurface(b, output->format, 0);


    


    rect1 = new SDL_Rect;

    //for (int i = 0; i < 200; i++)
    //{
    //    for (int j = 0; j < output->w; j++)
    //    {
    //        rect1->x = j;
    //        for (int k = 0; k < output->h; k++)
    //        {
    //            rect1->y = k;
    //            if(k%2)
    //                SDL_BlitSurface(b, NULL, output, rect1);
    //            else
    //                SDL_BlitSurface(w, NULL, output, rect1);
    //        }
    //        //std::cout << j;
    //    }
    //    texture = SDL_CreateTextureFromSurface(renderer, input);
    //    SDL_RenderCopy(renderer, texture, NULL, NULL);
    //    SDL_RenderPresent(renderer);
    //    std::cout << i << std::endl;
    //}

   
    rect1->w = input->w;
    rect1->h = input->h;
    rect1->x = 0;
    rect1->y = 0;

    vector<thread> thr;
    thr.push_back(thread(f1));
    thr.push_back(thread(f2));

    //f("hejka.bmp");

    for (auto& t : thr)
        t.join();


    texture_i = SDL_CreateTextureFromSurface(renderer, input);
    texture_o = SDL_CreateTextureFromSurface(renderer, output);


    

    SDL_SetTextureBlendMode(texture_i, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texture_o, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(renderer, texture_o, NULL, NULL);
    SDL_RenderPresent(renderer);




    //for (int i = 0; i < 1000; i++)
    //{
    //    for (int j = 0; j < output->w; j++)
    //    {
    //        for (int k = 0; k < output->h; k++)
    //        {
    //            SDL_RenderCopy(renderer, texture_i, NULL, NULL);
    //            
    //        }
    //        //std::cout << j;
    //    }
    //    SDL_RenderPresent(renderer);
    //    std::cout << i << std::endl;
    //}


    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < output->w; j++)
        {
            for (int k = 0; k < output->h; k++)
            {
                SDL_RenderDrawPoint(renderer, j, k);

            }
            //std::cout << j;
        }
        SDL_RenderPresent(renderer);
        std::cout << i << std::endl;
    }

    
    SDL_Delay(20000);
    SDL_Quit();
    return 0;
}