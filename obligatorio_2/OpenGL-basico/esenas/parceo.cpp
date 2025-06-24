#include "parceo.h"
#include <string>
#include <vector>



vector3 parceo::parseovec3(char* vec, tinyxml2::XMLElement* element)
{
	auto vector = element->FirstChildElement(vec);
	float x = vector->FloatAttribute("x");
	float y = vector->FloatAttribute("y");
	float z = vector->FloatAttribute("z");
	
	return vector3(x, y, z);
}

luz* parceo::parsL(tinyxml2::XMLElement* lightElemen)
{
	vector3 position = parceo::parseovec3("position", lightElemen);
	vector3 color = parceo::parseovec3("color", lightElemen);
	float intensity = lightElemen->FloatAttribute("intensity");

    return new luz(position , color , intensity);
}

pared* parceo::parsePared(tinyxml2::XMLElement* paredElemen)
{
	const float alto = paredElemen->FloatAttribute("ancho");
	const float  ancho = paredElemen->FloatAttribute("alto");
	const vector3 color = parceo::parseovec3("color",paredElemen);
	const vector3 position = parceo::parseovec3("position", paredElemen);
	const vector3 normal = parceo::parseovec3("normal", paredElemen);
	const float alfa = paredElemen->FloatAttribute("alfa");
	const float translucido = paredElemen->FloatAttribute("translucido");
	const float indiceRef = paredElemen->FloatAttribute("indiceRef");
	const float reflex = paredElemen->FloatAttribute("reflex");
	float ancho, alto;
	return new pared(position, normal, alfa, reflex, translucido , indiceRef, ancho, alto);
}

camara* parceo::parseCamara(tinyxml2::XMLElement* camaraElemen)
{
	return nullptr;
}

Esfera* parceo::parseEsfera(tinyxml2::XMLElement* esperaElemen)
{
	const vector3 position = parceo::parseovec3("position", esperaElemen);
	const vector3 color = parceo::parseovec3("color", esperaElemen);
	const float radio = esperaElemen->FloatAttribute("radio");
	const float reflex = esperaElemen->FloatAttribute("reflex");
	const float translucido = esperaElemen->FloatAttribute("translucido");
	const float indiceRef = esperaElemen->FloatAttribute("indiceRef");
	const float alfa = esperaElemen->FloatAttribute("alfa");
	return new Esfera(position, radio, color , alfa , reflex, translucido , indiceRef);
}
