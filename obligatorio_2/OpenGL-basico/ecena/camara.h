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
    vector3 U_, V_;
    vector3 centro;
    int ancho, alto;
    float tamHorizontal;
    float length_;

public:
    explicit camara(const vector3& position, const vector3& look_at, const vector3& up, int ancho_, int alto_)
        : pos(position), look_at_(look_at), up_(up.normalize()), ancho(ancho_), alto(alto_)
    {
		float relaspecto_ = (float)ancho / (float)alto;
        tamHorizontal = (float)ancho / 2;
        length_ = 500;
        direction_ = (look_at_ - pos).normalize();
        U_ = (direction_ * up_).normalize();
        V_ = (U_ * direction_).normalize();
        U_ = U_ * tamHorizontal;
        V_ = V_ * (tamHorizontal / relaspecto_);
        centro = pos + (direction_ * length_);
    }

  
    float get_length() const;
    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;
    vector3 get_U() const;
    vector3 get_V() const;


    void generate_ray(float u, float v, rayo& ra);

};