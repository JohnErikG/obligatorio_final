#pragma once
#include "objeto.h"
class esfera: public objeto
{
	float radio;

public:
	esfera(vector3 pos, float rad, vector3 color, float alfa,float bri, float reflec, float transparencia,float  indiceRef ) : objeto(pos, color, alfa, reflec, transparencia, indiceRef,bri),
	radio(rad) {
		// Constructor que inicializa el radio y llama al constructor de la clase base
	}




	bool intereseccion(rayo& rayo, vector3& punto, vector3& normal) override;

	~esfera() override;
};

