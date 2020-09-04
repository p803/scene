#ifndef OBJECT_HPP
#define OBJECT_HPP

class Color;
class Ray;

#include "material.hpp"
#include "point.hpp"
#include "vector.hpp"

class Object
{
public:
    Object(Material const &material, Point const &origin);
    virtual ~Object() = default;

    Point const &getOrigin() const;

    Vector const &getUp() const;
    Vector const &getFront() const;
    Vector const &getRight() const;

    Material const &getMaterial() const;

    virtual float intersectDistance(Ray const &ray) const = 0;
    Vector mappedNormalAt(Point const &surfacePoint) const;
    virtual Point mapTexturePointFromSurfacePoint(Point const &surfacePoint) const = 0;
    virtual Point mapSurfacePointFromTexturePoint(Point const &texturePoint) const = 0;
    Point toWorld(Point const &local) const;

protected:
    virtual Vector normalAt(Point const &surfacePoint) const = 0;

    Material _material;
    Point _origin;
    Vector _front;
    Vector _up;
    Vector _right;
};

#endif
