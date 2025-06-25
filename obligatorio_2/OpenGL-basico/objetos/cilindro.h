#pragma once
#include "objeto.h"
#include"pared.h"


class cilindro : public objeto{

    float radio;
	float altura;
    pared top; // parte superior del cilindro
	pared base; // parte inferior del cilindro
public:
    cilindro(vector3 pos, vector3 color , float alfa ,float bri, float reflc,float translucido, float indiceRef , float rad, float alt )
        :objeto(pos, color , alfa,bri, reflc, translucido , indiceRef ), altura(alt), radio(rad), top(pos+vector3(0, altura, 0), vector3(0,1,0), color , alfa ,bri, reflc, translucido, indiceRef, radio, radio), base(pos,vector3(0,-1,0),color,
        alfa,bri, reflc, translucido,indiceRef,radio, radio){
    }
    bool intereseccion(rayo& rayo, vector3& punto, vector3& normal) override;

	~cilindro() override;


};

