#pragma once
#include <FreeImage.h>
#include <ostream>

class color
{
    double rojo_, verde_,azul_, alpha_;

public:
    color()
    {
        rojo_ = 0;
        verde_ = 255;
        azul_ = 0;
        alpha_ = 255;
    }

    color(double rojo, double verde, double azul, double alpha = 255)
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
    void set_alpha(double alpha);
    double get_alpha() const;
    void set_rojo(double rojo) { rojo_ = rojo; }
    void set_verde(double verde) { verde_ = verde; }
    void set_azul(double azul) { azul_ = azul; }
    double get_rojo() const { return rojo_; }
    double get_verde() const { return verde_; }
    double get_azul() const { return azul_; }
    color operator+= (const color& c);
    color operator/ (double f) const;

    color operator+(const color& c) const;
    color operator*(double f) const;
    friend std::ostream& operator<<(std::ostream& os, const color& c);
    color operator-(const color& color) const;

    color combinar(const color& c, double ratio) const;
};


color operator*(const color& c1, const color& c2);
color operator*(double f, const color& c);