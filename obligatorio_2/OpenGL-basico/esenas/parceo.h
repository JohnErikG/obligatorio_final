#pragma once
#include "tinyxml2.h"
#include "../utilidades/vector3.h"
#include "../luz.h"
#include "../utilidades/vector3.h"
#include"../objetos/pared.h"
#include "../ecena/camara.h" 
#include "../objetos/Esfera.h"
#include <vector>
#include "../objetos/mesa.h"
#include "../objetos/cilindro.h"
class parceo
{
	static vector3 parseovec3(char* vec, tinyxml2::XMLElement* element);
public:
	static luz* parsL(tinyxml2::XMLElement* lightElemen);
	static pared* parsePared(tinyxml2::XMLElement* paredElemen);
	static camara* parseCamara(tinyxml2::XMLElement* camaraElemen);
	static Esfera* parseEsfera(tinyxml2::XMLElement* esperaElemen);
	static mesa* parseMesa(tinyxml2::XMLElement* mesaElemen);
	static cilindro* parseCilindro(tinyxml2::XMLElement* cilindroElemen);

};

