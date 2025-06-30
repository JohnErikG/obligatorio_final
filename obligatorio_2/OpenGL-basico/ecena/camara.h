#pragma once
#include "../utilidades/vector3.h"
#include <iostream>
#include <cmath>
#include <ostream>
#include "../ray_tracing/rayo.h"
class camara
{
    vector3 pos, look_at_, up_;
    vector3 direction_;
    vector3 U, V;
    vector3 centro;
    int ancho, alto;


public:
    explicit camara(const vector3& position, const vector3& look_at, const vector3& up, int ancho_, int alto_)
        : pos(position), look_at_(look_at), up_(up.normalize()), ancho(ancho_), alto(alto_)
    {
        direction_ = (look_at_ - pos).normalize();
        U = (direction_ * up_).normalize();
        V = (U * direction_).normalize();
        U = U * (float)ancho / 2;
        V = V * (((float)ancho / 2) / ((float)ancho / (float)alto));
        centro = pos + (direction_ * 500);
    }

  
    vector3 get_position() const;

    void crear_rayo(float u, float v, rayo& ra);

};