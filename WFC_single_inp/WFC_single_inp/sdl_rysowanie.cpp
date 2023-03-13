
#include "pix_set.h"
#include "superpositions.h"
#include <iostream>


using namespace std;

const bool ADD_ROTATIONS = false;
const bool DELETE_COPIES = true;

const int MAX_DEPTH = 20;

const string INPUT = "input.bmp";
const int INPUT_SCREEN_SCALE = 20;

const int OUT_WIDTH = 45;
const int OUT_HEIGHT = 45;
const int OUT_SCREEN_SCALE = 15;

const int SECTION_W = 3;
const int SECTION_H = SECTION_W;

SDL_Event event;

SDL_Renderer* inp_renderer;
SDL_Window* inp_window;

SDL_Renderer* out_renderer;
SDL_Window* out_window;







SDL_Surface* init()
{
    SDL_Surface* input;
    input = SDL_LoadBMP(INPUT.c_str());
    inp_window = SDL_CreateWindow("input", 50, 100, INPUT_SCREEN_SCALE * input->w, INPUT_SCREEN_SCALE * input->h, 0);
    inp_renderer = SDL_CreateRenderer(inp_window, -1, 0);
    SDL_SetRenderDrawColor(inp_renderer, 255, 255, 255, 255);
    SDL_RenderPresent(inp_renderer);

    out_window = SDL_CreateWindow("output", 150 + INPUT_SCREEN_SCALE * input->w, 100, OUT_SCREEN_SCALE * OUT_WIDTH, OUT_SCREEN_SCALE * OUT_HEIGHT, 0);
    out_renderer = SDL_CreateRenderer(out_window, -1, 0);
    SDL_SetRenderDrawColor(out_renderer, 255, 255, 255, 255);
    SDL_RenderPresent(out_renderer);

    return input;
}



void wfc_iteration(pix_set &set, pixels &output, superpositions &wave_f, bool &end, rules &r)
{
    if (end)
        return;

    vector<pair<int, int>> coords(wave_f.get_lowest_uncollapsed());
    if (coords.size() == 0)
        return;
    shuffle(coords);
    for (auto el : coords)
    {
        vector<int> temp_outcomes(wave_f.get_outcomes(el.first, el.second));
        output.draw(out_renderer, OUT_SCREEN_SCALE);
        for (auto choice : temp_outcomes)
        {
            if (end)
                return;
            wave_f.collapse(el.first, el.second, choice);
            pixels temp_output(output.ubdate_output(set.get_el(choice), el.first, el.second));
            //cout << el.first << "  " << el.second << endl;
            temp_output.draw_frag(out_renderer, OUT_SCREEN_SCALE, el.first, el.second ,SECTION_W, SECTION_H);
            bool broke = false;
            superpositions temp(wave_f.depth_propagation(set, el.first, el.second, broke, 0, r));
            wfc_iteration(set, temp_output, temp, end, r);
            if (wave_f.all_collapsed() || end)
            {
                end = true;
                return;
            }
            //cout << "lol" << end;
        }
        wave_f.set_outcomes(el.first, el.second, temp_outcomes);
        
        output.reset_frag(out_renderer, OUT_SCREEN_SCALE, el.first, el.second, SECTION_W, SECTION_H);
    }
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    srand(time(NULL));
    

    SDL_Surface* bitmap_input;
    bitmap_input = init();

    pixels pix_inp(bitmap_input);
    pix_inp.draw(inp_renderer, INPUT_SCREEN_SCALE);

    pix_set set(SECTION_W, SECTION_H, pix_inp);

    if(ADD_ROTATIONS)
        set.add_rotations();
    if(DELETE_COPIES)
        set.del_copies();
    

    pixels output(OUT_WIDTH, OUT_HEIGHT);
    output.draw(out_renderer, OUT_SCREEN_SCALE);

    superpositions wave_f(OUT_WIDTH - SECTION_W + 1, OUT_HEIGHT - SECTION_H + 1, set.size(), SECTION_H, MAX_DEPTH);
    
    wave_f.set_seed();

    rules r(set, SECTION_W);

    

    bool end = false;
    wfc_iteration(set, output, wave_f, end, r);
    
    cout << "koniec" << endl;


    SDL_Delay(20000000);
    SDL_Quit();
    return 0;
}







