#include "renderr.h"




int renderr::id = 0;
void renderr::guardado( imagen* img)
{
	float ww = img->getAncho();
	float hh = img->getAlto(); 
	std::vector<BYTE> pixels(3 * ww * hh);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, ww, hh, GL_BGR, GL_UNSIGNED_BYTE, pixels.data());
	FIBITMAP* bitmapp = FreeImage_ConvertFromRawBits(
		pixels.data(),
		ww, hh,
		3 * ww,              // pitch
		24,                 // bits por píxel
		0x00FF0000,         // máscara rojo
		0x0000FF00,         // máscara verde
		0x000000FF,         // máscara azul
		false               // no flip vertical
	);
	FreeImage_Save(FIF_PNG, bitmapp, "../imagenes/output.png", 0);
	FreeImage_Unload(bitmapp);
}

void renderr::algoritmo(imagen* img )
{
	/*
	for (int i = 0; i < img->getAncho(); i++) {
		for (int j = 0; j < img->getAlto(); j++) {
			
		}
	}*/

}
