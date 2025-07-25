#include "color.h"

RGBQUAD color::to_rgb() const
{
    RGBQUAD rgb;
    rgb.rgbRed = static_cast<BYTE>(rojo_);
    rgb.rgbGreen = static_cast<BYTE>(verde_);
    rgb.rgbBlue = static_cast<BYTE>(azul_);
    rgb.rgbReserved = static_cast<BYTE>(alpha_);
    return rgb;
}

void color::set_alpha(double alpha)
{
    alpha_ = alpha;
}

double color::get_alpha() const
{
    return alpha_;
}

color color::operator+(const color& c) const
{
    return color(rojo_ + c.rojo_, verde_ + c.verde_, azul_ + c.azul_, alpha_ + c.alpha_);
}

color color::operator*(double f) const
{
    return color(rojo_ * f, verde_ * f, azul_ * f, alpha_ * f);
}

color color::operator-(const color& color) const
{
    return {
        std::max(0.0, rojo_ - color.rojo_),
        std::max(0.0, verde_ - color.verde_),
        std::max(0.0, azul_ - color.azul_),
    };
}

color color::combinar(const color& c, double ratio) const
{
    double new_rojo = rojo_ * ratio + c.rojo_ * (1 - ratio);
    double new_verde = verde_ * ratio + c.verde_ * (1 - ratio);
    double new_azul = azul_ * ratio + c.azul_ * (1 - ratio);
    double new_alpha = alpha_ * ratio + c.alpha_ * (1 - ratio);

    return color(new_rojo, new_verde, new_azul, new_alpha);
}

color operator*(const color& c1, const color& c2)
{
    return color(c1.get_rojo() * c2.get_rojo(), c1.get_verde() * c2.get_verde(), c1.get_azul() * c2.get_azul());
}

color operator*(double f, const color& c)
{
    return color(c.get_rojo() * f, c.get_verde() * f, c.get_azul() * f, c.get_alpha() * f);
}


color color::operator/(double f) const
{
    return color(rojo_ / f, verde_ / f, azul_ / f, alpha_ / f);
}

color color::operator+=(const color& c)
{
    rojo_ += c.rojo_;
    verde_ += c.verde_;
    azul_ += c.azul_;
    alpha_ += c.alpha_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const color& c)
{
    os << "Color: (" << c.rojo_ << ", " << c.verde_ << ", " << c.azul_ << ", " << c.alpha_ << ")";
    return os;
}