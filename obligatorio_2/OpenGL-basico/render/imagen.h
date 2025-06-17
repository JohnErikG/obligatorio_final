#pragma once
#include <vector>
#include "pixel.h"
enum typo
{
	norma, reflaxion, transimision
};
class imagen
{

private:
	typo tipo;
	unsigned int id;
	int ancho, alto;
	std::vector <pixel> pixeles;
public :
	int getAncho() const { return ancho; }
	int getAlto() const { return alto; }

};

