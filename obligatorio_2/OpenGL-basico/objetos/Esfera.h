#pragma once
#include "objeto.h"
class Esfera: public objeto
{
	float readio;

public:
	Esfera(vector3 pos, float rad, vector3 color, float alfa, float reflec, float transparencia,float  indiceRef ) : objeto(pos, color, alfa, reflec, transparencia, indiceRef) {
		// Constructor que inicializa el radio y llama al constructor de la clase base
	}






	~Esfera() override;
};

