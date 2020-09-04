#ifndef BILINEAR_FILTER_HPP
#define BILINEAR_FILTER_HPP

#include "texture.hpp"
#include "texture_filter.hpp"

template <typename T>
class BilinearFilter : public TextureFilter<T>
{
public:
    virtual T filter(float x, float y, Texture<T> const &texture) const;
};

template <typename T>
T BilinearFilter<T>::filter(float x, float y, Texture<T> const &texture) const
{
    int x0 = (int)x;
    int y0 = (int)y;

    T a = texture.getTexel(x0, y0);
    T b = texture.getTexel(x0 + 1, y0);
    T c = texture.getTexel(x0, y0 + 1);
    T d = texture.getTexel(x0 + 1, y0 + 1);

    T ab = a + (b - a) * (x - x0);
    T cd = c + (d - c) * (x - x0);

    return ab + (cd - ab) * (y - y0);
}

#endif
