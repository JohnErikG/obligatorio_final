#pragma once
#include "imagen.h"	
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <vector>
class renderr
{

public:
	static int id;
	static void guardado(imagen* img);
	static void algoritmo(imagen* img);
};

