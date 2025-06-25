#include "imagen.h"

imagen::imagen(int ancho, int alto, std::vector<pixel>& vector, typo tipo)
{
	this->ancho = ancho;
	this->alto = alto;
	this->pixeles = vector;
	this->tipo = tipo;
}
