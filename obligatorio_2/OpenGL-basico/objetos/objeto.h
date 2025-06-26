#pragma once
#include "../utilidades/vector3.h"
#include "../ray_tracing/rayo.h"
#include <cstdio>
#include <iostream>
#include"../utilidades/color.h"
class objeto
{
protected:
	vector3 pos;
	vector3 colo;
	float alfa, reflectividad,brillo,  transparaencia, indiceRefraccion;
public:	
	objeto(vector3 pos_, vector3 color_, float alfa_, float reflectividad_, float transparaencia_, float indiceRefraccion_, float bri)
		: pos(pos_), colo(color_), alfa(alfa_), reflectividad(reflectividad_),
		transparaencia(transparaencia_), indiceRefraccion(indiceRefraccion_), brillo(bri){
	};

	vector3 getcolor() const { return colo; }
	vector3 getpos() const { return pos; }
	float getalfa() const { return alfa; }
	float getreflectividad() const { return reflectividad; }
	float getbrillo() const { return brillo; }
	float gettransparaencia() const { return transparaencia; }
	float getindiceRefraccion() const { return indiceRefraccion; }
	virtual bool intereseccion(rayo& rayo, vector3& punto, vector3& normal);
	color getColor() const {
		return color(colo.get_x(), colo.get_y(), colo.get_z(), alfa);
	}

	virtual ~objeto();
};

