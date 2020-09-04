#include "camera.hpp"

#include "bilinear_filter.hpp"
#include "fp.hpp"
#include "ray.hpp"

Camera::Camera(size_t width, size_t height, Material const &material, Point origin) : Object(material, origin), _width(width), _height(height)
{
}

size_t Camera::getWidth() const
{
    return _width;
}

size_t Camera::getHeight() const
{
    return _height;
}

float Camera::intersectDistance(Ray const &ray) const
{
    // Intersect if ray heading towards camera.
    float cos = ray.getAhead().dot(ray.getOrigin().directionTo(_origin));

    if (Fp::eq(cos, 1))
    {
        return ray.getOrigin().distanceTo(_origin);
    }

    return INFINITY;
}

Vector Camera::normalAt(Point const &surfacePoint) const
{
    throw "Exception in Camera::rawNormalAt(): Camera has no normal vector.\n";
}

Point Camera::mapTexturePointFromSurfacePoint(Point const &surfacePoint) const
{
    throw "Exception in Camera::mapTexturePointFromSurfacePoint(): Camera has no texture.\n";
}

Point Camera::mapSurfacePointFromTexturePoint(Point const &texturePoint) const
{
    throw "Exception in Camera::mapSurfacePointFromTexturePoint(): Camera has no texture.\n";
}
