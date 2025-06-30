#include "camara.h"

vector3 camara::get_position() const
{
    return pos;
}

vector3 camara::get_up() const
{
    return up_;
}

vector3 camara::get_direction() const
{
    return direction_;
}


float camara::get_horizontal_size() const
{
    return horizontal_size_;
}

float camara::get_length() const
{
    return length_;
}


vector3 camara::get_U() const
{
    return U_;
}


vector3 camara::get_V() const
{
    return V_;
}




void camara::generate_ray(float u, float v, rayo& ray)
{

    vector3 pixel = centro + (U_ * u);
    pixel = pixel + (V_ * v);

   
    ray.setOrigen(pos);
    ray.setDireccion(pixel);
}
