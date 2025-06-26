#pragma once
#include "imagen.h"	
#include "SDL.h"

class renderr
{

public:
	static int id;
	static void guardado(imagen& img);
	static void algoritmo(imagen& img, int maxX, SDL_Renderer* render);
};

