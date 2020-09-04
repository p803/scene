#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
    Color(float red, float green, float blue);

    float red() const;
    float green() const;
    float blue() const;

    bool isBlack() const;

    Color trim() const;

    Color operator+(Color const &other) const;
    Color &operator+=(Color const &other);

    Color operator-(Color const &other) const;
    Color &operator-=(Color const &other);

    Color operator*(Color const &other) const;
    Color &operator*=(Color const &other);

    Color operator*(float t) const;
    Color &operator*=(float t);

    Color operator/(float t) const;
    Color &operator/=(float t);

protected:
    float _red;
    float _green;
    float _blue;
};

#endif
