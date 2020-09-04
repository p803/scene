#ifndef UNARY_FILTER_HPP
#define UNARY_FILTER_HPP

#include "texture.hpp"
#include "texture_filter.hpp"

template <typename T>
class UnaryFilter : public TextureFilter<T>
{
public:
    virtual T filter(float x, float y, Texture<T> const &texture) const;
};

template <typename T>
T UnaryFilter<T>::filter(float x, float y, Texture<T> const &texture) const
{
    int x0 = (int)x;
    int y0 = (int)y;

    return texture.getTexel(x0, y0);
}

#endif
