#include "ray.hpp"

#include "fp.hpp"
#include "hit.hpp"
#include "object.hpp"
#include "scene.hpp"

Ray::Ray(Point const &origin, Vector const &ahead) : _origin(origin), _ahead(ahead)
{
}

Point Ray::pointAt(float distance) const
{
    return _origin + _ahead * distance;
}

Point const &Ray::getOrigin() const
{
    return _origin;
}

Vector const &Ray::getAhead() const
{
    return _ahead;
}

Ray Ray::reflect(Object const *object, Point const &surfacePoint) const
{
    Vector normal = object->mappedNormalAt(surfacePoint);
    Vector aback = static_cast<Vector>(_ahead - 2 * normal * normal.dot(_ahead)).unitise();

    return Ray(surfacePoint, aback);
}

Ray Ray::transmit(Object const *object, Point const &surfacePoint) const
{
    float iorOutside = Scene::INDEX_OF_REFRACTION_AIR;
    float iorInside = object->getMaterial().getIndexOfRefraction();

    // Assume ray outside in.
    float ior = iorOutside / iorInside;
    Vector normal = object->mappedNormalAt(surfacePoint);
    float cos = -_ahead.dot(normal);

    // Swap values if ray inside out.
    if (Fp::lt(cos, 0))
    {
        ior = iorInside / iorOutside;
        normal *= -1;
        cos *= -1;
    }

    float t = 1 - ior * ior * (1 - cos * cos);

    return Ray(surfacePoint, static_cast<Vector>(normal * (ior * cos - sqrt(t)) + _ahead * ior).unitise());
}

Ray Ray::scatter(Object const *object, Point const &surfacePoint) const
{
    Vector normal = object->mappedNormalAt(surfacePoint);

    Vector x = _ahead.revert().cross(normal).unitise();
    Vector z = x.cross(normal);

    Vector direction = randomDirectionOnHemisphere().rebase(x, normal, z);

    return Ray(surfacePoint, direction);
}

float Ray::distanceTo(Object const *target) const
{
    return target->intersectDistance(*this);
}

Vector Ray::randomDirectionOnHemisphere()
{
    // Random direction on hemisphere with cosinus distribution.
    float a = Fp::rand();
    float b = Fp::rand();
    float c = std::sqrt(1 - a);

    float x = c * cos(2 * M_PI * b);
    float y = sqrt(a);
    float z = c * sin(2 * M_PI * b);

    return Vector(x, y, z).unitise();
}
