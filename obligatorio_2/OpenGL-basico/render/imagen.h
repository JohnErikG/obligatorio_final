#pragma once
#include <vector>
#include "pixel.h"
enum typo
{
	normal, reflexion, refraccion
};
class imagen
{


	typo tipo;
	unsigned int id;
	int ancho, alto;
	std::vector <pixel> pixeles;
public:
	explicit imagen(int ancho, int alto,std::vector<pixel>& vector, typo tipo = normal);
	int getAncho() const { return ancho; }
	int getAlto() const { return alto; }
	void agregarP(pixel pix);
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
		case reflexion:
			return "reflectividad";
		case refraccion:
			return "refraccion";
		}
	}
	static imagen vacia(int ancho, int alto, typo tip)
	{
		std::vector<pixel> vacio;
		return imagen(ancho, alto, vacio, tip);
	}
};

