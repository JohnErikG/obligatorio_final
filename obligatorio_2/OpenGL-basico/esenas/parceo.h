#pragma once
#include "tinyxml2.h"
#include "../utilidades/vector3.h"
#include "../luz.h"
#include "../utilidades/vector3.h"
class parceo
{
	static vector3 parseovec3(char* vec, tinyxml2::XMLElement* element);
public:
	static luz* parsL(tinyxml2::XMLElement* lightElemen);
};

