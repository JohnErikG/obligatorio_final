#pragma once
#include "objeto.h"
class esfera: public objeto
{
	float radio;

public:
	esfera(vector3 pos, float rad, vector3 color, float alfa,float bri, float reflec, float transparencia,float  indiceRef ) : objeto(pos, color, alfa, reflec, transparencia, indiceRef, bri),
	radio(rad) {}

	bool calcular_interseccion(rayo& rayo, vector3& punto, vector3& normal) override;

	~esfera() override;
};

