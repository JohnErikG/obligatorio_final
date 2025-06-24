#pragma once
#include "../utilidades/vector3.h"

class objeto
{
protected:
	vector3 pos;
	vector3 color;
	float alfa, reflectividad, transparaencia, indiceRefraccion;
public:	
	objeto(vector3 pos_, vector3 color_, float alfa_ , float reflectividad_ , float transparaencia_ , float indiceRefraccion_)
		: pos(pos_), color(color_), alfa(alfa_), reflectividad(reflectividad_),
	transparaencia(transparaencia_), indiceRefraccion(indiceRefraccion_) {}


	virtual bool intersecta(const vector3& origen, const vector3& direccion, float& t);
	vector3 getcolor() const { return color; }
	vector3 getpos() const { return pos; }
	float getalfa() const { return alfa; }
	float getreflectividad() const { return reflectividad; }

	float gettransparaencia() const { return transparaencia; }
	float getindiceRefraccion() const { return indiceRefraccion; }
	


	virtual ~objeto() {}
};

