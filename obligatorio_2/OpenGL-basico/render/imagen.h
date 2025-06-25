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
	std::vector<pixel> getPixeles() const { return pixeles; }
	pixel getpixel(int x, int y) const
	{
		if (x >= 0 && x < ancho && y >= 0 && y < alto)
		{
			return pixeles[x * (alto)+y];
		}
	}
	std::string getTipo() {
		switch (tipo)
		{
		case normal:
			return "normal";
		case reflaxion:
			return "reflectividad";
		case transimision:
			return "transimision";
		}
	}
};

