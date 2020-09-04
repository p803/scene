#ifndef TEXTURE_FILTER_HPP
#define TEXTURE_FILTER_HPP

template <typename T>
class Texture;

template <typename T>
class TextureFilter
{
public:
    virtual T filter(float x, float y, Texture<T> const &texture) const = 0;
};

#endif
