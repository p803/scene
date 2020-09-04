// Floating point arithmetic module.

#ifndef DB_HPP
#define DB_HPP

#include <cmath>
#include <cstdlib>

namespace Fp
{
    // Rounding error tolerance.
    static const float EPS = .0001;

    inline bool lt(float a, float b)
    {
        return a < b - EPS;
    }

    inline bool le(float a, float b)
    {
        return !lt(b, a);
    }

    inline bool eq(float a, float b)
    {
        return !lt(a, b) && !lt(b, a);
    }

    inline bool neq(float a, float b)
    {
        return lt(a, b) || lt(b, a);
    }

    inline bool gt(float a, float b)
    {
        return lt(b, a);
    }

    inline bool ge(float a, float b)
    {
        return !lt(a, b);
    }

    inline float rand()
    {
        return (float)std::rand() / RAND_MAX;
    }

    inline float arccos(float x)
    {
        return le(x, -1) ? M_PI : ge(x, 1) ? 0 : acos(x);
    }

} // namespace Fp

#endif
