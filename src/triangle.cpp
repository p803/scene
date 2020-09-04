#include "triangle.hpp"

#include "fp.hpp"
#include "material.hpp"
#include "point.hpp"
#include "ray.hpp"

Triangle::Triangle(Point const &a, Point const &b, Point const &c, Material const &material, Point const &origin) : Object(material, origin), _a(a), _b(b), _c(c), _ta(0, 0, 0), _tb(1, 0, 0), _tc(.5, 1, 0)
{
}

float Triangle::intersectDistance(Ray const &ray) const
{
    // Triangle normal is constant anywhere.
    Vector normal = normalAt(Point(0, 0, 0)); // anywhere

    // Parameter `d` of plane equation `Ax + By + Cz + d = 0`.
    float d = -normal.dot(toWorld(_a));

    // Check if ray hits triangle plane.
    float normalDotRayAhead = normal.dot(ray.getAhead());
    float normalDotRayOrigin = normal.dot(ray.getOrigin());

    float distance = (-d - normalDotRayOrigin) / normalDotRayAhead;

    if (Fp::le(distance, 0) || Fp::ge(distance, INFINITY))
    {
        return INFINITY;
    }

    // Check if ray hits triangle area.
    Point planePoint = ray.pointAt(distance).rebase(_origin);

    float abc = area(_a, _b, _c);

    float pbc = area(planePoint, _b, _c);
    float apc = area(_a, planePoint, _c);
    float abp = area(_a, _b, planePoint);

    if (Fp::gt(pbc + apc + abp, abc))
    {
        return INFINITY;
    }

    return distance;
}

float Triangle::area(Point const &a, Point const &b, Point const &c)
{
    // Compute triangle area using Heron formula.
    float ab = a.distanceTo(b);
    float ac = a.distanceTo(c);
    float bc = b.distanceTo(c);

    float p = (ab + ac + bc) / 2;
    float heron = p * (p - ac) * (p - bc) * (p - ab);

    return std::sqrt(std::max(heron, 0.f)); // fix rounding error
}

Vector Triangle::normalAt(Point const &surfacePoint) const
{
    return Vector(_c - _a).cross(Vector(_b - _a)).unitise();
}

Point Triangle::mapTexturePointFromSurfacePoint(Point const &surfacePoint) const
{
    float abc = area(_a, _b, _c);

    float r1 = area(surfacePoint, _b, _c) / abc;
    float r2 = area(_a, surfacePoint, _c) / abc;
    float r3 = 1 - r1 - r2;

    return _ta * r1 + _tb * r2 + _tc * r3;
}

Point Triangle::mapSurfacePointFromTexturePoint(Point const &texturePoint) const
{
    float tabc = area(_ta, _tb, _tc);

    float r1 = area(texturePoint, _tb, _tc) / tabc;
    float r2 = area(_ta, texturePoint, _tc) / tabc;
    float r3 = 1 - r1 - r2;

    return _a * r1 + _b * r2 + _c * r3;
}
