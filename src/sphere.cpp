#include "sphere.hpp"

#include "fp.hpp"
#include "ray.hpp"

Sphere::Sphere(float radius, Material const &material, Point const &origin) : Object(material, origin), _radius(radius)
{
}

float Sphere::intersectDistance(Ray const &ray) const
{
    // Possible 0, 1 or 2 solutions to the quadratic equation on intersected points.
    Vector toRay = _origin.vectorTo(ray.getOrigin());
    float b = toRay.dot(ray.getAhead());
    float delta = b * b - toRay.dot(toRay) + _radius * _radius;

    // No solutions.
    if (Fp::lt(delta, 0))
    {
        return INFINITY;
    }

    float deltaSquared = sqrt(delta);
    float distance1 = -b - deltaSquared;
    float distance2 = -b + deltaSquared;

    // Possible solutions.
    if (Fp::gt(distance1, 0))
    {
        return distance1;
    }

    if (Fp::gt(distance2, 0))
    {
        return distance2;
    }

    // No solutions.
    return INFINITY;
}

Vector Sphere::normalAt(Point const &surfacePoint) const
{
    return _origin.directionTo(surfacePoint);
}

Point Sphere::mapTexturePointFromSurfacePoint(Point const &surfacePoint) const
{
    Vector toSurfacePoint = _origin.vectorTo(surfacePoint);

    float yDivR = toSurfacePoint.y() / _radius;
    float latitudeRatio = Fp::arccos(yDivR) / M_PI;

    float rMulSin = _radius * sin(latitudeRatio * M_PI);
    float longtitudeRatio =
        Fp::eq(latitudeRatio, 0) ? 0 :                                 // south pole
            Fp::eq(latitudeRatio, 1) ? 0 :                             // north pole
                Fp::arccos(toSurfacePoint.x() / rMulSin) / (2 * M_PI); // elsewhere

    return Point(longtitudeRatio, latitudeRatio, 0);
}

Point Sphere::mapSurfacePointFromTexturePoint(Point const &texturePoint) const
{
    return Point(
        _origin.x() + _radius * sin(M_PI * texturePoint.y()) * cos(2 * M_PI * texturePoint.x()),
        _origin.y() + _radius * cos(M_PI * texturePoint.y()),
        _origin.z() + _radius * sin(M_PI * texturePoint.y()) * sin(2 * M_PI * texturePoint.x()));
}
