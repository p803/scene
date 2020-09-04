#ifndef RENDERING_ALGORITHM_HPP
#define RENDERING_ALGORITHM_HPP

class Color;

#include <cstddef>

class Renderer
{
public:
    virtual ~Renderer() = default;

    virtual Color *render(size_t width, size_t height) const = 0;
};

#endif
