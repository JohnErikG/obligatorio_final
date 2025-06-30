#pragma once
#include "tinyxml2.h"
#include "../utilidades/vector3.h"
#include "../luz.h"
#include "../utilidades/vector3.h"
#include"../objetos/pared.h"
#include "../ecena/camara.h" 
#include "../objetos/esfera.h"
#include <vector>
#include "../objetos/mesa.h"
#include "../objetos/cilindro.h"
#include "../utilidades/color.h"
class parceo
{
	static vector3 parseovec3(char* vec, tinyxml2::XMLElement* element);
public:
	static luz* parsL(tinyxml2::XMLElement* lightElemen);
	static pared* parsePared(tinyxml2::XMLElement* paredElemen);
	static esfera* parseEsfera(tinyxml2::XMLElement* esperaElemen);
	static mesa* parseMesa(tinyxml2::XMLElement* mesaElemen);
	static cilindro* parseCilindro(tinyxml2::XMLElement* cilindroElemen);
	static color parseColor(tinyxml2::XMLElement* colorElemen);
	static int parceoInt(tinyxml2::XMLElement* element, const char* name);
	static objeto* parseObjeto(tinyxml2::XMLElement* element);
	static camara* parseCamara(tinyxml2::XMLElement* element, int ancho, int alto);
};

