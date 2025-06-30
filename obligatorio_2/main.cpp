#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <vector>
#include <../OpenGL-basico/render/renderr.h>
#include <../OpenGL-basico/render/imagen.h>
#include <../OpenGL-basico/ecena/escena.h>

using namespace std;

int main(int argc, char *argv[]) {

	escena esc("../esena1.xml");


    SDL_Init(SDL_INIT_VIDEO);

	FreeImage_Initialise();

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		esc.get_ancho(), esc.get_alto(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(render, 0, 0, 0, 255); 
	SDL_RenderClear(render);
	SDL_RenderPresent(render); 
    bool fin = false;

    SDL_Event evento;

    while (!fin)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                fin = true;
            }
        }

        if (!esc.termino())
        {
            esc.Render( 1);
            renderr::algoritmo(esc.get_imagen_final(), esc.get_iter(), render);
        }
        else
        {
            renderr::guardado(esc.get_imagen_final());
            renderr::guardado(esc.get_imagen_reflexion());
            renderr::guardado(esc.get_imagen_refraccion());
            fin = true;
        }
        SDL_RenderPresent(render);
       
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    FreeImage_DeInitialise();
  
    return 0;
}


