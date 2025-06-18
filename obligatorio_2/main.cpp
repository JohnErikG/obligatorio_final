#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <vector>
#include <../OpenGL-basico/render/renderr.h>

using namespace std;

int main(int argc, char *argv[]) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	FreeImage_Initialise();

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;

	SDL_Event evento;


	
	
	
	
	
	//LOOP PRINCIPAL
	do{

		//MANEJO DE EVENTOS
		while (SDL_PollEvent(&evento)){
			switch (evento.type) {
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYUP:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_RIGHT:
					break;
				default :
					break;
				}
			default:
				break;
			}
		}
		//FIN MANEJO DE EVENTOS

		SDL_GL_SwapWindow(win);
	} while (!fin);
	//FIN LOOP PRINCIPAL

	renderr ren;
	//ren.guardado(imagen* img);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
