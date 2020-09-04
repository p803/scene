#include "hit.hpp"

#include <cstddef>

#include "object.hpp"
#include "point.hpp"
#include "ray.hpp"

Hit::Hit(Ray const &ray, float distance, Object const *object) : _ray(ray), _distance(distance), _object(object)
{
}

bool Hit::isUndefined() const
{
    return _object == NULL;
}

Point Hit::getSurfacePoint() const
{
    return _ray.pointAt(_distance);
}

Point Hit::getTexturePoint() const
{
    return _object->mapTexturePointFromSurfacePoint(getSurfacePoint());
}

Object const *Hit::getObject() const
{
    return _object;
}

bool Hit::is(Object const *object) const
{
    return _object == object;
}
