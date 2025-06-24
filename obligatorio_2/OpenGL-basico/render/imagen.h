#pragma once
#include <vector>
#include "pixel.h"
enum tipo
{
	normal, reflexion, refraccion
};
class imagen
{

private:
	tipo tipo;
	unsigned int id;
	int ancho, alto;
	std::vector <pixel> pixeles;
public :
	int getAncho() const { return ancho; }
	int getAlto() const { return alto; }

};

