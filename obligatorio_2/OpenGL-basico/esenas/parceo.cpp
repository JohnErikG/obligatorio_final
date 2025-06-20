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
