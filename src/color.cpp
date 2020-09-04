#include "color.hpp"
#include "fp.hpp"

Color::Color(float red, float green, float blue) : _red(red), _green(green), _blue(blue)
{
}

float Color::red() const
{
    return _red;
}

float Color::green() const
{
    return _green;
}

float Color::blue() const
{
    return _blue;
}

bool Color::isBlack() const
{
    return Fp::eq(_red + _green + _blue, 0);
}

Color Color::trim() const
{
    return Color(std::fminf(_red, 1), std::fminf(_green, 1), std::fminf(_blue, 1));
}

Color Color::operator+(Color const &other) const
{
    Color that(*this);

    return that += other;
}

Color &Color::operator+=(Color const &other)
{
    _red += other._red;
    _green += other._green;
    _blue += other._blue;

    return *this;
}

Color Color::operator-(Color const &other) const
{
    Color that(*this);

    return that -= other;
}

Color &Color::operator-=(Color const &other)
{
    _red -= other._red;
    _green -= other._green;
    _blue -= other._blue;

    return *this;
}

Color Color::operator*(Color const &other) const
{
    Color that(*this);

    return that *= other;
}

Color &Color::operator*=(Color const &other)
{
    _red *= other._red;
    _green *= other._green;
    _blue *= other._blue;

    return *this;
}

Color Color::operator*(float t) const
{
    Color that(*this);

    return that *= t;
}

Color &Color::operator*=(float t)
{
    _red *= t;
    _green *= t;
    _blue *= t;

    return *this;
}

Color Color::operator/(float t) const
{
    Color that(*this);

    return that /= t;
}

Color &Color::operator/=(float t)
{
    _red /= t;
    _green /= t;
    _blue /= t;

    return *this;
}
