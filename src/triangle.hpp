#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

class Material;
class Point;
class Ray;
class Vector;

#include "object.hpp"

class Triangle : public Object
{
public:
    Triangle(Point const &a, Point const &b, Point const &c, Material const &material, Point const &origin);

    virtual float intersectDistance(Ray const &ray) const;
    virtual Point mapTexturePointFromSurfacePoint(Point const &surfacePoint) const;
    virtual Point mapSurfacePointFromTexturePoint(Point const &texturePoint) const;

protected:
    static float area(Point const &a, Point const &b, Point const &c);

    virtual Vector normalAt(Point const &surfacePoint) const;

    // Triangle vertices in the space.
    Point _a;
    Point _b;
    Point _c;

    // Triangle vertices on the texture.
    Point _ta;
    Point _tb;
    Point _tc;
};

#endif
