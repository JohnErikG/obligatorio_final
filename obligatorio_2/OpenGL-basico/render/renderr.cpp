#include "renderr.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <vector>
	

int renderr::id = 0;
void renderr::guardado()
{
	int ww = 640, hh = 480;
	std::vector<BYTE> pixels(3 * ww * hh);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, ww, hh, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());
	FIBITMAP* bitmapp = FreeImage_ConvertFromRawBits(
		pixels.data(),
		ww, hh,
		3 * ww,              // pitch
		24,                 // bits por p�xel
		0x00FF0000,         // m�scara rojo
		0x0000FF00,         // m�scara verde
		0x000000FF,         // m�scara azul
		false               // no flip vertical
	);
	FreeImage_Save(FIF_PNG, bitmapp, "../imagenes/output.png", 0);
	FreeImage_Unload(bitmapp);
}

void renderr::algoritmo()
{
}
