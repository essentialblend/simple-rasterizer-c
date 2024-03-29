#include <iostream>
#include <SDL.h>
#undef main

#include "display.h"
#include "YourImplementationInThisFile.h"

SDL_Event event;
SDL_Renderer* renderer;
SDL_Window* window;

bool close = false;



void COMP3011_CreateWindow(int w, int h)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer);
}

bool COMP3011_WindowShouldClose()
{
    return close;
}


void COMP3011_SwapBuffers()
{
    for (int pixel_y = 0; pixel_y < PIXEL_H; pixel_y++)
    {
        for (int pixel_x = 0; pixel_x < PIXEL_W; pixel_x++)
        {
            float pixel_r = display_buffer[pixel_x][PIXEL_H - pixel_y].x;
            float pixel_g = display_buffer[pixel_x][PIXEL_H - pixel_y].y;
            float pixel_b = display_buffer[pixel_x][PIXEL_H - pixel_y].z;
            SDL_SetRenderDrawColor(renderer, pixel_r, pixel_g, pixel_b, 255);
            SDL_RenderDrawPoint(renderer, pixel_x, pixel_y);
        }
    }
    SDL_RenderPresent(renderer);
}

void COMP3011_PollEvents()
{
    if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        close = true;
    }
}

void COMP3011_Deinit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main()
{
    //make a window
    COMP3011_CreateWindow(PIXEL_W, PIXEL_H);

    //render loop
    while (!COMP3011_WindowShouldClose())
    {
        //clear the screen
        float bgd[] = {1, 1, 1};
        ClearColourBuffer(bgd);

        //draw
        Draw(6);

        //sawp buffers
        COMP3011_SwapBuffers();

        //process input
        COMP3011_PollEvents();

    }

    //deinit
    COMP3011_Deinit();
}
