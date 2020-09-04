#include "object.hpp"

#include "fp.hpp"

Object::Object(Material const &material, Point const &origin) : _material(material), _origin(origin), _front(0, 0, 1), _up(0, 1, 0), _right(_up.cross(_front))
{
}

Point const &Object::getOrigin() const
{
    return _origin;
}

Vector const &Object::getUp() const
{
    return _up;
}

Vector const &Object::getFront() const
{
    return _front;
}

Vector const &Object::getRight() const
{
    return _right;
}

Material const &Object::getMaterial() const
{
    return _material;
}

Vector Object::mappedNormalAt(Point const &surfacePoint) const
{
    Vector normal = normalAt(surfacePoint);

    if (!_material.hasNormalMap())
    {
        return normal;
    }

    Point texturePoint = mapTexturePointFromSurfacePoint(surfacePoint);
    Vector mappedNormal = _material.getNormal(texturePoint);

    static const float delta = 100 * Fp::EPS;

    Point tx(texturePoint.x() + delta, texturePoint.y(), 0);
    Point tz(texturePoint.x(), texturePoint.y() + delta, 0);

    Point sx = mapSurfacePointFromTexturePoint(tx);
    Point sz = mapSurfacePointFromTexturePoint(tz);

    Vector x = surfacePoint.directionTo(sx);
    Vector z = surfacePoint.directionTo(sz);

    return mappedNormal.rebase(x, normal, z);
}

Point Object::toWorld(Point const &local) const
{
    return _origin + local;
}
