#ifndef SPHERE_HPP
#define SPHERE_HPP

class Material;
class Point;
class Ray;
class Vector;

#include "object.hpp"

class Sphere : public Object
{
public:
    Sphere(float radius, Material const &material, Point const &origin);

    virtual float intersectDistance(Ray const &ray) const;
    virtual Point mapTexturePointFromSurfacePoint(Point const &surfacePoint) const;
    virtual Point mapSurfacePointFromTexturePoint(Point const &texturePoint) const;

protected:
    virtual Vector normalAt(Point const &surfacePoint) const;

    float _radius;
};

#endif
