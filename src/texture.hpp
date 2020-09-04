#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../vendor/cimg/CImg.h"

#include "texture_filter.hpp"

template <typename T>
class Texture
{
public:
    Texture(char const *filename, TextureFilter<T> const &filter);

    bool isEmpty() const;

    T getTexel(int x, int y) const;
    T getTexel(float x, float y) const;

private:
    cimg_library::CImg<int> _image;
    TextureFilter<T> const &_filter;
};

template <typename T>
Texture<T>::Texture(char const *filename, TextureFilter<T> const &filter) : _image(filename), _filter(filter)
{
}

template <typename T>
bool Texture<T>::isEmpty() const
{
    return _image.size() <= 1;
}

template <typename T>
T Texture<T>::getTexel(float x, float y) const
{
    return _filter.filter(x * _image.width(), y * _image.height(), *this);
}

template <typename T>
T Texture<T>::getTexel(int x, int y) const
{
    float r, g, b;

    if (_image.spectrum() == 1)
    {
        r = g = b = (float)_image(x, y) / 255;
    }
    else if (_image.spectrum() == 3)
    {
        r = (float)_image(x, y, 0, 0) / 255;
        g = (float)_image(x, y, 0, 1) / 255;
        b = (float)_image(x, y, 0, 2) / 255;
    }
    else
    {
        throw "Exception in Texture::getTexel(): Bad spectrum.";
    }

    return T(r, g, b);
}

#endif
