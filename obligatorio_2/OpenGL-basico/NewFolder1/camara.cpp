#include "camara.h"
#include <iostream>
#include <cmath>


constexpr float to_radians(float degrees) {
    return degrees * 3.14159265359f / 180.0f;
}

float normalizar_angulo(float angulo) {
    while (angulo < 0.0f) angulo += 360.0f;
    while (angulo >= 360.0f) angulo -= 360.0f;
    return angulo;
}

void camara::actualizar_angulos_desde_direccion()
{
    vector3 dir_normalizada = direccion_;

    pitch_ = std::asin(dir_normalizada.get_y()) * 180.0f / 3.14159265359f;

    yaw_ = std::atan2(dir_normalizada.get_z(), dir_normalizada.get_x()) * 180.0f / 3.14159265359f;

    if (yaw_ < 0.0f)
        yaw_ += 360.0f;
}


vector3 camara::get_posicion() const
{
    return posicion_;
}

vector3 camara::get_direccion() const
{
    return direccion_;
}

vector3 camara::get_up() const
{
    return up_;
}

void camara::set_direccion(const vector3& direccion)
{
    direccion_ = direccion;
}

void camara::set_posicion(const vector3& posicion)
{
    posicion_ = posicion;
}

void camara::set_up(const vector3& up)
{
    up_ = up;
}

void camara::mover(const vector3& desplazamiento)
{
    posicion_ += desplazamiento;
}



void camara::rotar(const float x_offset, const float y_offset, const bool primera_persona, const bool vertical, const bool atras)
{
    constexpr float sensitivity = 0.1f;


    float x_off = x_offset * sensitivity;
    float y_off = y_offset * sensitivity;


    yaw_ += x_off;
    pitch_ += y_off;

    // Restringir rotacion vertical
    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    if (primera_persona && !vertical) {
        if (!atras) {
            if (yaw_ > 89.0f)
                yaw_ = 89.0f;
            if (yaw_ < -89.0f)
                yaw_ = -89.0f;
        }
        else {
            if (yaw_ < 90.0f) yaw_ = 90.0f;
            if (yaw_ > 270.0f) yaw_ = 270.0f;
        }
    }

    if (!primera_persona) {
        yaw_ = normalizar_angulo(yaw_);
    }
    // Recalcular dirección
    vector3 nueva_direccion;
    nueva_direccion.set_x(std::cos(to_radians(yaw_)) * std::cos(to_radians(pitch_)));
    nueva_direccion.set_y(std::sin(to_radians(pitch_)));
    nueva_direccion.set_z(std::sin(to_radians(yaw_)) * std::cos(to_radians(pitch_)));
    nueva_direccion.normalize();

    direccion_ = nueva_direccion;
}