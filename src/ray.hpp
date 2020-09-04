#ifndef RAY_HPP
#define RAY_HPP

class Object;

#include "vector.hpp"
#include "point.hpp"

class Ray
{
public:
    Ray(Point const &origin, Vector const &ahead);

    Point pointAt(float distance) const;
    Ray reflect(Object const *object, Point const &surfacePoint) const;
    Ray transmit(Object const *object, Point const &surfacePoint) const;
    Ray scatter(Object const *object, Point const &surfacePoint) const;
    float distanceTo(Object const *target) const;

    Point const &getOrigin() const;
    Vector const &getAhead() const;

protected:
    static Vector randomDirectionOnHemisphere();

    Point _origin;
    Vector _ahead;
};

#endif
