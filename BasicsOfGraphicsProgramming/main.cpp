#include<iostream>
#include<vector>
#include<cmath>
#include<SDL.h>
#include"Mathematics.hpp"

void drawGentleLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);

int main(int argc, char * argv[])
{
    SDL_Renderer *renderer;
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
    
    if(!window)
    {
        std::cerr << "Error failed to create window!\n";
        return 1;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    Vector2D<int>* point0 = new Vector2D<int>(60, 60);
    Vector2D<int>* point1 = new Vector2D<int>(200, 80); 

    Vector2D<int>* point2 = new Vector2D<int>(60, 80);
    Vector2D<int>* point3 = new Vector2D<int>(200, 60); 

    Vector2D<int>* point4 = new Vector2D<int>(60, 60);
    Vector2D<int>* point5 = new Vector2D<int>(200, 60); 

    Vector2D<int>* point6 = new Vector2D<int>(60, 60);
    Vector2D<int>* point7 = new Vector2D<int>(60, 200); 

    drawLine(point0, point1, renderer);
    drawLine(point2, point3, renderer);
    drawLine(point4, point5, renderer);
    drawLine(point6, point7, renderer);

    SDL_RenderPresent(renderer);
    SDL_Event event;
    bool running = true;


    while(running)
    {
    
        while(SDL_PollEvent(&event))
        {
            running = event.type != SDL_QUIT;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void drawGentleLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    int deltaX = point1->x - point0->x;
    int deltaY = point1->y - point0->y;

    int yIteration = 1;

    if(deltaY <0)
    {
        yIteration = -1;
        deltaY = -deltaY;
    }

    int difference = (2 * deltaY) - deltaX;

    int y = point0->y;

    for (int i = point0->x; i <= point1->x; i++)
    {
        SDL_RenderDrawPoint(renderer, i, y);
        if(difference >0)
        {
            y = y + yIteration;
            difference = difference + (2*(deltaY - deltaX));
        }
        else
        {
            difference = difference + 2*deltaY;
        }
    }
}


void drawSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    int deltaX = point1->x - point0->x;
    int deltaY = point1->y - point0->y;

    int xIteration = 1;

    if(deltaX <0)
    {
        xIteration = -1;
        deltaX = -deltaX;
    }

    int difference = (2 * deltaX) - deltaY;

    int x = point0->x;

    for (int i = point0->y; i <= point1->y; i++)
    {
        SDL_RenderDrawPoint(renderer, x, i);
        if(difference >0)
        {
            x = x + xIteration;
            difference = difference + (2*(deltaX - deltaY));
        }
        else
        {
            difference = difference + 2*deltaX;
        }
    }
}

void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
{
    if(abs(point1->y - point0->y) < abs(point1->x - point0->x))
    {
        if(point0->x > point1->x)
        {
            drawGentleLine(point1, point0, renderer);
        }
        else
        {
            drawGentleLine(point0, point1, renderer);
        }
    }
    else
    {
        if(point0->y > point1->y)
        {
            drawSteepLine(point1, point0, renderer);
        }
        else
        {
            drawSteepLine(point0, point1, renderer);
        }
    }
}

