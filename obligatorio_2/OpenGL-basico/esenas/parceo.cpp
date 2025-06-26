#include "parceo.h"
#include <string>
#include <vector>
#include <iostream>


vector3 parceo::parseovec3(char* vec, tinyxml2::XMLElement* element)
{
	auto vector = element->FirstChildElement(vec);
	float x = vector->FloatAttribute("x");
	float y = vector->FloatAttribute("y");
	float z = vector->FloatAttribute("z");
	std::cout << "Vector3 parsed: " << x << ", " << y << ", " << z << std::endl;
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
	const float brillo = paredElemen->FloatAttribute("brillo");
	return new pared(position, normal,color, alfa,brillo, reflex, translucido , indiceRef, ancho, alto);
}

camara* parceo::parseCamara(tinyxml2::XMLElement* camaraElemen)
{
	return nullptr;
}

esfera* parceo::parseEsfera(tinyxml2::XMLElement* esperaElemen)
{
	const vector3 position = parceo::parseovec3("position", esperaElemen);
	const vector3 color = parceo::parseovec3("color", esperaElemen);
	const float radio = esperaElemen->FloatAttribute("radio");
	const float reflex = esperaElemen->FloatAttribute("reflex");
	const float translucido = esperaElemen->FloatAttribute("translucido");
	const float indiceRef = esperaElemen->FloatAttribute("indiceRef");
	const float alfa = esperaElemen->FloatAttribute("alfa");
	const float brillo = esperaElemen->FloatAttribute("brillo");
	return new esfera(position, radio, color , alfa ,brillo,  reflex, translucido , indiceRef);
}

mesa* parceo::parseMesa(tinyxml2::XMLElement* mesaElemen)
{
	const vector3 pos = parceo::parseovec3("position", mesaElemen);
	const vector3 color = parceo::parseovec3("color", mesaElemen);
	const float alfa = mesaElemen->FloatAttribute("alfa");
	const float alto = mesaElemen->FloatAttribute("alto");
	const float ancho = mesaElemen->FloatAttribute("ancho");
	const float profundidad = mesaElemen->FloatAttribute("profundidad");
	const float reflex = mesaElemen->FloatAttribute("reflex");
	const float translucido = mesaElemen->FloatAttribute("translucido");
	const float indiceRef = mesaElemen->FloatAttribute("indiceRef");
	const float brillo = mesaElemen->FloatAttribute("brillo");
	return new mesa(mesa::crearMesa(pos, color , alfa,brillo , reflex, translucido, indiceRef,alto, ancho, profundidad));
}

cilindro* parceo::parseCilindro(tinyxml2::XMLElement* cilindroElemen)
{
	const vector3 pos = parceo::parseovec3("position", cilindroElemen);
	const vector3 color = parceo::parseovec3("color", cilindroElemen);
	const float radio = cilindroElemen->FloatAttribute("radio");
	const float alto = cilindroElemen->FloatAttribute("alto");
	const float reflex = cilindroElemen->FloatAttribute("reflex");
	const float translucido = cilindroElemen->FloatAttribute("translucido");
	const float indiceRef = cilindroElemen->FloatAttribute("indiceRef");
	const float alfa = cilindroElemen->FloatAttribute("alfa");
	const float brillo = cilindroElemen->FloatAttribute("brillo");
	return new cilindro(pos, color , alfa,brillo, reflex, translucido, indiceRef, radio, alto);
}

color parceo::parseColor(tinyxml2::XMLElement* colorElemen)
{
	const auto fill = colorElemen->FirstChildElement("color");

	double  r = fill->FloatAttribute("red");
	double g = fill->FloatAttribute("green");
	double  b = fill->FloatAttribute("blue");

	return  color(r, g, b);
}

int parceo::parceoInt(tinyxml2::XMLElement* element, const char* name)
{
	return element->IntAttribute(name);
}

objeto* parceo::parseObjeto(tinyxml2::XMLElement* element)
{
	string objN = std::string(element->Attribute("tipo"));
	objeto* obj = nullptr;
	if (objN == "pared") { obj = parsePared(element); }
	else if (objN == "esfera") { obj = parseEsfera(element); }
	else if (objN== "cilindro") { obj = parseCilindro(element); }
	else if (objN == "mesa") { obj = parseMesa(element); }
	
	return obj;
}

camara* parceo::parseCamara(tinyxml2::XMLElement* element, int ancho, int alto)
{
	const auto position = parseovec3("position", element);
	const auto look_at = parseovec3("look_at", element);
	const auto up = parseovec3("up", element);

	return new camara(position, look_at, up, ancho, alto);
	return nullptr;
}

