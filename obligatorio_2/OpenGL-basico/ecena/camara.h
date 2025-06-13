#pragma once
#include "../utilidades/vector3.h"

class camara
{
    vector3 posicion_, direccion_, up_;
    float yaw_ = -90.0f;
    float pitch_ = 0.0f;

public:
    explicit camara(const vector3* posicion, const vector3* direccion, const vector3* up) : posicion_(*posicion), direccion_(*direccion),
        up_(*up)
    {
    }

    vector3 get_posicion() const;
    vector3 get_direccion() const;
    vector3 get_up() const;

    void set_direccion(const vector3& direccion);
    void set_posicion(const vector3& posicion);
    void set_up(const vector3& up);
    void actualizar_angulos_desde_direccion();

    void mover(const vector3& desplazamiento);
    void rotar(float x_offset, float y_offset, bool primera_persona, bool vertical, bool atras);
};