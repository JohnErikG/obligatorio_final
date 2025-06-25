#include "camara.h"

vector3 camara::get_position() const
{
    return position_;
}

vector3 camara::get_up() const
{
    return up_;
}

vector3 camara::get_direction() const
{
    return direction_;
}

vector3 camara::get_U() const
{
    return U_;
}

vector3 camara::get_V() const
{
    return V_;
}

double camara::get_aspect_ratio() const
{
    return aspect_ratio_;
}

double camara::get_horizontal_size() const
{
    return horizontal_size_;
}

double camara::get_length() const
{
    return length_;
}

void camara::generate_ray(double u, double v, rayo& ray)
{

    vector3 pixel = camera_centre_ + (U_ * u);
    pixel = pixel + (V_ * v);

    
    ray.setOrigen(position_);
    ray.setDireccion(pixel);
}
vector3 camara::get_position() const
{
    return position_;
}

vector3 camara::get_up() const
{
    return up_;
}

vector3 camara::get_direction() const
{
    return direction_;
}

vector3 camara::get_U() const
{
    return U_;
}

vector3 camara::get_V() const
{
    return V_;
}

double camara::get_aspect_ratio() const
{
    return aspect_ratio_;
}

double camara::get_horizontal_size() const
{
    return horizontal_size_;
}

double camara::get_length() const
{
    return length_;
}

void camara::generate_ray(double u, double v, rayo& ray)
{

    vector3 pixel = camera_centre_ + (U_ * u);
    pixel = pixel + (V_ * v);

   
    ray.setOrigen(position_);
    ray.setDireccion(pixel);
}
