#pragma once
#include <FreeImage.h>
#include <ostream>

class color
{
    float rojo_, verde_,azul_, alpha_;

public:
    color()
    {
        rojo_ = 0;
        verde_ = 255;
        azul_ = 0;
        alpha_ = 255;
    }

    color(float rojo, float verde, float azul, float alpha = 255)
    {
        rojo_ = rojo;
        verde_ = verde;
        azul_ = azul;
        alpha_ = alpha;
        if (rojo < 0) rojo_ = 0;
        if (rojo > 255) rojo_ = 255;
        if (verde < 0) verde_ = 0;
        if (verde > 255) verde_ = 255;
        if (azul < 0) azul_ = 0;
        if (azul > 255) azul_ = 255;
        if (alpha < 0) alpha_ = 0;
        if (alpha > 255) alpha_ = 255;

    }

    RGBQUAD to_rgb() const;
    void set_alpha(float alpha);
    float get_alpha() const;
    void set_rojo(float rojo) { rojo_ = rojo; }
    void set_verde(float verde) { verde_ = verde; }
    void set_azul(float azul) { azul_ = azul; }
    float get_rojo() const { return rojo_; }
    float get_verde() const { return verde_; }
    float get_azul() const { return azul_; }
    color operator+= (const color& c);
    color operator/ (float f) const;

    color operator+(const color& c) const;
    color operator*(float f) const;
    color operator-(const color& color) const;

    color combinar(const color& c, float ratio) const;
};


color operator*(const color& c1, const color& c2);
color operator*(float f, const color& c);