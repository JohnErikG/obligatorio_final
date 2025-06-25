#pragma once
#include "objeto.h"
class cilindro : public objeto{

    float radio;
	float altura;
public:
    cilindro(vector3 pos, vector3 color , float alfa , float reflc,float translucido, float indiceRef , float rad, float alt )
    :objeto(pos, color , alfa, reflc, translucido , indiceRef ), altura(alt), radio(rad){
    }
    bool intereseccion(rayo& rayo, vector3& punto, vector3& normal);

	~cilindro() override;


};

